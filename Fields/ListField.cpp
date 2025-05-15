#include "StdAfx.h"
#include "ListField.h"
#include "conversion.h"

ListField::ListField(int len0)
{
	content = gcnew Field(len0);
}

bool ListField::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= content->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ListField::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);

	data = addData(data,content->encode());

	len = data->Length;

	return data;
}

String^ ListField::getAttributeType()
{
	String^ desc = attrId((int)content->get());
	if (desc == "") {
		desc = content->getShortDesc();
	}
	return desc;
}

String^ ListField::getShortDesc()
{
	return "";
}

String^ ListField::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("content:" + getAttributeType());

	return desc->string;
}
