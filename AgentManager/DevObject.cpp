#include "StdAfx.h"
#include "DevObject.h"
#include "nomenclature.h"
#include "phd_constants.h"
#include "util.h"

DevObject::DevObject()
{
	objectClass = 0;
	objectHandle = 0;
	compound = false;
}

DevAttribute^ DevObject::findAttribute(UInt16 id)
{
	for each (DevAttribute^ attribute in attributes) {
		if (attribute->id == id) {
			return attribute;
		}
	}
	return nullptr;
}

ArrayList^ DevObject::findMap()
{
	DevAttribute^ attribute = findAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	if (attribute) {
		return %attribute->map;
	}
	return nullptr;
}

ArrayList^ DevObject::findList()
{
	DevAttribute^ attribute = findAttribute(MDC_ATTR_ID_PHYSIO_LIST);
	if (attribute) {
		return %attribute->list;
	}
	return nullptr;
}

UInt32 DevObject::getType()
{
	DevAttribute^ attribute = findAttribute(MDC_ATTR_ID_TYPE);
	if (attribute) {
		return (UInt32)attribute->getVal();
	}
	return 0;
}

UInt32 DevObject::getUnit()
{
	DevAttribute^ attribute = findAttribute(MDC_ATTR_UNIT_CODE);
	if (attribute) {
		return (UInt32)attribute->getVal();
	}
	return 0;
}

// MDS

MdsObject::MdsObject(SpecType spectype,UInt16 configId,UInt64 eui)
{
	UInt16 sysType;
	//UInt16 configId;
	array<Byte>^ manmodel;
	String^ man = "Brunel";
	String^ model;

	objectHandle = 0;
	compound = false;

	switch (spectype) {
		case SpecType::Scales:
			sysType = MDC_DEV_SPEC_PROFILE_SCALE;
			model = "WS";
			break;
		case SpecType::BloodPressure:
			sysType = MDC_DEV_SPEC_PROFILE_BP;
			model = "BP";
			break;
		case SpecType::BloodGlucose:
			sysType = MDC_DEV_SPEC_PROFILE_GLUCOSE;
			model = "BG";
			break;
		case SpecType::PulseOxim:
			sysType = MDC_DEV_SPEC_PROFILE_PULS_OXIM;
			model = "SpO2";
			break;
		case SpecType::Motion:
			sysType = MDC_DEV_SPEC_PROFILE_AI_ACTIVITY_HUB;
			model = "Motion";
			break;
		case SpecType::Usage:
			sysType = MDC_DEV_SPEC_PROFILE_AI_ACTIVITY_HUB;
			model = "Usage";
			break;
		default:
			sysType = 0;
			model = "";
			break;
	}
	array<UInt16>^ configIdVal = {configId};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_DEV_CONFIG_ID,configIdVal));

	array<UInt16>^ specListVal = {1,4,sysType,1};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_SYS_TYPE_SPEC_LIST,specListVal));

	manmodel = manModelStringToBytes(man,model);
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_MODEL,manmodel));

	attributes.Add(gcnew DevAttribute(MDC_ATTR_SYS_ID,eui));

	//array<UInt16>^ timeInfo = {MDS_TIME_CAPAB_REAL_TIME_CLOCK | MDS_TIME_CAPAB_SET_CLOCK | MDS_TIME_CAPAB_BO_TIME |
	//							MDS_TIME_MGR_SET_TIME};
	array<UInt16>^ timeInfo = {MDS_TIME_CAPAB_REAL_TIME_CLOCK | MDS_TIME_CAPAB_BO_TIME};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_MDS_TIME_INFO,timeInfo));
}

// Scales

BodyWeightObject::BodyWeightObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 1;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_MASS_BODY_ACTUAL};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_KILO_G};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_SIMP,4);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

BodyHeightObject::BodyHeightObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 2;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_LEN_BODY_ACTUAL};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_CENTI_M};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_SIMP,4);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

