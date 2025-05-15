#pragma once

#include "Field.h"

ref class ProtoInfo : Field
{
public:
	Field^ protoVer;
	Field^ encoding;
	Field^ nomVer;
	Field^ funcUnits;
	Field^ systemType;
	Field^ systemIdLen;
	Field^ systemId;
	Field^ configId;
	Field^ reqMode;
	Field^ reqAgentCount;
	Field^ reqManagerCount;
	Field^ optionCount;
	Field^ optionLen;

	ProtoInfo();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
