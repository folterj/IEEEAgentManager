
#include "stdafx.h"
#include "conversion.h"
#include "phd_constants.h"
#include "nomenclature.h"
#include "defines.h"


String^ apduChoice(int choice) {
	String^ s = "";
	switch (choice) {
		case AARQ_CHOSEN:	s = "AARQ";								break;
		case AARE_CHOSEN:	s = "AARE";								break;
		case RLRQ_CHOSEN:	s = "RLRQ";								break;
		case RLRE_CHOSEN:	s = "RLRE";								break;
		case ABRT_CHOSEN:	s = "ABRT";								break;
		case PRST_CHOSEN:	s = "PRST";								break;

		default:			s = String::Format("{0:X4}",choice);	break;
	}
	return s;
}

String^ acseChoice(int choice) {
	String^ s = "";
	switch (choice) {
		case ROIV_CMIP_EVENT_REPORT_CHOSEN:				s = "ROIV_CMIP_EVENT_REPORT";			break;
		case ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN:	s = "ROIV_CMIP_CONFIRMED_EVENT_REPORT";	break;
		case ROIV_CMIP_GET_CHOSEN:						s = "ROIV_CMIP_GET";					break;
		case ROIV_CMIP_SET_CHOSEN:						s = "ROIV_CMIP_SET";					break;
		case ROIV_CMIP_CONFIRMED_SET_CHOSEN:			s = "ROIV_CMIP_CONFIRMED_SET";			break;
		case ROIV_CMIP_ACTION_CHOSEN:					s = "ROIV_CMIP_ACTION";					break;
		case ROIV_CMIP_CONFIRMED_ACTION_CHOSEN:			s = "ROIV_CMIP_CONFIRMED_ACTION";		break;
		case RORS_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN:	s = "RORS_CMIP_CONFIRMED_EVENT_REPORT";	break;
		case RORS_CMIP_GET_CHOSEN:						s = "RORS_CMIP_GET";					break;
		case RORS_CMIP_CONFIRMED_SET_CHOSEN:			s = "RORS_CMIP_CONFIRMED_SET";			break;
		case RORS_CMIP_CONFIRMED_ACTION_CHOSEN:			s = "RORS_CMIP_CONFIRMED_ACTION";		break;
		case ROER_CHOSEN:								s = "ROER";								break;
		case RORJ_CHOSEN:								s = "RORJ";								break;

		default:										s = String::Format("{0:X4}",choice);	break;
	}
	return s;
}

String^ roseChoice(int choice) {
	String^ s = "";
	switch (choice) {
		case MDC_NOTI_CONFIG:						s = "NOTI_CONFIG";							break;
		case MDC_NOTI_SCAN_REPORT_FIXED:			s = "NOTI_SCAN_REPORT_FIXED";				break;
		case MDC_NOTI_SCAN_REPORT_VAR:				s = "NOTI_SCAN_REPORT_VAR";					break;
		case MDC_NOTI_SCAN_REPORT_MP_FIXED:			s = "NOTI_SCAN_REPORT_MP_FIXED";			break;
		case MDC_NOTI_SCAN_REPORT_MP_VAR:			s = "NOTI_SCAN_REPORT_MP_VAR";				break;
		case MDC_NOTI_SEGMENT_DATA:					s = "NOTI_SEGMENT_DATA";					break;
		case MDC_NOTI_UNBUF_SCAN_REPORT_VAR:		s = "NOTI_UNBUF_SCAN_REPORT_VAR";			break;
		case MDC_NOTI_UNBUF_SCAN_REPORT_FIXED:		s = "NOTI_UNBUF_SCAN_REPORT_FIXED";			break;
		case MDC_NOTI_UNBUF_SCAN_REPORT_GROUPED:	s = "NOTI_UNBUF_SCAN_REPORT_GROUPED";		break;
		case MDC_NOTI_UNBUF_SCAN_REPORT_MP_VAR:		s = "NOTI_UNBUF_SCAN_REPORT_MP_VAR";		break;
		case MDC_NOTI_UNBUF_SCAN_REPORT_MP_FIXED:	s = "NOTI_UNBUF_SCAN_REPORT_MP_FIXED";		break;
		case MDC_NOTI_UNBUF_SCAN_REPORT_MP_GROUPED:	s = "NOTI_UNBUF_SCAN_REPORT_MP_GROUPED";	break;
		case MDC_NOTI_BUF_SCAN_REPORT_VAR:			s = "NOTI_BUF_SCAN_REPORT_VAR";				break;
		case MDC_NOTI_BUF_SCAN_REPORT_FIXED:		s = "NOTI_BUF_SCAN_REPORT_FIXED";			break;
		case MDC_NOTI_BUF_SCAN_REPORT_GROUPED:		s = "NOTI_BUF_SCAN_REPORT_GROUPED";			break;
		case MDC_NOTI_BUF_SCAN_REPORT_MP_VAR:		s = "NOTI_BUF_SCAN_REPORT_MP_VAR";			break;
		case MDC_NOTI_BUF_SCAN_REPORT_MP_FIXED:		s = "NOTI_BUF_SCAN_REPORT_MP_FIXED";		break;
		case MDC_NOTI_BUF_SCAN_REPORT_MP_GROUPED:	s = "NOTI_BUF_SCAN_REPORT_MP_GROUPED";		break;

		default:									s = String::Format("{0:X4}",choice);		break;
	}
	return s;
}

String^ actionType(int action) {
	String^ s = "";
	switch (action) {
		case MDC_ACT_SEG_CLR:		s = "SEG_CLR";							break;
		case MDC_ACT_SEG_GET_INFO:	s = "SEG_GET_INFO";						break;
		case MDC_ACT_SET_TIME:		s = "SET_TIME";							break;
		case MDC_ACT_DATA_REQUEST:	s = "DATA_REQUEST";						break;
		case MDC_ACT_SEG_TRIG_XFER:	s = "SEG_TRIG_XFER";					break;
		case MDC_ACT_SET_BO_TIME:	s = "SET_BO_TIME";						break;

		default:					s = String::Format("{0:X4}",action);	break;
	}
	return s;
}

