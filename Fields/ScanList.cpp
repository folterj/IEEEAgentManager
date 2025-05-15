#include "StdAfx.h"
#include "ScanList.h"
#include "ScanItemList.h"
#include "ObservationField.h"
#include "nomenclature.h"

ScanList::ScanList(int reportType0)
{
	reqId = gcnew Field(2);
	reportNo = gcnew Field(2);
	obsCount = gcnew Field(2);
	obsLen = gcnew Field(2);

	reportType = reportType0;
}

bool ScanList::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	bool fixedObs = (reportType == MDC_NOTI_SCAN_REPORT_FIXED);
	int count;

	ok &= reqId->decode(data,index);
	ok &= reportNo->decode(data,index);
	ok &= obsCount->decode(data,index);
	ok &= obsLen->decode(data,index);

	count = (int)obsCount->get();
	if (fixedObs) {
		items = gcnew array<ObservationField^>(count);
	} else {
		items = gcnew array<ScanItemList^>(count);
	}

	for (int i=0;i<count;i++) {
		if (fixedObs) {
			items[i] = gcnew ObservationField();
		} else {
			items[i] = gcnew ScanItemList();
		}
		ok &= items[i]->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ScanList::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ obsData = gcnew array<Byte>(0);
	int count = items->Length;
	int totsublen = 0;

	for (int i=0;i<count;i++) {
		obsData = addData(obsData,items[i]->encode());
		totsublen += items[i]->getLen();
	}
	obsCount->set(count);
	obsLen->set(totsublen);

	data = addData(data,reqId->encode());
	data = addData(data,reportNo->encode());
	data = addData(data,obsCount->encode());
	data = addData(data,obsLen->encode());
	data = addData(data,obsData);

	len = data->Length;

	return data;
}

String^ ScanList::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add("reqId:" + reqId->getShortDesc());
	desc->add(String::Format("reportNo:{0}",reportNo->get()));

	for (int i=0;i<items->Length;i++) {
		desc->addChild("",items[i]->getShortDesc());
	}
	return desc->string;
}

String^ ScanList::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("reqId:" + reqId->getFullDesc());
	desc->add(String::Format("reportNo:{0}",reportNo->get()));

	// composite fields
	for (int i=0;i<items->Length;i++) {
		desc->addChild("observation",items[i]->getFullDesc());
	}
	return desc->string;
}
