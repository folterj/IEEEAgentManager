#pragma once

#include "defines.h"
#include "TreeString.h"

using namespace System;

ref class Field
{
protected:
	array<Byte>^ val;
	int len;

public:
	Field();
	Field(int len0);

	int getLen();
	void setLen(int len0);

	UInt64 get();
	array<UInt16>^ get16array();
	void set(UInt64 val0);
	void set(array<UInt16>^ val0);

	virtual bool decode(array<Byte>^ data,int% index);
	virtual array<Byte>^ encode();
	virtual String^ getShortDesc();
	virtual String^ getFullDesc();

	array<Byte>^ addData(array<Byte>^ data,array<Byte>^ add);
};
