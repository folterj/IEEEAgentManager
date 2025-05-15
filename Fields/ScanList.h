#pragma once

#include "Field.h"
#include "ObservationField.h"

ref class ScanList : Field
{
public:
	Field^ reqId;
	Field^ reportNo;
	Field^ obsCount;
	Field^ obsLen;
	array<Field^>^ items;

	int reportType;

	ScanList(int reportType0);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
