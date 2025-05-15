#include "StdAfx.h"
#include "AttributeField.h"
#include "nomenclature.h"
#include "conversion.h"
#include "ValMap.h"
#include "ValList.h"

AttributeField::AttributeField()
{
	id = gcnew Field(2);
	valLen = gcnew Field(2);
}

bool AttributeField::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= id->decode(data,index);
	ok &= valLen->decode(data,index);

	switch (id->get()) {
		case MDC_ATTR_ATTRIBUTE_VAL_MAP:
			// val map
			value = gcnew ValMap();
			break;
		case MDC_ATTR_ID_PHYSIO_LIST:
			// list
			value = gcnew ValList();
			break;
		default:
			// simple value
			value = gcnew Field((int)valLen->get());
			break;
	}
	if (value) {
		ok &= value->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ AttributeField::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ valData = value->encode();

	valLen->set(value->getLen());

	data = addData(data,id->encode());
	data = addData(data,valLen->encode());
	data = addData(data,valData);

	len = data->Length;

	return data;
}

String^ AttributeField::getAttributeType()
{
	String^ desc = attrId((int)id->get());
	if (desc == "") {
		desc = id->getShortDesc();
	}
	return desc;
}

String^ AttributeField::getShortDesc()
{
	return "";
}

String^ AttributeField::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("id:" + getAttributeType());
	desc->add(String::Format("valLen:{0}",valLen->get()));

	// composite fields
	if (value) {
		desc->addChild("value",value->getFullDesc());
	}
	return desc->string;
}
