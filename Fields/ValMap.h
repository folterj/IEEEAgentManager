#pragma once

#include "Field.h"
#include "MapField.h"

ref class ValMap : Field
{
public:
	Field^ mapCount;
	Field^ mapLen;
	array<MapField^>^ maps;

	ValMap();
	ValMap(int count);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