String^ objClass(UInt16 objclass) {
	String^ s = "";
	switch (objclass) {
		case MDC_MOC_VMO_METRIC:				s = "METRIC";				break;
		case MDC_MOC_VMO_METRIC_ENUM:			s = "METRIC_ENUM";			break;
		case MDC_MOC_VMO_METRIC_NU:				s = "METRIC_NU";			break;
		case MDC_MOC_VMO_METRIC_SA_RT:			s = "METRIC_SA_RT";			break;
		case MDC_MOC_SCAN:						s = "SCAN";					break;
		case MDC_MOC_SCAN_CFG:					s = "SCAN_CFG";				break;
		case MDC_MOC_SCAN_CFG_EPI:				s = "SCAN_CFG_EPI";			break;
		case MDC_MOC_SCAN_CFG_PERI:				s = "SCAN_CFG_PERI";		break;
		case MDC_MOC_VMS_MDS_SIMP:				s = "VMS_MDS_SIMP";			break;
		case MDC_MOC_VMO_PMSTORE:				s = "VMO_PMSTORE";			break;
		case MDC_MOC_PM_SEGMENT:				s = "PM_SEGMENT";			break;

		default:								s = objclass.ToString();	break;
	}
	return s;
}

String^ attrId(UInt16 id) {
	String^ s = "";
	switch (id) {
		case MDC_ATTR_SOURCE_HANDLE_REF:		s = "SOURCE_HANDLE_REF";			break;
		case MDC_ATTR_SYS_ID:					s = "SYS_ID";						break;
		case MDC_ATTR_SYS_TYPE:					s = "SYS_TYPE";						break;
		case MDC_ATTR_SYS_TYPE_SPEC_LIST:		s = "SYS_TYPE_SPEC_LIST";			break;
		case MDC_ATTR_UNIT_CODE:				s = "UNIT_CODE";					break;
		case MDC_ATTR_ID_MODEL:					s = "ID_MODEL";						break;
		case MDC_ATTR_ID_PHYSIO:				s = "ID_PHYSIO";					break;
		case MDC_ATTR_ID_PROD_SPECN:			s = "ID_PROD_SPECN";				break;
		case MDC_ATTR_ID_TYPE:					s = "ID_TYPE";						break;
		case MDC_ATTR_ID_PHYSIO_LIST:			s = "ID_PHYSIO_LIST";				break;

		case MDC_ATTR_TIME_ABS:					s = "TIME_ABS";						break;
		case MDC_ATTR_TIME_REL:					s = "TIME_REL";						break;
		case MDC_ATTR_TIME_BO:					s = "TIME_BO";						break;
		case MDC_ATTR_TIME_STAMP_ABS:			s = "TIME_STAMP_ABS";				break;
		case MDC_ATTR_TIME_STAMP_REL:			s = "TIME_STAMP_REL";				break;
		case MDC_ATTR_TIME_STAMP_BO:			s = "TIME_STAMP_BO";				break;
		case MDC_ATTR_TIME_START_SEG:			s = "TIME_START_SEG";				break;
		case MDC_ATTR_TIME_START_SEG_BO:		s = "TIME_START_SEG_BO";			break;
		case MDC_ATTR_TIME_END_SEG:				s = "TIME_END_SEG";					break;
		case MDC_ATTR_TIME_END_SEG_BO:			s = "TIME_END_SEG_BO";				break;
		case MDC_ATTR_TIME_REL_HI_RES:			s = "TIME_REL_HI_RES";				break;
		case MDC_ATTR_TIME_STAMP_REL_HI_RES:	s = "TIME_STAMP_REL_HI_RES";		break;
		case MDC_ATTR_TIME_PD_MSMT_ACTIVE:		s = "TIME_PD_MSMT_ACTIVE";			break;

		case MDC_ATTR_ATTRIBUTE_VAL_MAP:			s = "ATTRIBUTE_VAL_MAP";			break;
		case MDC_ATTR_DEV_CONFIG_ID:				s = "DEV_CONFIG_ID";				break;
		case MDC_ATTR_MDS_TIME_INFO:				s = "MDS_TIME_INFO";				break;
		case MDC_ATTR_METRIC_SPEC_SMALL:			s = "METRIC_SPEC_SMALL";			break;
		case MDC_ATTR_NU_VAL_OBS_BASIC:				s = "NU_VAL_OBS_BASIC";				break;
		case MDC_ATTR_NU_VAL_OBS_SIMP:				s = "NU_VAL_OBS_SIMP";				break;
		case MDC_ATTR_NU_CMPD_VAL_OBS_SIMP:			s = "NU_CMPD_VAL_OBS_SIMP";			break;
		case MDC_ATTR_NU_CMPD_VAL_OBS_BASIC:		s = "NU_CMPD_VAL_OBS_BASIC";		break;
		case MDC_ATTR_VAL_ENUM_OBS:					s = "VAL_ENUM_OBS";					break;
		case MDC_ATTR_ENUM_OBS_VAL_SIMP_OID:		s = "ENUM_OBS_VAL_SIMP_OID";		break;
		case MDC_ATTR_ENUM_OBS_VAL_SIMP_STR:		s = "ENUM_OBS_VAL_SIMP_STR";		break;
		case MDC_ATTR_ENUM_OBS_VAL_SIMP_BIT_STR:	s = "ENUM_OBS_VAL_SIMP_BIT_STR";	break;
		case MDC_ATTR_ENUM_OBS_VAL_BASIC_BIT_STR:	s = "ENUM_OBS_VAL_BASIC_BIT_STR";	break;
		case MDC_ATTR_METRIC_STRUCT_SMALL:			s = "METRIC_STRUCT_SMALL";			break;

		case MDC_PULS_RATE_NON_INV:				s = "PULS_RATE_NON_INV";			break;
		case MDC_PRESS_BLD_NONINV:				s = "PRESS_BLD_NONINV";				break;
		case MDC_PRESS_BLD_NONINV_SYS:			s = "PRESS_BLD_NONINV_SYS";			break;
		case MDC_PRESS_BLD_NONINV_DIA:			s = "PRESS_BLD_NONINV_DIA";			break;
		case MDC_PRESS_BLD_NONINV_MEAN:			s = "PRESS_BLD_NONINV_MEAN";		break;
		case MDC_TEMP_BODY:						s = "TEMP_BODY";					break;
		case MDC_PULS_OXIM_PULS_RATE:			s = "PULS_OXIM_PULS_RATE";			break;
		case MDC_SAT_O2_QUAL:					s = "SAT_O2_QUAL";					break;
		case MDC_PULS_OXIM_PERF_REL:			s = "PULS_OXIM_PERF_REL";			break;
		case MDC_PULS_OXIM_PLETH:				s = "PULS_OXIM_PLETH";				break;
		case MDC_PULS_OXIM_SAT_O2:				s = "PULS_OXIM_SAT_O2";				break;
		case MDC_PULS_OXIM_PULS_CHAR:			s = "PULS_OXIM_PULS_CHAR";			break;
		case MDC_PULS_OXIM_DEV_STATUS:			s = "PULS_OXIM_DEV_STATUS";			break;
		case MDC_MASS_BODY_ACTUAL:				s = "MASS_BODY_ACTUAL";				break;
		case MDC_BODY_FAT:						s = "BODY_FAT";						break;
		case MDC_LEN_BODY_ACTUAL:				s = "LEN_BODY_ACTUAL";				break;
		case MDC_RATIO_MASS_BODY_LEN_SQ:		s = "RATIO_MASS_BODY_LEN_SQ";		break;

		default:								s = String::Format("{0:X4}",id);	break;
	}
	return s;
}

