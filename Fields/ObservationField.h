#pragma once

#include "Field.h"

ref class ObservationField : Field
{
public:
	Field^ objectHandle;
	Field^ valLen;
	Field^ value;

	ObservationField();
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
