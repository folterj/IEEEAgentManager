#pragma once

#include "Field.h"
#include "AttributeList.h"

ref class ObjectList : Field
{
public:
	Field^ reportId;
	Field^ objectCount;
	Field^ objectLen;
	array<AttributeList^>^ attributeLists;

	ObjectList();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