String^ partId(UInt16 id) {
	String^ s = "";
	switch (id) {
		case MDC_PART_OBJ:						s = "OBJ";							break;
		case MDC_PART_SCADA:					s = "SCADA";						break;
		case MDC_PART_ALERT:					s = "ALERT";						break;
		case MDC_PART_DIM:						s = "DIM";							break;
		case MDC_PART_VATTR:					s = "VATTR";						break;
		case MDC_PART_PGRP:						s = "PGRP";							break;
		case MDC_PART_SITES:					s = "SITES";						break;
		case MDC_PART_FEF:						s = "FEF";							break;
		case MDC_PART_ECG_EXTN:					s = "ECG_EXTN";						break;
		case MDC_PART_IDCO_EXTN:				s = "IDCO_EXTN";					break;
		case MDC_PART_PHD_DM:					s = "PHD_DM";						break;
		case MDC_PART_PHD_HF:					s = "PHD_HF";						break;
		case MDC_PART_PHD_AI:					s = "PHD_AI";						break;
		case MDC_PART_RET_CODE:					s = "RET_CODE";						break;
		case MDC_PART_EXT_NOM:					s = "EXT_NOM";						break;
		case MDC_PART_PRIV:						s = "PRIV";							break;

		default:								s = String::Format("{0:X4}",id);	break;
	}
	return s;
}

