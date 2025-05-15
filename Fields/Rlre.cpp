#include "StdAfx.h"
#include "Rlre.h"

Rlre::Rlre()
{
	reason = gcnew Field(2);
}

bool Rlre::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= reason->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ Rlre::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);

	data = addData(data,reason->encode());

	len = data->Length;

	return data;
}

String^ Rlre::getShortDesc()
{
	return String::Format("reason:{0}",reason->get());
}

String^ Rlre::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add(getShortDesc());

	return desc->string;
}
