#include "StdAfx.h"
#include "ActionMethod.h"
#include "nomenclature.h"
#include "conversion.h"

ActionMethod::ActionMethod()
{
	objHandle = gcnew Field(2);
	type = gcnew Field(2);
	valLen = gcnew Field(2);
}

bool ActionMethod::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= objHandle->decode(data,index);
	ok &= type->decode(data,index);
	ok &= valLen->decode(data,index);
	value = gcnew Field((int)valLen->get());
	ok &= value->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ActionMethod::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ valData = value->encode();

	valLen->set(value->getLen());

	data = addData(data,objHandle->encode());
	data = addData(data,type->encode());
	data = addData(data,valLen->encode());
	data = addData(data,valData);

	len = data->Length;

	return data;
}

String^ ActionMethod::getType()
{
	String^ desc = actionType((int)type->get());
	if (desc == "") {
		desc = type->getShortDesc();
	}
	return desc;
}

String^ ActionMethod::getShortDesc()
{
	return getType();
}

String^ ActionMethod::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();
	
	// simple fields
	desc->add(String::Format("objHandle:{0}",objHandle->get()));
	desc->add(String::Format("actionType:" + getType()));
	desc->add(String::Format("valLen:{0}",valLen->get()));
	desc->add("value:" + value->getFullDesc());

	return desc->string;
}
