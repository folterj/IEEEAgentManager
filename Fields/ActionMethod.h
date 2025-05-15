#pragma once

#include "Field.h"

ref class ActionMethod : Field
{
public:
	Field^ objHandle;
	Field^ type;
	Field^ valLen;
	Field^ value;

	ActionMethod();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
