#pragma once

#include "Field.h"

ref class Apdu : Field
{
public:
	Field^ acseType;
	Field^ acseLen;
	Field^ acse;

	Apdu();
	bool decode(array<Byte>^ data);
	virtual array<Byte>^ encode() override;
	String^ getType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
