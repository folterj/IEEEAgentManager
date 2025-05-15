#pragma once

#include "Field.h"

ref class ListField : Field
{
public:
	Field^ content;

	ListField(int len0);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getAttributeType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
