#include "StdAfx.h"
#include "Apdu.h"
#include "Aarq.h"
#include "Aare.h"
#include "Rlrq.h"
#include "Rlre.h"
#include "Abrt.h"
#include "Prst.h"
#include "phd_constants.h"
#include "conversion.h"

Apdu::Apdu()
{
	acseType = gcnew Field(2);
	acseLen = gcnew Field(2);
}

bool Apdu::decode(array<Byte>^ data)
{
	int index = 0;
	bool ok = true;

	ok &= acseType->decode(data,index);
	ok &= acseLen->decode(data,index);

	switch (acseType->get()) {
		case AARQ_CHOSEN:
			acse = gcnew Aarq();
			break;
		case AARE_CHOSEN:
			acse = gcnew Aare();
			break;
		case RLRQ_CHOSEN:
			acse = gcnew Rlrq();
			break;
		case RLRE_CHOSEN:
			acse = gcnew Rlre();
			break;
		case ABRT_CHOSEN:
			acse = gcnew Abrt();
			break;
		case PRST_CHOSEN:
			acse = gcnew Prst();
			break;
	}
	if (acse) {
		ok &= acse->decode(data,index);
		if (acseLen->get() != acse->getLen()) {
			ok = false;
		}
	} else {
		ok = false;
	}

	len = index;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ Apdu::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ acseData = acse->encode();

	acseLen->set(acse->getLen());

	data = addData(data,acseType->encode());
	data = addData(data,acseLen->encode());
	data = addData(data,acseData);

	len = data->Length;

	return data;
}

String^ Apdu::getType()
{
	String^ desc = apduChoice((int)acseType->get());
	if (desc == "") {
		desc = acseType->getShortDesc();
	}
	return desc;
}

String^ Apdu::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add(getType());
	if (acse) {
		desc->addChild("",acse->getShortDesc());
	}
	return desc->string;
}

String^ Apdu::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("acseType:" + getType());
	desc->add(String::Format("acseLen:{0}",acseLen->get()));

	// composite fields
	if (acse) {
		desc->addChild("acse",acse->getFullDesc());
	}
	return desc->string;
}
