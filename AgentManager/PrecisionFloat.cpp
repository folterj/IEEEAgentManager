#include "StdAfx.h"
#include "PrecisionFloat.h"

PrecisionFloat::PrecisionFloat()
{
	value = 0;
	precision = 0;
}

PrecisionFloat::PrecisionFloat(float value0,int precision0)
{
	set(value0,precision0);
}

PrecisionFloat::PrecisionFloat(UInt16 val)
{
	set(val);
}

PrecisionFloat::PrecisionFloat(UInt32 val)
{
	set(val);
}

void PrecisionFloat::set(float value0,int precision0)
{
	value = value0;
	precision = precision0;
}

void PrecisionFloat::set(UInt16 val)
{
	set(val,0x1000,0x10);
}

void PrecisionFloat::set(UInt32 val)
{
	set(val,0x1000000,0x100);
}

void PrecisionFloat::set(UInt64 val,int valSize,int expSize)
{
	UInt64 val0 = (val & (valSize - 1));
	UInt64 exp = val / valSize;

	if (val0 & (valSize / 2)) {
		val0 = valSize - val0;
		value = -(float)val0;
	} else {
		value = (float)val0;
	}
	if (exp & (expSize / 2)) {
		exp = expSize - exp;
		precision = (int)exp;
	} else {
		precision = -(int)exp;
	}
	value /= (float)Math::Pow(10,precision);
}

UInt16 PrecisionFloat::getBasic()
{
	// convert to 16 bit precision float
	return (UInt16)getPFloat(0x1000,0x10);
}

UInt32 PrecisionFloat::getSimple()
{
	// convert to 32 bit precision float
	return (UInt32)getPFloat(0x1000000,0x100);
}

UInt64 PrecisionFloat::getPFloat(int valSize,int expSize)
{
	UInt64 val;
	UInt64 exp;
	int exp0 = -precision;

	if (exp0 > expSize) {
		exp0 = expSize;
	} else if (exp0 < -expSize) {
		exp0 = -expSize;
	}
	exp = exp0;
	val = (UInt64)Math::Round(value * Math::Pow(10,precision)) & (valSize - 1);
	val |= exp * valSize;

	return val;
}

String^ PrecisionFloat::ToString()
{
	String^ format = "{0:F" + precision + "}";
	return String::Format(format,value);
}
