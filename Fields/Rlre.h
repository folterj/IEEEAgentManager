#pragma once

#include "Field.h"

ref class Rlre : Field
{
public:
	Field^ reason;

	Rlre();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
