#pragma once

#include "Field.h"

ref class Abrt : Field
{
public:
	Field^ reason;

	Abrt();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
