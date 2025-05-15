#include "StdAfx.h"
#include "Prst.h"

Prst::Prst()
{
	iacseLen = gcnew Field(2);
	iacse = gcnew IAcse();
}

bool Prst::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= iacseLen->decode(data,index);
	ok &= iacse->decode(data,index);

	len = index - index0;

	if (iacseLen->get() != iacse->getLen()) {
		ok = false;
	}
	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ Prst::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ iacseData = iacse->encode();

	iacseLen->set(iacse->getLen());

	data = addData(data,iacseLen->encode());
	data = addData(data,iacseData);

	len = data->Length;

	return data;
}

String^ Prst::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	if (iacse) {
		desc->addChild("",iacse->getShortDesc());
	}
	return desc->string;
}

String^ Prst::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();
	
	// simple fields
	desc->add(String::Format("iacseLen:{0}",iacseLen->get()));

	// composite fields
	if (iacse) {
		desc->addChild("iacse",iacse->getFullDesc());
	}
	return desc->string;
}
