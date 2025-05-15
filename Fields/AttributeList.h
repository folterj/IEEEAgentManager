#pragma once

#include "Field.h"
#include "AttributeField.h"

ref class AttributeList : Field
{
public:
	Field^ objectClass;
	Field^ objectHandle;
	Field^ attributeCount;
	Field^ attributeLen;
	array<AttributeField^>^ attributes;

	AttributeList();
	AttributeList(int nattr);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getObjectClassType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
