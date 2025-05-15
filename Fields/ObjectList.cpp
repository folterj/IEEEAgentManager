#include "StdAfx.h"
#include "ObjectList.h"

ObjectList::ObjectList()
{
	reportId = gcnew Field(2);
	objectCount = gcnew Field(2);
	objectLen = gcnew Field(2);
}

bool ObjectList::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	int count;

	ok &= reportId->decode(data,index);
	ok &= objectCount->decode(data,index);
	ok &= objectLen->decode(data,index);

	count = (int)objectCount->get();
	attributeLists = gcnew array<AttributeList^>(count);

	for (int i=0;i<count;i++) {
		attributeLists[i] = gcnew AttributeList();
		ok &= attributeLists[i]->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ObjectList::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ attrsData = gcnew array<Byte>(0);
	int count = attributeLists->Length;
	int totsublen = 0;

	for (int i=0;i<count;i++) {
		attrsData = addData(attrsData,attributeLists[i]->encode());
		totsublen += attributeLists[i]->getLen();
	}
	objectCount->set(count);
	objectLen->set(totsublen);

	data = addData(data,reportId->encode());
	data = addData(data,objectCount->encode());
	data = addData(data,objectLen->encode());
	data = addData(data,attrsData);

	len = data->Length;

	return data;
}

String^ ObjectList::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add("reportId:" + reportId->getShortDesc());

	for (int i=0;i<attributeLists->Length;i++) {
		desc->addChild("",attributeLists[i]->getShortDesc());
	}
	return desc->string;
}

String^ ObjectList::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add("reportId:" + reportId->getShortDesc());

	// composite fields
	for (int i=0;i<attributeLists->Length;i++) {
		desc->addChild("attributeList",attributeLists[i]->getFullDesc());
	}
	return desc->string;
}