String^ typeId(UInt16 id) {
	String^ s = "";
	switch (id) {
		case MDC_PULS_RATE_NON_INV:				s = "PULS_RATE_NON_INV";				break;
		case MDC_PRESS_BLD_NONINV:				s = "PRESS_BLD_NONINV";					break;
		case MDC_PRESS_BLD_NONINV_SYS:			s = "PRESS_BLD_NONINV_SYS";				break;
		case MDC_PRESS_BLD_NONINV_DIA:			s = "PRESS_BLD_NONINV_DIA";				break;
		case MDC_PRESS_BLD_NONINV_MEAN:			s = "PRESS_BLD_NONINV_MEAN";			break;

		case MDC_TEMP_BODY:						s = "TEMP_BODY";						break;
		case MDC_PULS_OXIM_PULS_RATE:			s = "PULS_OXIM_PULS_RATE";				break;
		case MDC_SAT_O2_QUAL:					s = "SAT_O2_QUAL";						break;
		case MDC_PULS_OXIM_PERF_REL:			s = "PULS_OXIM_PERF_REL";				break;
		case MDC_PULS_OXIM_PLETH:				s = "PULS_OXIM_PLETH";					break;
		case MDC_PULS_OXIM_SAT_O2:				s = "PULS_OXIM_SAT_O2";					break;
		case MDC_PULS_OXIM_PULS_CHAR:			s = "PULS_OXIM_PULS_CHAR";				break;
		case MDC_PULS_OXIM_DEV_STATUS:			s = "PULS_OXIM_DEV_STATUS";				break;

		case MDC_MASS_BODY_ACTUAL:				s = "MASS_BODY_ACTUAL";					break;
		case MDC_BODY_FAT:						s = "BODY_FAT";							break;
		case MDC_LEN_BODY_ACTUAL:				s = "LEN_BODY_ACTUAL";					break;
		case MDC_RATIO_MASS_BODY_LEN_SQ:		s = "RATIO_MASS_BODY_LEN_SQ";			break;
		
		case MDC_CONC_GLU_GEN:					s = "CONC_GLU_GEN";						break;
		case MDC_CONC_GLU_CAPILLARY_WHOLEBLOOD:	s = "CONC_GLU_CAPILLARY_WHOLEBLOOD";	break;
		case MDC_CONC_GLU_CAPILLARY_PLASMA:		s = "CONC_GLU_CAPILLARY_PLASMA";		break;
		case MDC_CONC_GLU_VENOUS_WHOLEBLOOD:	s = "CONC_GLU_VENOUS_WHOLEBLOOD";		break;
		case MDC_CONC_GLU_VENOUS_PLASMA:		s = "CONC_GLU_VENOUS_PLASMA";			break;
		case MDC_CONC_GLU_ARTERIAL_WHOLEBLOOD:	s = "CONC_GLU_ARTERIAL_WHOLEBLOOD";		break;
		case MDC_CONC_GLU_ARTERIAL_PLASMA:		s = "CONC_GLU_ARTERIAL_PLASMA";			break;
		case MDC_CONC_GLU_CONTROL:				s = "CONC_GLU_CONTROL";					break;
		case MDC_CONC_GLU_ISF:					s = "CONC_GLU_ISF";						break;
		case MDC_CONC_HBA1C:					s = "CONC_HBA1C";						break;

		case MDC_TRIG:							s = "TRIG";								break;
		case MDC_TRIG_BEAT:						s = "TRIG_BEAT";						break;
		case MDC_TRIG_BEAT_MAX_INRUSH:			s = "TRIG_BEAT_MAX_INRUSH";				break;
		case MDC_METRIC_NOS:					s = "METRIC_NOS";						break;
		case MDC_MODALITY_FAST:					s = "MODALITY_FAST";					break;
//		case MDC_MODALITY_SLOW:					s = "MODALITY_SLOW";					break;
		case MDC_MODALITY_SPOT:					s = "MODALITY_SPOT";					break;

		case MDC_AI_TYPE_SENSOR_FALL:			s = "SENSOR_FALL";						break;
		case MDC_AI_TYPE_SENSOR_PERS:			s = "SENSOR_PERS";						break;
		case MDC_AI_TYPE_SENSOR_SMOKE:			s = "SENSOR_SMOKE";						break;
		case MDC_AI_TYPE_SENSOR_CO:				s = "SENSOR_CO";						break;
		case MDC_AI_TYPE_SENSOR_WATER:			s = "SENSOR_WATER";						break;
		case MDC_AI_TYPE_SENSOR_GAS:			s = "SENSOR_GAS";						break;
		case MDC_AI_TYPE_SENSOR_MOTION:			s = "SENSOR_MOTION";					break;
		case MDC_AI_TYPE_SENSOR_PROPEXIT:		s = "SENSOR_PROPEXIT";					break;
		case MDC_AI_TYPE_SENSOR_ENURESIS:		s = "SENSOR_ENURESIS";					break;
		case MDC_AI_TYPE_SENSOR_CONTACTCLOSURE:	s = "SENSOR_CONTACTCLOSURE";			break;
		case MDC_AI_TYPE_SENSOR_USAGE:			s = "SENSOR_USAGE";						break;
		case MDC_AI_TYPE_SENSOR_SWITCH:			s = "SENSOR_SWITCH";					break;
		case MDC_AI_TYPE_SENSOR_DOSAGE:			s = "SENSOR_DOSAGE";					break;
		case MDC_AI_TYPE_SENSOR_TEMP:			s = "SENSOR_TEMP";						break;
		case MDC_AI_TYPE_SENSOR_HUMIDITY:		s = "SENSOR_HUMIDITY";					break;

		case MDC_CTXT_GLU_MEAL:					s = "GLU_MEAL";							break;
		case MDC_CTXT_GLU_EXERCISE:				s = "GLU_EXERCISE";						break;

		default:								s = String::Format("{0:X4}",id);		break;
	}
	return s;
}

