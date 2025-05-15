#pragma once

#include "Field.h"
#include "Proto.h"

ref class Aarq : Field
{
public:
	Field^ assocVer;
	Field^ protoCount;
	Field^ protoLen;
	Proto^ proto;

	Aarq();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
