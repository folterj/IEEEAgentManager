#include "StdAfx.h"
#include "IAcse.h"
#include "phd_constants.h"
#include "EventReport.h"
#include "MdsAttributeList.h"
#include "ActionMethod.h"
#include "ActionResult.h"
#include "conversion.h"


IAcse::IAcse()
{
	invokeId = gcnew Field(2);
	roseType = gcnew Field(2);
	roseLen = gcnew Field(2);
}

bool IAcse::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= invokeId->decode(data,index);
	ok &= roseType->decode(data,index);
	ok &= roseLen->decode(data,index);

	switch (roseType->get()) {
		// ROIV
		case ROIV_CMIP_EVENT_REPORT_CHOSEN:
		case ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN:
			rose = gcnew EventReport(0,true);
			break;
		case ROIV_CMIP_GET_CHOSEN:
			rose = gcnew MdsAttributeList(0);
			break;
		// RORS
		case RORS_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN:
			rose = gcnew EventReport(0,false);
			break;
		case RORS_CMIP_GET_CHOSEN:
			rose = gcnew MdsAttributeList();
			break;
		case ROIV_CMIP_ACTION_CHOSEN:
		case ROIV_CMIP_CONFIRMED_ACTION_CHOSEN:
			rose = gcnew ActionMethod();
			break;
		case RORS_CMIP_CONFIRMED_ACTION_CHOSEN:
			rose = gcnew ActionResult();
			break;
	}
	if (rose) {
		ok &= rose->decode(data,index);
		if (roseLen->get() != rose->getLen()) {
			ok = false;
		}
	} else {
		ok = false;
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ IAcse::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ roseData = rose->encode();

	roseLen->set(rose->getLen());

	data = addData(data,invokeId->encode());
	data = addData(data,roseType->encode());
	data = addData(data,roseLen->encode());
	data = addData(data,roseData);

	len = data->Length;

	return data;
}

String^ IAcse::getType()
{
	String^ desc = acseChoice((int)roseType->get());
	if (desc == "") {
		desc = roseType->getShortDesc();
	}
	return desc;
}

String^ IAcse::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add(getType());
	if (rose) {
		desc->addChild("",rose->getShortDesc());
	}
	return desc->string;
}

String^ IAcse::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add(String::Format("invokeId:{0}",invokeId->get()));
	desc->add("roseType:" + getType());
	desc->add(String::Format("roseLen:{0}",roseLen->get()));

	// composite fields
	if (rose) {
		desc->addChild("rose",rose->getFullDesc());
	}
	return desc->string;
}
