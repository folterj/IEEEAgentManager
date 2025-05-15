#pragma once

#include "Field.h"
#include "ListField.h"

ref class ValList : Field
{
public:
	Field^ listCount;
	Field^ listLen;
	array<ListField^>^ vals;

	ValList();
	ValList(int count,int vallen);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
