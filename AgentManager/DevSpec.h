#pragma once

#include "DevObject.h"
#include "SpecType.h"

ref class DevSpec
{
public:
	SpecType spectype;
	UInt16 configId;
	List<DevObject^> objects;

	DevSpec();
	DevSpec(SpecType spectype0);
	DevSpec(SpecType spectype0,UInt16 configId0,UInt64 eui);

	DevObject^ getMdsObject();
	DevObject^ findObject(UInt16 objectHandle);
	void addObject(DevObject^ object);
};

// specialisations

ref class ScalesSpec : public DevSpec
{
public:
	ScalesSpec();
	ScalesSpec(UInt64 eui);
	void initObjects();
};

ref class BloodPressureSpec : public DevSpec
{
public:
	BloodPressureSpec();
	BloodPressureSpec(UInt64 eui);
	void initObjects();
};

ref class BloodGlucoseSpec : public DevSpec
{
public:
	BloodGlucoseSpec();
	BloodGlucoseSpec(UInt64 eui);
	void initObjects();
};

ref class PulseOximSpec : public DevSpec
{
public:
	PulseOximSpec();
	PulseOximSpec(UInt64 eui);
	void initObjects();
};

ref class MotionSpec : public DevSpec
{
public:
	MotionSpec();
	MotionSpec(UInt64 eui);
	void initObjects();
};

ref class UsageSpec : public DevSpec
{
public:
	UsageSpec();
	UsageSpec(UInt64 eui);
	void initObjects();
};
