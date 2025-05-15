#pragma once

#include "Field.h"
#include "ProtoInfo.h"

ref class Aare : Field
{
public:
	Field^ assocResult;
	Field^ protoId;
	Field^ protoInfoLen;
	ProtoInfo^ protoInfo;

	Aare();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getResultType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
