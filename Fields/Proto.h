#pragma once

#include "Field.h"
#include "ProtoInfo.h"

ref class Proto : Field
{
public:
	Field^ protoId;
	Field^ protoInfoLen;
	array<ProtoInfo^>^ protoInfo;

	Proto(int nProtoInfo);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