String^ typeIdFull(UInt16 id) {
	String^ s = "";
	switch (id) {
		case MDC_PULS_RATE_NON_INV:				s = "MDC_PULS_RATE_NON_INV";				break;
		case MDC_PRESS_BLD_NONINV:				s = "MDC_PRESS_BLD_NONINV";					break;
		case MDC_PRESS_BLD_NONINV_SYS:			s = "MDC_PRESS_BLD_NONINV_SYS";				break;
		case MDC_PRESS_BLD_NONINV_DIA:			s = "MDC_PRESS_BLD_NONINV_DIA";				break;
		case MDC_PRESS_BLD_NONINV_MEAN:			s = "MDC_PRESS_BLD_NONINV_MEAN";			break;

		case MDC_TEMP_BODY:						s = "MDC_TEMP_BODY";						break;
		case MDC_PULS_OXIM_PULS_RATE:			s = "MDC_PULS_OXIM_PULS_RATE";				break;
		case MDC_SAT_O2_QUAL:					s = "MDC_SAT_O2_QUAL";						break;
		case MDC_PULS_OXIM_PERF_REL:			s = "MDC_PULS_OXIM_PERF_REL";				break;
		case MDC_PULS_OXIM_PLETH:				s = "MDC_PULS_OXIM_PLETH";					break;
		case MDC_PULS_OXIM_SAT_O2:				s = "MDC_PULS_OXIM_SAT_O2";					break;
		case MDC_PULS_OXIM_PULS_CHAR:			s = "MDC_PULS_OXIM_PULS_CHAR";				break;
		case MDC_PULS_OXIM_DEV_STATUS:			s = "MDC_PULS_OXIM_DEV_STATUS";				break;

		case MDC_MASS_BODY_ACTUAL:				s = "MDC_MASS_BODY_ACTUAL";					break;
		case MDC_BODY_FAT:						s = "MDC_BODY_FAT";							break;
		case MDC_LEN_BODY_ACTUAL:				s = "MDC_LEN_BODY_ACTUAL";					break;
		case MDC_RATIO_MASS_BODY_LEN_SQ:		s = "MDC_RATIO_MASS_BODY_LEN_SQ";			break;
		
		case MDC_CONC_GLU_GEN:					s = "MDC_CONC_GLU_GEN";						break;
		case MDC_CONC_GLU_CAPILLARY_WHOLEBLOOD:	s = "MDC_CONC_GLU_CAPILLARY_WHOLEBLOOD";	break;
		case MDC_CONC_GLU_CAPILLARY_PLASMA:		s = "MDC_CONC_GLU_CAPILLARY_PLASMA";		break;
		case MDC_CONC_GLU_VENOUS_WHOLEBLOOD:	s = "MDC_CONC_GLU_VENOUS_WHOLEBLOOD";		break;
		case MDC_CONC_GLU_VENOUS_PLASMA:		s = "MDC_CONC_GLU_VENOUS_PLASMA";			break;
		case MDC_CONC_GLU_ARTERIAL_WHOLEBLOOD:	s = "MDC_CONC_GLU_ARTERIAL_WHOLEBLOOD";		break;
		case MDC_CONC_GLU_ARTERIAL_PLASMA:		s = "MDC_CONC_GLU_ARTERIAL_PLASMA";			break;
		case MDC_CONC_GLU_CONTROL:				s = "MDC_CONC_GLU_CONTROL";					break;
		case MDC_CONC_GLU_ISF:					s = "MDC_CONC_GLU_ISF";						break;
		case MDC_CONC_HBA1C:					s = "MDC_CONC_HBA1C";						break;

		case MDC_TRIG:							s = "MDC_TRIG";								break;
		case MDC_TRIG_BEAT:						s = "MDC_TRIG_BEAT";						break;
		case MDC_TRIG_BEAT_MAX_INRUSH:			s = "MDC_TRIG_BEAT_MAX_INRUSH";				break;
		case MDC_METRIC_NOS:					s = "MDC_METRIC_NOS";						break;
		case MDC_MODALITY_FAST:					s = "MDC_MODALITY_FAST";					break;
//		case MDC_MODALITY_SLOW:					s = "MDC_MODALITY_SLOW";					break;
		case MDC_MODALITY_SPOT:					s = "MDC_MODALITY_SPOT";					break;

		case MDC_AI_TYPE_SENSOR_FALL:			s =  "MDC_AI_TYPE_SENSOR_FALL";				break;
		case MDC_AI_TYPE_SENSOR_PERS:			s =  "MDC_AI_TYPE_SENSOR_PERS";				break;
		case MDC_AI_TYPE_SENSOR_SMOKE:			s =  "MDC_AI_TYPE_SENSOR_SMOKE";			break;
		case MDC_AI_TYPE_SENSOR_CO:				s =  "MDC_AI_TYPE_SENSOR_CO";				break;
		case MDC_AI_TYPE_SENSOR_WATER:			s =  "MDC_AI_TYPE_SENSOR_WATER";			break;
		case MDC_AI_TYPE_SENSOR_GAS:			s =  "MDC_AI_TYPE_SENSOR_GAS";				break;
		case MDC_AI_TYPE_SENSOR_MOTION:			s =  "MDC_AI_TYPE_SENSOR_MOTION";			break;
		case MDC_AI_TYPE_SENSOR_PROPEXIT:		s =  "MDC_AI_TYPE_SENSOR_PROPEXIT";			break;
		case MDC_AI_TYPE_SENSOR_ENURESIS:		s =  "MDC_AI_TYPE_SENSOR_ENURESIS";			break;
		case MDC_AI_TYPE_SENSOR_CONTACTCLOSURE:	s =  "MDC_AI_TYPE_SENSOR_CONTACTCLOSURE";	break;
		case MDC_AI_TYPE_SENSOR_USAGE:			s =  "MDC_AI_TYPE_SENSOR_USAGE";			break;
		case MDC_AI_TYPE_SENSOR_SWITCH:			s =  "MDC_AI_TYPE_SENSOR_SWITCH";			break;
		case MDC_AI_TYPE_SENSOR_DOSAGE:			s =  "MDC_AI_TYPE_SENSOR_DOSAGE";			break;
		case MDC_AI_TYPE_SENSOR_TEMP:			s =  "MDC_AI_TYPE_SENSOR_TEMP";				break;
		case MDC_AI_TYPE_SENSOR_HUMIDITY:		s =  "MDC_AI_TYPE_SENSOR_HUMIDITY";			break;
	}
	return s;
}

String^ unitId(UInt16 id) {
	String^ s = "";
	switch(id) {
		case MDC_DIM_PERCENT:					s = "PERCENT";						break;
		case MDC_DIM_KILO_G:					s = "KILO_G";						break;
		case MDC_DIM_MIN:						s = "MIN";							break;
		case MDC_DIM_HR:						s = "HR";							break;
		case MDC_DIM_DAY:						s = "DAY";							break;
		case MDC_DIM_DEGC:						s = "DEGC";							break;
		case MDC_DIM_MILLI_L:					s = "MILLI_L";						break;
		case MDC_DIM_MILLI_G:					s = "MILLI_G";						break;
		case MDC_DIM_MILLI_G_PER_DL:			s = "MILLI_G_PER_DL";				break;
		case MDC_DIM_MILLI_MOLE_PER_L:			s = "MILLI_MOLE_PER_L";				break;
		case MDC_DIM_INTL_UNIT:					s = "INTL_UNIT";					break;
		case MDC_DIM_X_G:						s = "X_G";							break;
		case MDC_DIM_BEAT_PER_MIN:				s = "BEAT_PER_MIN";					break;
		case MDC_DIM_KILO_PASCAL:				s = "KILO_PASCAL";					break;
		case MDC_DIM_MMHG:						s = "MMHG";							break;
		case MDC_DIM_CENTI_M:					s = "CENTI_M";						break;
		case MDC_DIM_INCH:						s = "INCH";							break;
		case MDC_DIM_LB:						s = "LB";							break;
		case MDC_DIM_KG_PER_M_SQ:				s = "KG_PER_M_SQ";					break;

		default:								s = String::Format("{0:X4}",id);	break;
	}
	return s;
}

