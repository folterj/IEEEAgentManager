#pragma once

#include "Field.h"

ref class MapField : Field
{
public:
	Field^ id;
	Field^ valLen;

	MapField();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getAttributeType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
