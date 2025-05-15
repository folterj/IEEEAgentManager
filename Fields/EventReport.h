#pragma once

#include "Field.h"

ref class EventReport : Field
{
public:
	Field^ objHandle;
	Field^ eventTime;
	Field^ eventType;
	Field^ eventLen;
	array<Field^>^ eventItems;
	bool listContent;

	EventReport(int nitems,bool listContent);
	virtual bool decode(array<Byte>^ data,int% index) override;
	virtual array<Byte>^ encode() override;
	String^ getType();
	virtual String^ getShortDesc() override;
	virtual String^ getFullDesc() override;
};