String^ unitIdFull(UInt16 id) {
	String^ s = "";
	switch(id) {
		case MDC_DIM_PERCENT:					s = "MDC_DIM_PERCENT";				break;
		case MDC_DIM_KILO_G:					s = "MDC_DIM_KILO_G";				break;
		case MDC_DIM_MIN:						s = "MDC_DIM_MIN";					break;
		case MDC_DIM_HR:						s = "MDC_DIM_HR";					break;
		case MDC_DIM_DAY:						s = "MDC_DIM_DAY";					break;
		case MDC_DIM_DEGC:						s = "MDC_DIM_DEGC";					break;
		case MDC_DIM_MILLI_L:					s = "MDC_DIM_MILLI_L";				break;
		case MDC_DIM_MILLI_G:					s = "MDC_DIM_MILLI_G";				break;
		case MDC_DIM_MILLI_G_PER_DL:			s = "MDC_DIM_MILLI_G_PER_DL";		break;
		case MDC_DIM_MILLI_MOLE_PER_L:			s = "MDC_DIM_MILLI_MOLE_PER_L";		break;
		case MDC_DIM_INTL_UNIT:					s = "MDC_DIM_INTL_UNIT";			break;
		case MDC_DIM_X_G:						s = "MDC_DIM_X_G";					break;
		case MDC_DIM_BEAT_PER_MIN:				s = "MDC_DIM_BEAT_PER_MIN";			break;
		case MDC_DIM_KILO_PASCAL:				s = "MDC_DIM_KILO_PASCAL";			break;
		case MDC_DIM_MMHG:						s = "MDC_DIM_MMHG";					break;
		case MDC_DIM_CENTI_M:					s = "MDC_DIM_CENTI_M";				break;
		case MDC_DIM_INCH:						s = "MDC_DIM_INCH";					break;
		case MDC_DIM_LB:						s = "MDC_DIM_LB";					break;
		case MDC_DIM_KG_PER_M_SQ:				s = "MDC_DIM_KG_PER_M_SQ";			break;
	}
	return s;
}

String^ devTypeId(UInt16 id) {
	String^ s = "";
	switch(id) {
		case MDC_DEV_SPEC_PROFILE_PULS_OXIM:		s = "PULS_OXIM";					break;
		case MDC_DEV_SPEC_PROFILE_MIN_ECG:			s = "MIN_ECG";						break;
		case MDC_DEV_SPEC_PROFILE_BP:				s = "BP";							break;
		case MDC_DEV_SPEC_PROFILE_TEMP:				s = "TEMP";							break;
		case MDC_DEV_SPEC_PROFILE_RESP_RATE:		s = "RESP_RATE";					break;
		case MDC_DEV_SPEC_PROFILE_SCALE:			s = "SCALE";						break;
		case MDC_DEV_SPEC_PROFILE_GLUCOSE:			s = "GLUCOSE";						break;
		case MDC_DEV_SPEC_PROFILE_INR:				s = "INR";							break;
		case MDC_DEV_SPEC_PROFILE_INSULIN_PUMP:		s = "INSULIN_PUMP";					break;
		case MDC_DEV_SPEC_PROFILE_BCA:				s = "BCA";							break;
		case MDC_DEV_SPEC_PROFILE_PEAK_FLOW:		s = "PEAK_FLOW";					break;
		case MDC_DEV_SPEC_PROFILE_HF_CARDIO:		s = "HF_CARDIO";					break;
		case MDC_DEV_SPEC_PROFILE_HF_STRENGTH:		s = "HF_STRENGTH";					break;
		case MDC_DEV_SPEC_PROFILE_AI_ACTIVITY_HUB:	s = "AI_ACTIVITY_HUB";				break;
		case MDC_DEV_SPEC_PROFILE_AI_MED_MINDER:	s = "AI_MED_MINDER";				break;

		default:									s = String::Format("{0:X4}",id);	break;
	}
	return s;
}

String^ devTypeIdFull(UInt16 id) {
	String^ s = "";
	switch(id) {
		case MDC_DEV_SPEC_PROFILE_PULS_OXIM:		s = "MDC_DEV_SPEC_PROFILE_PULS_OXIM";		break;
		case MDC_DEV_SPEC_PROFILE_MIN_ECG:			s = "MDC_DEV_SPEC_PROFILE_MIN_ECG";			break;
		case MDC_DEV_SPEC_PROFILE_BP:				s = "MDC_DEV_SPEC_PROFILE_BP";				break;
		case MDC_DEV_SPEC_PROFILE_TEMP:				s = "MDC_DEV_SPEC_PROFILE_TEMP";			break;
		case MDC_DEV_SPEC_PROFILE_RESP_RATE:		s = "MDC_DEV_SPEC_PROFILE_RESP_RATE";		break;
		case MDC_DEV_SPEC_PROFILE_SCALE:			s = "MDC_DEV_SPEC_PROFILE_SCALE";			break;
		case MDC_DEV_SPEC_PROFILE_GLUCOSE:			s = "MDC_DEV_SPEC_PROFILE_GLUCOSE";			break;
		case MDC_DEV_SPEC_PROFILE_INR:				s = "MDC_DEV_SPEC_PROFILE_INR";				break;
		case MDC_DEV_SPEC_PROFILE_INSULIN_PUMP:		s = "MDC_DEV_SPEC_PROFILE_INSULIN_PUMP";	break;
		case MDC_DEV_SPEC_PROFILE_BCA:				s = "MDC_DEV_SPEC_PROFILE_BCA";				break;
		case MDC_DEV_SPEC_PROFILE_PEAK_FLOW:		s = "MDC_DEV_SPEC_PROFILE_PEAK_FLOW";		break;
		case MDC_DEV_SPEC_PROFILE_HF_CARDIO:		s = "MDC_DEV_SPEC_PROFILE_HF_CARDIO";		break;
		case MDC_DEV_SPEC_PROFILE_HF_STRENGTH:		s = "MDC_DEV_SPEC_PROFILE_HF_STRENGTH";		break;
		case MDC_DEV_SPEC_PROFILE_AI_ACTIVITY_HUB:	s = "MDC_DEV_SPEC_PROFILE_AI_ACTIVITY_HUB";	break;
		case MDC_DEV_SPEC_PROFILE_AI_MED_MINDER:	s = "MDC_DEV_SPEC_PROFILE_AI_MED_MINDER";	break;
	}
	return s;
}

