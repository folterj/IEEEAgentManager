#include "StdAfx.h"
#include "ValList.h"
#include "ListField.h"
#include "nomenclature.h"

ValList::ValList()
{
	listCount = gcnew Field(2);
	listLen = gcnew Field(2);
}

ValList::ValList(int count,int vallen)
{
	listCount = gcnew Field(2);
	listLen = gcnew Field(2);

	listCount->set(count);

	vals = gcnew array<ListField^>(count);
	for (int i=0;i<count;i++) {
		vals[i] = gcnew ListField(vallen);
	}
}

bool ValList::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	int count;
	int len;
	int vallen;

	ok &= listCount->decode(data,index);
	ok &= listLen->decode(data,index);

	count = (int)listCount->get();
	len = (int)listLen->get();
	vals = gcnew array<ListField^>(count);
	vallen = len / count;	// assume length of each field = total length / total count

	for (int i=0;i<count;i++) {
		vals[i] = gcnew ListField(vallen);
		ok &= vals[i]->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ValList::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ listData = gcnew array<Byte>(0);
	int count = vals->Length;
	int totsublen = 0;

	for (int i=0;i<count;i++) {
		listData = addData(listData,vals[i]->encode());
		totsublen += vals[i]->getLen();
	}
	listCount->set(count);
	listLen->set(totsublen);

	data = addData(data,listCount->encode());
	data = addData(data,listLen->encode());
	data = addData(data,listData);

	len = data->Length;

	return data;
}

String^ ValList::getShortDesc()
{
	return "";
}

String^ ValList::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add(String::Format("listCount:{0}",listCount->get()));
	desc->add(String::Format("listLen:{0}",listLen->get()));

	// composite fields
	for (int i=0;i<vals->Length;i++) {
		desc->addChild("listAttribute",vals[i]->getFullDesc());
	}
	return desc->string;
}
