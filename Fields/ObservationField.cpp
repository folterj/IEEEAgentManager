#include "StdAfx.h"
#include "ObservationField.h"
#include "nomenclature.h"

ObservationField::ObservationField()
{
	objectHandle = gcnew Field(2);
	valLen = gcnew Field(2);
}

bool ObservationField::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= objectHandle->decode(data,index);
	ok &= valLen->decode(data,index);
	value = gcnew Field((int)valLen->get());
	ok &= value->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ObservationField::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ valData = value->encode();

	valLen->set(value->getLen());

	data = addData(data,objectHandle->encode());
	data = addData(data,valLen->encode());
	data = addData(data,valData);

	len = data->Length;

	return data;
}


String^ ObservationField::getShortDesc()
{
	return String::Format("objectHandle:{0}",objectHandle->get());
}

String^ ObservationField::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();

	// simple fields
	desc->add(String::Format("objectHandle:{0}",objectHandle->get()));
	desc->add(String::Format("valLen:{0}",valLen->get()));

	// composite fields
	if (value) {
		desc->addChild("value",value->getFullDesc());
	}
	return desc->string;
}