String^ configId(UInt16 id) {
	String^ s = "";
	if (id >= RESERVED_START)
		s = "Reserved ";
	else if (id >= EXTENDED_CONFIG_START)
		s = "Extended ";

	switch(id) {

		case STANDARD_CONFIG_SPO2:			s+= "SPO2";							break;
		case STANDARD_CONFIG_BP:			s+= "BP";							break;
		case STANDARD_CONFIG_ECG:			s+= "ECG";							break;
		case STANDARD_CONFIG_THERMOMETER:	s+= "THERMOMETER";					break;
		case STANDARD_CONFIG_SCALE:			s+= "SCALE";						break;
		case STANDARD_CONFIG_GLUCOSE:		s+= "GLUCOSE";						break;
		case STANDARD_CONFIG_ILAH:			s+= "ILAH";							break;
		case STANDARD_CONFIG_MEDICATION:	s+= "MEDICATION";					break;
		case STANDARD_CONFIG_INR:			s+= "INR";							break;

		default:							s+= String::Format("{0:X4}",id);	break;
	}
	return s;
}

String^ assocRes(UInt16 res) {
	String^ s = "";
	switch(res) {
		case ACCEPTED:								s = "ACCEPTED";								break;
		case REJECTED_PERMANENT:					s = "REJECTED_PERMANENT";					break;
		case REJECTED_TRANSIENT:					s = "REJECTED_TRANSIENT";					break;
		case ACCEPTED_UNKNOWN_CONFIG:				s = "ACCEPTED_UNKNOWN_CONFIG";				break;
		case REJECTED_NO_COMMON_PROTOCOL:			s = "REJECTED_NO_COMMON_PROTOCOL";			break;
		case REJECTED_NO_COMMON_PARAMETER:			s = "REJECTED_NO_COMMON_PARAMETER";			break;
		case REJECTED_UNKNOWN:						s = "REJECTED_UNKNOWN";						break;
		case REJECTED_UNAUTHORIZED:					s = "REJECTED_UNAUTHORIZED";				break;
		case REJECTED_UNSUPPORTED_ASSOC_VERSION:	s = "REJECTED_UNSUPPORTED_ASSOC_VERSION";	break;

		default:									s = String::Format("{0}",res);				break;
	}
	return s;
}

String^ releaseReason(UInt16 id) {
	String^ s = "";
	switch(id) {
		case RELEASE_REQUEST_REASON_NORMAL:					s = "NORMAL";						break;
		case RELEASE_REQUEST_REASON_NO_MORE_CONFIGURATIONS:	s = "NO_MORE_CONFIGURATIONS";		break;
		case RELEASE_REQUEST_REASON_CONFIGURATION_CHANGED:	s = "CONFIGURATION_CHANGED";		break;

		default:											s = String::Format("{0}",id);		break;
	}
	return s;
}

String^ abortReason(UInt16 id) {
	String^ s = "";
	switch(id) {
		case ABORT_REASON_UNDEFINED:				s = "UNDEFINED";							break;
		case ABORT_REASON_BUFFER_OVERFLOW:			s = "BUFFER_OVERFLOW";						break;
		case ABORT_REASON_RESPONSE_TIMEOUT:			s = "RESPONSE_TIMEOUT";						break;
		case ABORT_REASON_CONFIGURATION_TIMEOUT:	s = "CONFIGURATION_TIMEOUT";				break;

		default:									s = String::Format("{0}",id);				break;
	}
	return s;
}

String^ errorId(UInt16 id) {
	String^ s = "";
	switch(id) {
		case NO_SUCH_OBJECT_INSTANCE:				s = "NO_SUCH_OBJECT_INSTANCE";				break;
		case NO_SUCH_ACTION:						s = "NO_SUCH_ACTION";						break;
		case INVALID_OBJECT_INSTANCE:				s = "INVALID_OBJECT_INSTANCE";				break;
		case PROTOCOL_VIOLATION:					s = "PROTOCOL_VIOLATION";					break;
		case NOT_ALLOWED_BY_OBJECT:					s = "NOT_ALLOWED_BY_OBJECT";				break;
		case ACTION_TIMED_OUT:						s = "ACTION_TIMED_OUT";						break;
		case ACTION_ABORTED:						s = "ACTION_ABORTED";						break;

		default:									s = String::Format("{0}",id);				break;
	}
	return s;
}

String^ rejectId(UInt16 id) {
	String^ s = "";
	switch(id) {
		case UNRECOGNIZED_APDU:						s = "UNRECOGNIZED_APDU";					break;
		case BADLY_STRUCTURED_APDU:					s = "BADLY_STRUCTURED_APDU";				break;
		case UNRECOGNIZED_OPERATION:				s = "UNRECOGNIZED_OPERATION";				break;
		case RESOURCE_LIMITATION:					s = "RESOURCE_LIMITATION";					break;
		case UNEXPECTED_ERROR:						s = "UNEXPECTED_ERROR";						break;

		default:									s = String::Format("{0}",id);				break;
	}
	return s;
}

String^ resultId(UInt16 id) {
	String^ s = "";
	switch(id) {
		case ACCEPTED_CONFIG:						s = "ACCEPTED_CONFIG";						break;
		case UNSUPPORTED_CONFIG:					s = "UNSUPPORTED_CONFIG";					break;
		case STANDARD_CONFIG_UNKNOWN:				s = "STANDARD_CONFIG_UNKNOWN";				break;

		default:									s = String::Format("{0}",id);				break;
	}
	return s;
}

