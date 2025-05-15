#include "StdAfx.h"
#include "AttributeList.h"
#include "nomenclature.h"
#include "conversion.h"

AttributeList::AttributeList()
{
	objectClass = gcnew Field(2);
	objectHandle = gcnew Field(2);
	attributeCount = gcnew Field(2);
	attributeLen = gcnew Field(2);
}

AttributeList::AttributeList(int nattr)
{
	objectClass = gcnew Field(2);
	objectHandle = gcnew Field(2);
	attributeCount = gcnew Field(2);
	attributeLen = gcnew Field(2);

	attributes = gcnew array<AttributeField^>(nattr);
}

bool AttributeList::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	int count;

	ok &= objectClass->decode(data,index);
	ok &= objectHandle->decode(data,index);
	ok &= attributeCount->decode(data,index);
	ok &= attributeLen->decode(data,index);

	count = (int)attributeCount->get();
	attributes = gcnew array<AttributeField^>(count);

	for (int i=0;i<count;i++) {
		attributes[i] = gcnew AttributeField();
		ok &= attributes[i]->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ AttributeList::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ attributeData = gcnew array<Byte>(0);
	int count = attributes->Length;
	int totsublen = 0;

	for (int i=0;i<count;i++) {
		attributeData = addData(attributeData,attributes[i]->encode());
		totsublen += attributes[i]->getLen();
	}
	attributeCount->set(count);
	attributeLen->set(totsublen);

	data = addData(data,objectClass->encode());
	data = addData(data,objectHandle->encode());
	data = addData(data,attributeCount->encode());
	data = addData(data,attributeLen->encode());
	data = addData(data,attributeData);

	len = data->Length;

	return data;
}

String^ AttributeList::getObjectClassType()
{
	String^ desc = objClass((int)objectClass->get());
	if (desc == "") {
		desc = objectClass->getShortDesc();
	}
	return desc;
}

String^ AttributeList::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	for (int i=0;i<attributes->Length;i++) {
		desc->addChild("",attributes[i]->getShortDesc());
	}
	return desc->string;
}

String^ AttributeList::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("objectClass:" + getObjectClassType());
	desc->add(String::Format("objectHandle:{0}",objectHandle->get()));
	desc->add(String::Format("attributeCount:{0}",attributeCount->get()));
	desc->add(String::Format("attributeLen:{0}",attributeLen->get()));

	// composite fields
	for (int i=0;i<attributes->Length;i++) {
		desc->addChild("attribute",attributes[i]->getFullDesc());
	}
	return desc->string;
}
