#pragma once

#include "Field.h"

ref class IAcse : Field
{
public:
	Field^ invokeId;
	Field^ roseType;
	Field^ roseLen;
	Field^ rose;

	IAcse();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