String^ getFlagText(UInt16 code, UInt16 type) {
	String^ codetext;

	switch (type)
	{
		case MDC_AI_TYPE_SENSOR_FALL:
			codetext = ((MDC_AI_TYPE_SENSOR_FALL_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_PERS:
			codetext = ((MDC_AI_TYPE_SENSOR_PERS_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_SMOKE:
		case MDC_AI_TYPE_SENSOR_CO:
		case MDC_AI_TYPE_SENSOR_WATER:
		case MDC_AI_TYPE_SENSOR_GAS:
			codetext = ((MDC_AI_TYPE_SENSOR_substance_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_MOTION:
			codetext = ((MDC_AI_TYPE_SENSOR_MOTION_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_PROPEXIT:
			codetext = ((MDC_AI_TYPE_SENSOR_PROPEXIT_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_ENURESIS:
			codetext = ((MDC_AI_TYPE_SENSOR_ENURESIS_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_CONTACTCLOSURE:
			codetext = ((MDC_AI_TYPE_SENSOR_CONTACTCLOSURE_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_USAGE:
			codetext = ((MDC_AI_TYPE_SENSOR_USAGE_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_SWITCH:
			codetext = ((MDC_AI_TYPE_SENSOR_SWITCH_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_DOSAGE:
			codetext = ((MDC_AI_TYPE_SENSOR_DOSAGE_flags)code).ToString();
			break;

		case MDC_AI_TYPE_SENSOR_TEMP:
			codetext = ((MDC_AI_TYPE_SENSOR_TEMP_flags)code).ToString();
			break;

		default:
			codetext = "";
			break;
	}
	return codetext;
}

String^ metricSpecSmallToString(UInt16 val)
{
	String^ s = "";

	if (val & MSS_AVAIL_INTERMITTENT) {
		if (s != "") s += "|";
		s += "AVAIL_INTERMITTENT";
	}
	if (val & MSS_AVAIL_STORED_DATA) {
		if (s != "") s += "|";
		s += "AVAIL_STORED_DATA";
	}
	if (val & MSS_UPD_APERIODIC) {
		if (s != "") s += "|";
		s += "UPD_APERIODIC";
	}
	if (val & MSS_MSMT_APERIODIC) {
		if (s != "") s += "|";
		s += "MSMT_APERIODIC";
	}
	if (val & MSS_MSMT_PHYS_EV_ID) {
		if (s != "") s += "|";
		s += "MSMT_PHYS_EV_ID";
	}
	if (val & MSS_MSMT_BTB_METRIC) {
		if (s != "") s += "|";
		s += "MSMT_BTB_METRIC";
	}
	if (val & MSS_ACC_MANAGER_INITIATED) {
		if (s != "") s += "|";
		s += "ACC_MANAGER_INITIATED";
	}
	if (val & MSS_ACC_AGENT_INITIATED) {
		if (s != "") s += "|";
		s += "ACC_AGENT_INITIATED";
	}
	if (val & MSS_CAT_MANUAL) {
		if (s != "") s += "|";
		s += "CAT_MANUAL";
	}
	if (val & MSS_CAT_SETTING) {
		if (s != "") s += "|";
		s += "CAT_SETTING";
	}
	if (val & MSS_CAT_CALCULATION) {
		if (s != "") s += "|";
		s += "CAT_CALCULATION";
	}

	return s;
}

String^ metricMdsTimeInfoToString(UInt16 val)
{
	String^ s = "";
	
	if (val & MDS_TIME_CAPAB_REAL_TIME_CLOCK) {
		if (s != "") s += "|";
		s += "CAPAB_REAL_TIME_CLOCK";
	}
	if (val & MDS_TIME_CAPAB_SET_CLOCK) {
		if (s != "") s += "|";
		s += "CAPAB_SET_CLOCK";
	}
	if (val & MDS_TIME_CAPAB_RELATIVE_TIME) {
		if (s != "") s += "|";
		s += "CAPAB_RELATIVE_TIME";
	}
	if (val & MDS_TIME_CAPAB_HIGH_RES_RELATIVE_TIME) {
		if (s != "") s += "|";
		s += "CAPAB_HIGH_RES_RELATIVE_TIME";
	}
	if (val & MDS_TIME_CAPAB_SYNC_ABS_TIME) {
		if (s != "") s += "|";
		s += "CAPAB_SYNC_ABS_TIME";
	}
	if (val & MDS_TIME_CAPAB_SYNC_REL_TIME) {
		if (s != "") s += "|";
		s += "CAPAB_SYNC_REL_TIME";
	}
	if (val & MDS_TIME_CAPAB_SYNC_HI_RES_RELATIVE_TIME) {
		if (s != "") s += "|";
		s += "CAPAB_SYNC_HI_RES_RELATIVE_TIME";
	}
	if (val & MDS_TIME_CAPAB_BO_TIME) {
		if (s != "") s += "|";
		s += "CAPAB_BO_TIME";
	}
	if (val & MDS_TIME_STATE_ABS_TIME_SYNCED) {
		if (s != "") s += "|";
		s += "STATE_ABS_TIME_SYNCED";
	}
	if (val & MDS_TIME_STATE_REL_TIME_SYNCED) {
		if (s != "") s += "|";
		s += "STATE_REL_TIME_SYNCED";
	}
	if (val & MDS_TIME_STATE_HI_RES_RELATIVE_TIME_SYNCED) {
		if (s != "") s += "|";
		s += "STATE_HI_RES_RELATIVE_TIME_SYNCED";
	}
	if (val & MDS_TIME_MGR_SET_TIME) {
		if (s != "") s += "|";
		s += "MGR_SET_TIME";
	}
	if (val & MDS_TIME_CAPAB_SYNC_BO_TIME) {
		if (s != "") s += "|";
		s += "CAPAB_SYNC_BO_TIME";
	}
	if (val & MSS_CAT_CALCULATION) {
		if (s != "") s += "|";
		s += "CAT_CALCULATION";
	}
	if (val & MDS_TIME_STATE_BO_TIME_SYNCED) {
		if (s != "") s += "|";
		s += "STATE_BO_TIME_SYNCED";
	}

	return s;
}
