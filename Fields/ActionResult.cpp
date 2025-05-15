#include "StdAfx.h"
#include "ActionResult.h"
#include "nomenclature.h"
#include "conversion.h"

ActionResult::ActionResult()
{
	objHandle = gcnew Field(2);
	type = gcnew Field(2);
	result = gcnew Field(2);
}

bool ActionResult::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= objHandle->decode(data,index);
	ok &= type->decode(data,index);
	ok &= result->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ActionResult::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);

	data = addData(data,objHandle->encode());
	data = addData(data,type->encode());
	data = addData(data,result->encode());

	len = data->Length;

	return data;
}

String^ ActionResult::getType()
{
	String^ desc = actionType((int)type->get());
	if (desc == "") {
		desc = type->getShortDesc();
	}
	return desc;
}

String^ ActionResult::getShortDesc()
{
	return getType();
}

String^ ActionResult::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();
	UInt16 res;
	String^ results;

	res = (UInt16)result->get();
	if (res == 0) {
		results = "Ok";
	} else {
		results = errorId(res);
	}
	
	desc->add(String::Format("objHandle:{0}",objHandle->get()));
	desc->add(String::Format("actionType:" + getType()));
	desc->add("Result:" + results);

	return desc->string;
}
