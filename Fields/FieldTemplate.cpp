#include "StdAfx.h"
#include "FieldTemplate.h"

FieldTemplate::FieldTemplate()
{
	x = gcnew Field(2);
	subLen = gcnew Field(2);
}

String^ FieldTemplate::decode(array<Byte>^ data,int% index)
{
	String^ desc = "";

	x->decode(data,index);
	subLen->decode(data,index);

	switch (x->get()) {
		//case ...:
			//subgroup = gcnew ...
			//break;
	}
	if (subgroup) {
		desc += subgroup->decode(data,index);
	}

	len = index;

	return desc;
}

array<Byte>^ FieldTemplate::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ subgroupData = subgroup->encode();

	subLen->set(subgroup->len);

	data = addData(data,x->encode());
	data = addData(data,subLen->encode());
	data = addData(data,subgroupData);

	len = data->Length;

	return data;
}
