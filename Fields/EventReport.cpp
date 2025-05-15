#include "StdAfx.h"
#include "EventReport.h"
#include "nomenclature.h"
#include "ObjectList.h"
#include "ScanList.h"
#include "Report.h"
#include "conversion.h"

EventReport::EventReport(int nitems,bool listContent)
{
	this->listContent = listContent;
	objHandle = gcnew Field(2);
	eventTime = gcnew Field(4);
	eventType = gcnew Field(2);
	eventLen = gcnew Field(2);
	eventItems = gcnew array<Field^>(nitems);
}

bool EventReport::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	int totlen = 0;

	ok &= objHandle->decode(data,index);
	ok &= eventTime->decode(data,index);
	ok &= eventType->decode(data,index);
	ok &= eventLen->decode(data,index);

	if (eventLen->get() > 0) {
		eventItems = gcnew array<Field^>(1);
		for (int i=0;i<eventItems->Length;i++) {
			switch (eventType->get()) {
				case MDC_NOTI_CONFIG:				// 0x0D1C
					if (listContent) {
						eventItems[i] = gcnew ObjectList();
					} else {
						eventItems[i] = gcnew Report();
					}
					break;
				case MDC_NOTI_SCAN_REPORT_FIXED:	// 0x0D1D
				case MDC_NOTI_SCAN_REPORT_VAR:		// 0x0D1E
					eventItems[i] = gcnew ScanList((int)eventType->get());
					break;
			}
			ok &= eventItems[i]->decode(data,index);
			totlen += eventItems[i]->getLen();
		}
	}

	len = index - index0;

	if (eventLen->get() != totlen) {
		ok = false;
	}
	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ EventReport::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ eventData = gcnew array<Byte>(0);
	int totsublen = 0;

	for (int i=0;i<eventItems->Length;i++) {
		eventData = addData(eventData,eventItems[i]->encode());
		totsublen += eventItems[i]->getLen();
	}
	eventLen->set(totsublen);

	data = addData(data,objHandle->encode());
	data = addData(data,eventTime->encode());
	data = addData(data,eventType->encode());
	data = addData(data,eventLen->encode());
	data = addData(data,eventData);

	len = data->Length;

	return data;
}

String^ EventReport::getType()
{
	String^ desc = roseChoice((int)eventType->get());
	if (desc == "") {
		desc = eventType->getShortDesc();
	}
	return desc;
}

String^ EventReport::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add(getType());
	for (int i=0;i<eventItems->Length;i++) {
		desc->addChild("",eventItems[i]->getShortDesc());
	}
	return desc->string;
}

String^ EventReport::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();
	
	// simple fields
	desc->add(String::Format("objHandle:{0}",objHandle->get()));
	desc->add(String::Format("eventTime:{0:X8}",eventTime->get()));
	desc->add("eventType:" + getType());
	desc->add(String::Format("eventLen:{0}",eventLen->get()));

	// composite fields
	for (int i=0;i<eventItems->Length;i++) {
		desc->addChild("eventItem",eventItems[i]->getFullDesc());
	}
	return desc->string;
}
