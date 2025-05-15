#include "StdAfx.h"
#include "Aarq.h"

Aarq::Aarq()
{
	assocVer = gcnew Field(4);
	protoCount = gcnew Field(2);
	protoLen = gcnew Field(2);
	proto = gcnew Proto(1);
}

bool Aarq::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= assocVer->decode(data,index);
	ok &= protoCount->decode(data,index);
	ok &= protoLen->decode(data,index);
	ok &= proto->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ Aarq::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ protoData = proto->encode();

	protoLen->set(proto->getLen());

	data = addData(data,assocVer->encode());
	data = addData(data,protoCount->encode());
	data = addData(data,protoLen->encode());
	data = addData(data,protoData);

	len = data->Length;

	return data;
}

String^ Aarq::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->addChild("",proto->getShortDesc());

	return desc->string;
}

String^ Aarq::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("assocVer:" + assocVer->getShortDesc());
	desc->add(String::Format("protoCount:{0}",protoCount->get()));
	desc->add(String::Format("protoLen:{0}",protoLen->get()));

	// composite fields
	desc->addChild("proto",proto->getFullDesc());

	return desc->string;
}
