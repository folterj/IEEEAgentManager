#include "StdAfx.h"
#include "DevObservation.h"
#include "util.h"
#include "conversion.h"

DevObservation::DevObservation()
{
	objectHandle = 0;
	timeStamp = DateTimeOffset::Now;
	value = 0;
	compound = false;
	state = SendState::New;
	invokeId = 0;
	reportNo = 0;
}

DevObservation::DevObservation(int objectHandle0)
{
	objectHandle = objectHandle0;
	timeStamp = DateTimeOffset::Now;
	value = 0;
	compound = false;
	state = SendState::New;
	invokeId = 0;
	reportNo = 0;
}

void DevObservation::set(UInt16 value0)
{
	valueSize = 2;
	value = value0;
}

void DevObservation::set(UInt32 value0)
{
	valueSize = 4;
	value = value0;
}

void DevObservation::setNum16(float value0,int precision0)
{
	PrecisionFloat^ pfloat = gcnew PrecisionFloat(value0,precision0);
	type = ObservationType::Numeric;
	valueSize = 2;
	set(pfloat->getBasic());
}

void DevObservation::setNum32(float value0,int precision0)
{
	PrecisionFloat^ pfloat = gcnew PrecisionFloat(value0,precision0);
	type = ObservationType::Numeric;
	valueSize = 4;
	set(pfloat->getSimple());
}

void DevObservation::setEnum(UInt16 value0)
{
	type = ObservationType::Enum;
	set(value0);
}

void DevObservation::setEnum(UInt32 value0)
{
	type = ObservationType::Enum;
	set(value0);
}

void DevObservation::addCompound(UInt16 value0)
{
	compound = true;
	valueSize = 2;
	compoundValues.Add(value0);
}

void DevObservation::addCompound(UInt32 value0)
{
	compound = true;
	valueSize = 4;
	compoundValues.Add(value0);
}

void DevObservation::addCompoundNum16(float value0,int precision0)
{
	PrecisionFloat^ pfloat = gcnew PrecisionFloat(value0,precision0);
	type = ObservationType::Numeric;
	addCompound(pfloat->getBasic());
}

void DevObservation::addCompoundNum32(float value0,int precision0)
{
	PrecisionFloat^ pfloat = gcnew PrecisionFloat(value0,precision0);
	type = ObservationType::Numeric;
	addCompound(pfloat->getSimple());
}

void DevObservation::addCompoundEnum(UInt16 value0)
{
	type = ObservationType::Enum;
	addCompound(value0);
}

void DevObservation::addCompoundEnum(UInt32 value0)
{
	type = ObservationType::Enum;
	addCompound(value0);
}

String^ DevObservation::ToString(UInt32 val,UInt16 codeType,bool fullTextConstants)
{
	String^ s = "";
	String^ codetext;
	PrecisionFloat^ pfloat;
	UInt32 x;
	int biti;

	if (type == ObservationType::Enum) {
		// enum
		x = value;
		biti = 0;
		while (x != 0) {
			if (x & 1) {
				if (s != "") {
					s += ",";
				}
				if (fullTextConstants) {
					codetext = getFlagText(biti,codeType);
				} else {
					codetext = "";
				}
				s += String::Format("{0}^{1}({2})",1,codetext,biti);
			}
			x /= 2;
			biti++;
		}
	} else {
		// numeric
		if (valueSize == 2) {
			pfloat = gcnew PrecisionFloat((UInt16)val);
		} else {
			pfloat = gcnew PrecisionFloat(val);
		}
		s += pfloat->ToString();
	}
	return s;
}

String^ DevObservation::ToString()
{
	String^ s = "";	//toString(timeStamp) + "\n";

	if (compound) {
		for each (UInt32 val in compoundValues) {
			s += ToString(val,0,true) + "\n";
		}
	} else {
		s += ToString(value,0,true) + "\n";
	}
	return s;
}
