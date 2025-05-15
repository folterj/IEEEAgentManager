#pragma once

#include "PrecisionFloat.h"
#include "SendState.h"

using namespace System;
using namespace System::Collections::Generic;


enum class ObservationType
{
	Numeric,
	Enum
};

ref class DevObservation
{
public:
	int objectHandle;
	ObservationType type;
	DateTimeOffset timeStamp;
	UInt32 value;
	List<UInt32> compoundValues;
	int valueSize;
	bool compound;
	int invokeId;
	int reportNo;
	SendState state;

	DevObservation();
	DevObservation(int objectHandle0);

	void set(UInt16 value0);
	void set(UInt32 value0);
	void setNum16(float value0,int precision0);
	void setNum32(float value0,int precision0);
	void setEnum(UInt16 value0);
	void setEnum(UInt32 value0);

	void addCompound(UInt16 value0);
	void addCompound(UInt32 value0);
	void addCompoundNum16(float value0,int precision0);
	void addCompoundNum32(float value0,int precision0);
	void addCompoundEnum(UInt16 value0);
	void addCompoundEnum(UInt32 value0);

	String^ ToString(UInt32 val,UInt16 codeType,bool fullTextConstants);
	virtual String^ ToString() override;
};
