#pragma once

using namespace System;
using namespace System::Collections;

ref class DevAttribute
{
public:
	UInt32 id;
	UInt32 len;
	array<UInt16>^ val;
	bool report;

	ArrayList map;
	ArrayList list;

	DevAttribute();
	DevAttribute(UInt32 id0);
	DevAttribute(UInt32 id0,UInt32 len0);
	DevAttribute(UInt32 id0,UInt64 eui64);
	DevAttribute(UInt32 id0,array<Byte>^ content0);
	DevAttribute(UInt32 id0,array<UInt16>^ content0);

	UInt64 getVal();
	UInt32 getLen();

	void clear();
	void mapAdd(UInt32 id0,UInt32 len0);
	void listAdd(UInt32 id0);
};
