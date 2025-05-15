#pragma once

#include "Field.h"
#include "AttributeField.h"

ref class ScanItemList : Field
{
public:
	Field^ objectHandle;
	Field^ itemCount;
	Field^ itemLen;
	array<AttributeField^>^ items;

	ScanItemList();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
