#include "StdAfx.h"
#include "DevSpec.h"
#include "phd_constants.h"
#include "nomenclature.h"

DevSpec::DevSpec()
{
	spectype = SpecType::None;
	configId = EXTENDED_CONFIG_START;
}

DevSpec::DevSpec(SpecType spectype0)
{
	spectype = spectype0;
	configId = EXTENDED_CONFIG_START;
}

DevSpec::DevSpec(SpecType spectype0,UInt16 configId0,UInt64 eui)
{
	spectype = spectype0;
	configId = configId0;

	objects.Add(gcnew MdsObject(spectype,configId,eui));
}

DevObject^ DevSpec::getMdsObject()
{
	return findObject(0);
}

DevObject^ DevSpec::findObject(UInt16 objectHandle)
{
	for each (DevObject^ object in objects.ToArray()) {
		if (object->objectHandle == objectHandle) {
			return object;
		}
	}
	return nullptr;
}

void DevSpec::addObject(DevObject^ devobject)
{
	DevObject^ object = findObject(devobject->objectHandle);
	if (object) {
		// delete object with same handle
		objects.Remove(object);
	}
	objects.Add(devobject);
}

// specialisations:

// Scales

ScalesSpec::ScalesSpec()
	: DevSpec(SpecType::Scales)
{
	initObjects();
}

ScalesSpec::ScalesSpec(UInt64 eui)
	: DevSpec(SpecType::Scales,STANDARD_CONFIG_SCALE,eui)
{
	initObjects();
}

void ScalesSpec::initObjects()
{
	objects.Add(gcnew BodyWeightObject());
	objects.Add(gcnew BodyHeightObject());
	objects.Add(gcnew BodyMassIndexObject());
}

// BP

BloodPressureSpec::BloodPressureSpec()
	: DevSpec(SpecType::BloodPressure)
{
	initObjects();
}

BloodPressureSpec::BloodPressureSpec(UInt64 eui)
	: DevSpec(SpecType::BloodPressure,STANDARD_CONFIG_BP,eui)
{
	initObjects();
}

void BloodPressureSpec::initObjects()
{
	objects.Add(gcnew BloodPressureObject());
	objects.Add(gcnew PulseRateObject());
}

// BG

BloodGlucoseSpec::BloodGlucoseSpec()
	: DevSpec(SpecType::BloodGlucose)
{
	initObjects();
}

BloodGlucoseSpec::BloodGlucoseSpec(UInt64 eui)
	: DevSpec(SpecType::BloodGlucose,STANDARD_CONFIG_GLUCOSE,eui)
{
	initObjects();
}

void BloodGlucoseSpec::initObjects()
{
	objects.Add(gcnew BloodGlucoseObject());
	objects.Add(gcnew BloodGlucoseContextMealObject());
	objects.Add(gcnew BloodGlucoseContextExerciseObject());
}

// PulseOxim

PulseOximSpec::PulseOximSpec()
	: DevSpec(SpecType::PulseOxim)
{
	initObjects();
}

PulseOximSpec::PulseOximSpec(UInt64 eui)
	: DevSpec(SpecType::PulseOxim,STANDARD_CONFIG_SPO2,eui)
{
	initObjects();
}

void PulseOximSpec::initObjects()
{
	objects.Add(gcnew PulseOximSatObject());
	objects.Add(gcnew PulseOximPulseObject());
}

// Motion

MotionSpec::MotionSpec()
	: DevSpec(SpecType::Motion)
{
	initObjects();
}

MotionSpec::MotionSpec(UInt64 eui)
	: DevSpec(SpecType::Motion,STANDARD_CONFIG_ILAH,eui)
{
	initObjects();
}

void MotionSpec::initObjects()
{
	objects.Add(gcnew MotionObject());
}

// Usage

UsageSpec::UsageSpec()
	: DevSpec(SpecType::Usage)
{
	initObjects();
}

UsageSpec::UsageSpec(UInt64 eui)
	: DevSpec(SpecType::Usage,STANDARD_CONFIG_ILAH,eui)
{
	initObjects();
}

void UsageSpec::initObjects()
{
	objects.Add(gcnew UsageObject());
}
