#include "StdAfx.h"
#include "MdsAttributeList.h"

MdsAttributeList::MdsAttributeList()
{
	objectHandle = gcnew Field(2);
	attributeCount = gcnew Field(2);
	attributeLen = gcnew Field(2);
}

MdsAttributeList::MdsAttributeList(int nattr)
{
	objectHandle = gcnew Field(2);
	attributeCount = gcnew Field(2);
	attributeLen = gcnew Field(2);

	attributes = gcnew array<AttributeField^>(nattr);
}

bool MdsAttributeList::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	int count;
	int totlen = 0;

	ok &= objectHandle->decode(data,index);
	ok &= attributeCount->decode(data,index);
	ok &= attributeLen->decode(data,index);

	count = (int)attributeCount->get();
	attributes = gcnew array<AttributeField^>(count);

	for (int i=0;i<count;i++) {
		attributes[i] = gcnew AttributeField();
		ok &= attributes[i]->decode(data,index);
		totlen += attributes[i]->getLen();
	}

	len = index - index0;

	if (attributeLen->get() != totlen) {
		ok = false;
	}
	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ MdsAttributeList::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ attributeData = gcnew array<Byte>(0);
	int count = 0;
	int totsublen = 0;

	if (attributes) {
		count = attributes->Length;
	}

	for (int i=0;i<count;i++) {
		attributeData = addData(attributeData,attributes[i]->encode());
		totsublen += attributes[i]->getLen();
	}
	attributeCount->set(count);
	attributeLen->set(totsublen);

	data = addData(data,objectHandle->encode());
	data = addData(data,attributeCount->encode());
	data = addData(data,attributeLen->encode());
	data = addData(data,attributeData);

	len = data->Length;

	return data;
}

String^ MdsAttributeList::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	if (attributes) {
		for (int i=0;i<attributes->Length;i++) {
			desc->addChild("",attributes[i]->getShortDesc());
		}
	}
	return desc->string;
}

String^ MdsAttributeList::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add(String::Format("objectHandle:{0}",objectHandle->get()));
	desc->add(String::Format("attributeCount:{0}",attributeCount->get()));
	desc->add(String::Format("attributeLen:{0}",attributeLen->get()));

	// composite fields
	if (attributes) {
		for (int i=0;i<attributes->Length;i++) {
			desc->addChild("attribute",attributes[i]->getFullDesc());
		}
	}
	return desc->string;
}
