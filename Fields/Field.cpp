#include "StdAfx.h"
#include "Field.h"

using namespace System::Reflection;

Field::Field()
{
	len = 0;
	val = gcnew array<Byte>(0);
}

Field::Field(int len0)
{
	setLen(len0);
}

int Field::getLen()
{
	return len;
}

void Field::setLen(int len0)
{
	len = len0;
	val = gcnew array<Byte>(len);
}

UInt64 Field::get()
{
	UInt64 val0;

	for (int i=0;i<len;i++) {
		val0 *= 0x100;
		if (i < val->Length) {
			val0 |= val[i];
		}
	}
	return val0;
}

array<UInt16>^ Field::get16array()
{
	array<UInt16>^ x = gcnew array<UInt16>(len / 2);
	Byte m,l;

	for (int i=0;i<len / 2;i++) {
		m = val[i*2];
		l = val[i*2+1];
		x[i] = l | (m * 0x100);
	}
	return x;
}

void Field::set(UInt64 val0)
{
	UInt64 val1 = val0;
	int valindex;

	for (int i=0;i<len;i++) {
		valindex = len-1 - i;
		if (valindex < val->Length) {
			val[valindex] = (val1 & 0xFF);
		}
		val1 /= 0x100;
	}
}

void Field::set(array<UInt16>^ val0)
{
	Byte m,l;
	int i = 0;

	for each (UInt16 x in val0) {
		m = x / 0x100;
		l = x & 0xFF;
		val[i++] = m;
		val[i++] = l;
	}
}

bool Field::decode(array<Byte>^ data,int% index)
{
	for (int i=0;i<len;i++) {
		if (i < val->Length && index + i < data->Length) {
			val[i] = data[index + i];
		}
	}
	index += len;

	return (index <= data->Length);
}

array<Byte>^ Field::encode()
{
	return val;
}

String^ Field::getShortDesc()
{
	String^ desc = "";

	for (int i=0;i<len;i++) {
		if (i < val->Length) {
			desc += String::Format("{0:X2}",val[i]);
		}
	}
	return desc;
}

String^ Field::getFullDesc()
{
	return getShortDesc();
}

array<Byte>^ Field::addData(array<Byte>^ data,array<Byte>^ add)
{
	int start = data->Length;
	int newlen = start + add->Length;
	Array::Resize(data,newlen);
	add->CopyTo(data,start);
	return data;
}