BodyMassIndexObject::BodyMassIndexObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 3;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_RATIO_MASS_BODY_LEN_SQ};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_KG_PER_M_SQ};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_SIMP,4);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

BloodPressureObject::BloodPressureObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 1;
	compound = true;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_PRESS_BLD_NONINV};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valStruct = {MS_STRUCT_COMPOUND_FIX,3};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_STRUCT_SMALL,valStruct));

	DevAttribute^ list = gcnew DevAttribute(MDC_ATTR_ID_PHYSIO_LIST);
	list->listAdd(MDC_PRESS_BLD_NONINV_SYS);
	list->listAdd(MDC_PRESS_BLD_NONINV_DIA);
	list->listAdd(MDC_PRESS_BLD_NONINV_MEAN);
	attributes.Add(list);
	array<UInt16>^ valUnit = {MDC_DIM_MMHG};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_CMPD_VAL_OBS_BASIC,10);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

PulseRateObject::PulseRateObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 2;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_PULS_RATE_NON_INV};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_BEAT_PER_MIN};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_BASIC,2);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

BloodGlucoseObject::BloodGlucoseObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 1;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_CONC_GLU_CAPILLARY_WHOLEBLOOD};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_MILLI_MOLE_PER_L};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_BASIC,2);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

BloodGlucoseContextMealObject::BloodGlucoseContextMealObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 2;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_PHD_DM,MDC_CTXT_GLU_MEAL};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	map->mapAdd(MDC_ATTR_ENUM_OBS_VAL_SIMP_OID,2);
	attributes.Add(map);
}

BloodGlucoseContextExerciseObject::BloodGlucoseContextExerciseObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 3;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_PHD_DM,MDC_CTXT_GLU_EXERCISE};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_PERCENT};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	map->mapAdd(MDC_ATTR_TIME_PD_MSMT_ACTIVE,4);	// *** observation has only a single value
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_BASIC,2);		// *** how to store multiple values?
	attributes.Add(map);
}

PulseOximSatObject::PulseOximSatObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 1;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_PULS_OXIM_SAT_O2};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_PERCENT};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_BASIC,2);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

PulseOximPulseObject::PulseOximPulseObject()
{
	objectClass = MDC_MOC_VMO_METRIC_NU;
	objectHandle = 2;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_SCADA,MDC_PULS_OXIM_PULS_RATE};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	array<UInt16>^ valUnit = {MDC_DIM_BEAT_PER_MIN};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_UNIT_CODE,valUnit));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_NU_VAL_OBS_BASIC,2);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

MotionObject::MotionObject()
{
	objectClass = MDC_MOC_VMO_METRIC_ENUM;
	objectHandle = 1;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_PHD_AI,MDC_AI_TYPE_SENSOR_MOTION};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_ENUM_OBS_VAL_SIMP_BIT_STR,2);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}

UsageObject::UsageObject()
{
	objectClass = MDC_MOC_VMO_METRIC_ENUM;
	objectHandle = 1;
	compound = false;

	array<UInt16>^ valType = {MDC_PART_PHD_AI,MDC_AI_TYPE_SENSOR_USAGE};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_ID_TYPE,valType));

	array<UInt16>^ spec = {MSS_AVAIL_INTERMITTENT | MSS_AVAIL_STORED_DATA | MSS_UPD_APERIODIC | MSS_MSMT_APERIODIC |
							MSS_ACC_AGENT_INITIATED};
	attributes.Add(gcnew DevAttribute(MDC_ATTR_METRIC_SPEC_SMALL,spec));

	DevAttribute^ map = gcnew DevAttribute(MDC_ATTR_ATTRIBUTE_VAL_MAP);
	map->mapAdd(MDC_ATTR_ENUM_OBS_VAL_SIMP_BIT_STR,2);
	map->mapAdd(MDC_ATTR_TIME_STAMP_ABS,8);
	attributes.Add(map);
}
