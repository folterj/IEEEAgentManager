#pragma once

#include "Field.h"
#include "AttributeField.h"

ref class MdsAttributeList : Field
{
public:
	Field^ objectHandle;
	Field^ attributeCount;
	Field^ attributeLen;
	array<AttributeField^>^ attributes;

	MdsAttributeList();
	MdsAttributeList(int nattr);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
