#include "StdAfx.h"
#include "ScanItemList.h"
#include "nomenclature.h"
#include "conversion.h"
#include "ValMap.h"
#include "ValList.h"

ScanItemList::ScanItemList()
{
	objectHandle = gcnew Field(2);
	itemCount = gcnew Field(2);
	itemLen = gcnew Field(2);
}

bool ScanItemList::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	int count;

	ok &= objectHandle->decode(data,index);
	ok &= itemCount->decode(data,index);
	ok &= itemLen->decode(data,index);

	count = (int)itemCount->get();
	items = gcnew array<AttributeField^>(count);

	for (int i=0;i<count;i++) {
		items[i] = gcnew AttributeField();
		ok &= items[i]->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ScanItemList::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ itemData = gcnew array<Byte>(0);
	int count = items->Length;
	int totsublen = 0;

	for (int i=0;i<count;i++) {
		itemData = addData(itemData,items[i]->encode());
		totsublen += items[i]->getLen();
	}
	itemCount->set(count);
	itemLen->set(totsublen);

	data = addData(data,objectHandle->encode());
	data = addData(data,itemCount->encode());
	data = addData(data,itemLen->encode());
	data = addData(data,itemData);

	len = data->Length;

	return data;
}

String^ ScanItemList::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add(String::Format("objectHandle:{0}",objectHandle->get()));
	for (int i=0;i<items->Length;i++) {
		desc->addChild("",items[i]->getShortDesc());
	}
	return desc->string;
}

String^ ScanItemList::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add(String::Format("objectHandle:{0}",objectHandle->get()));
	desc->add(String::Format("itemCount:{0}",itemCount->get()));
	desc->add(String::Format("itemLen:{0}",itemLen->get()));

	// composite fields
	for (int i=0;i<items->Length;i++) {
		desc->addChild("item",items[i]->getFullDesc());
	}
	return desc->string;
}
