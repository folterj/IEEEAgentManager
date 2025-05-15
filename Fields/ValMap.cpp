#include "StdAfx.h"
#include "ValMap.h"
#include "nomenclature.h"

ValMap::ValMap()
{
	mapCount = gcnew Field(2);
	mapLen = gcnew Field(2);
}

ValMap::ValMap(int count)
{
	mapCount = gcnew Field(2);
	mapLen = gcnew Field(2);

	mapCount->set(count);

	maps = gcnew array<MapField^>(count);
	for (int i=0;i<count;i++) {
		maps[i] = gcnew MapField();
	}
}

bool ValMap::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;
	int count;

	ok &= mapCount->decode(data,index);
	ok &= mapLen->decode(data,index);

	count = (int)mapCount->get();
	maps = gcnew array<MapField^>(count);

	for (int i=0;i<count;i++) {
		maps[i] = gcnew MapField();
		ok &= maps[i]->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ValMap::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ mapData = gcnew array<Byte>(0);
	int count = maps->Length;
	int totsublen = 0;

	for (int i=0;i<count;i++) {
		mapData = addData(mapData,maps[i]->encode());
		totsublen += maps[i]->getLen();
	}
	mapCount->set(count);
	mapLen->set(totsublen);

	data = addData(data,mapCount->encode());
	data = addData(data,mapLen->encode());
	data = addData(data,mapData);

	len = data->Length;

	return data;
}

String^ ValMap::getShortDesc()
{
	return "";
}

String^ ValMap::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add(String::Format("mapCount:{0}",mapCount->get()));
	desc->add(String::Format("mapLen:{0}",mapLen->get()));

	// composite fields
	for (int i=0;i<maps->Length;i++) {
		desc->addChild("mapAttribute",maps[i]->getFullDesc());
	}
	return desc->string;
}
