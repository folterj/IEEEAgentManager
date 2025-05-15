#pragma once

#include "Field.h"

ref class AttributeField : Field
{
public:
	Field^ id;
	Field^ valLen;
	Field^ value;

	AttributeField();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getAttributeType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
