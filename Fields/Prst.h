#pragma once

#include "Field.h"
#include "IAcse.h"

ref class Prst : Field
{
public:
	Field^ iacseLen;
	IAcse^ iacse;

	Prst();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
