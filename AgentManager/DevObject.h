#pragma once

#include "DevAttribute.h"
#include "SpecType.h"

using namespace System::Collections::Generic;

ref class DevObject
{
public:
	UInt16 objectClass;
	UInt16 objectHandle;
	List<DevAttribute^> attributes;
	bool compound;

	DevObject();

	DevAttribute^ findAttribute(UInt16 id);
	ArrayList^ findMap();
	ArrayList^ findList();
	UInt32 getType();
	UInt32 getUnit();
};

// MDS

ref class MdsObject : public DevObject
{
public:
	MdsObject(SpecType spectype,UInt16 configId,UInt64 eui);
};

// specialisation objects

ref class BodyWeightObject : public DevObject
{
public:
	BodyWeightObject();
};

ref class BodyHeightObject : public DevObject
{
public:
	BodyHeightObject();
};

ref class BodyMassIndexObject : public DevObject
{
public:
	BodyMassIndexObject();
};

ref class BloodPressureObject : public DevObject
{
public:
	BloodPressureObject();
};

ref class PulseRateObject : public DevObject
{
public:
	PulseRateObject();
};

ref class BloodGlucoseObject : public DevObject
{
public:
	BloodGlucoseObject();
};

ref class BloodGlucoseContextMealObject : public DevObject
{
public:
	BloodGlucoseContextMealObject();
};

ref class BloodGlucoseContextExerciseObject : public DevObject
{
public:
	BloodGlucoseContextExerciseObject();
};

ref class PulseOximSatObject : public DevObject
{
public:
	PulseOximSatObject();
};

ref class PulseOximPulseObject : public DevObject
{
public:
	PulseOximPulseObject();
};

ref class MotionObject : public DevObject
{
public:
	MotionObject();
};

ref class UsageObject : public DevObject
{
public:
	UsageObject();
};
