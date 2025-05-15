#include "StdAfx.h"
#include "MapField.h"
#include "conversion.h"

MapField::MapField()
{
	id = gcnew Field(2);
	valLen = gcnew Field(2);
}

bool MapField::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= id->decode(data,index);
	ok &= valLen->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ MapField::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);

	data = addData(data,id->encode());
	data = addData(data,valLen->encode());

	len = data->Length;

	return data;
}

String^ MapField::getAttributeType()
{
	String^ desc = attrId((int)id->get());
	if (desc == "") {
		desc = id->getShortDesc();
	}
	return desc;
}

String^ MapField::getShortDesc()
{
	return "";
}

String^ MapField::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("id:" + getAttributeType());
	desc->add(String::Format("valLen:{0}",valLen->get()));

	return desc->string;
}
