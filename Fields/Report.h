#pragma once

#include "Field.h"
#include "AttributeList.h"

ref class Report : Field
{
public:
	Field^ reportId;
	Field^ reportResult;

	Report();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
