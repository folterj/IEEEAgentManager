#include "StdAfx.h"
#include "DevAttribute.h"

DevAttribute::DevAttribute()
{
	clear();
}

DevAttribute::DevAttribute(UInt32 id0)
{
	clear();
	id = id0;
}

DevAttribute::DevAttribute(UInt32 id0,UInt32 len0)
{
	clear();
	id = id0;
	len = len0;
}

DevAttribute::DevAttribute(UInt32 id0,UInt64 eui64)
{
	UInt64 temp;

	clear();
	id = id0;
	len = 64 / 8;
	val = gcnew array<UInt16>(len/2);

	temp = eui64;
	for (int i=len/2-1;i>=0;i--) {
		val[i] = temp & 0xFFFF;
		temp /= 0x10000;
	}
}

DevAttribute::DevAttribute(UInt32 id0,array<Byte>^ val0)
{
	clear();
	id = id0;
	len = val0->Length;	// 1 byte elements
	val = gcnew array<UInt16>(len/2);
	for (unsigned int i=0;i<len/2;i++) {
		val[i] = val0[i*2] * 0x100 | val0[i*2+1];
	}
}

DevAttribute::DevAttribute(UInt32 id0,array<UInt16>^ val0)
{
	clear();
	id = id0;
	len = val0->Length * 2;	// 2 byte elements
	val = val0;	// * perform deep copy?
}

UInt64 DevAttribute::getVal()
{
	UInt64 val0 = 0;
	int mult = 1;

	if (val) {
		for (unsigned int i=0;i<len/2 && i<(unsigned int)val->Length;i++) {
			if (i > 0) {
				val0 *= 0x10000;
			}
			val0 |= val[i];
		}
	}
	return val0;
}

UInt32 DevAttribute::getLen()
{
	UInt32 totlen = len;
	for each (DevAttribute^ attr in map) {
		totlen += attr->len;
	}
	return totlen;
}

void DevAttribute::clear()
{
	id = 0;
	len = 0;
	val = gcnew array<UInt16>(0);
	report = false;
	map.Clear();
	list.Clear();
}

void DevAttribute::mapAdd(UInt32 id0,UInt32 len0)
{
	map.Add(gcnew DevAttribute(id0,len0));
}

void DevAttribute::listAdd(UInt32 id0)
{
	list.Add(gcnew DevAttribute(id0));
}
