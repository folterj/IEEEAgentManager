#pragma once

#include "Field.h"

ref class FieldTemplate : Field
{
public:
	Field^ x;
	Field^ subLen;
	Field^ subgroup;

	FieldTemplate();
	virtual String^ decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
};
