#ifndef NOMENCLATURE
#define NOMENCLATURE


/* Partition codes				*/
#define MDC_PART_UNSPEC	0	/*  Unspecified		*/
#define MDC_PART_OBJ	1	/*  Object Infrastr.		*/
#define MDC_PART_SCADA	2	/*  SCADA (Physio IDs)		*/
#define MDC_PART_ALERT	3	/*  Alert/Events		*/
#define MDC_PART_DIM	4	/*  Dimension		*/
#define MDC_PART_VATTR	5	/*  Virtual Attributes		*/
#define MDC_PART_PGRP	6	/*  Param Group ID		*/
#define MDC_PART_SITES	7	/*  Body Site Locations		*/
#define MDC_PART_INFRA 	8	/*  Infrastructure		*/
#define MDC_PART_FEF	9	/*  File Exchange Format		*/
#define MDC_PART_ECG_EXTN	10	/* ECG Extensions		*/
#define MDC_PART_IDCO_EXTN                                   11       /* IDCO Extensions                         */
#define MDC_PART_PHD_DM	128	/* Disease Mgmt		*/
#define MDC_PART_PHD_HF	129	/* Health and Fitness		*/
#define MDC_PART_PHD_AI	130	/* Aging Independently		*/
#define MDC_PART_RET_CODE	255	/* Return Codes		*/
#define MDC_PART_EXT_NOM	256	/* Ext. Nomenclature		*/
#define MDC_PART_PRIV	1024	/* Private		*/

/**********************************************************************************
* From Object Infrastructure (MDC_PART_OBJ)
**********************************************************************************/
#define MDC_MOC_VMO_METRIC	4	/*		*/
#define MDC_MOC_VMO_METRIC_ENUM	5	/*		*/
#define MDC_MOC_VMO_METRIC_NU	6	/*		*/
#define MDC_MOC_VMO_METRIC_SA_RT	9	/*		*/
#define MDC_MOC_SCAN	16	/*		*/
#define MDC_MOC_SCAN_CFG	17	/*		*/
#define MDC_MOC_SCAN_CFG_EPI	18	/*		*/
#define MDC_MOC_SCAN_CFG_PERI	19	/*		*/
#define MDC_MOC_VMS_MDS_SIMP	37	/*		*/
#define MDC_MOC_VMO_PMSTORE	61	/*		*/
#define MDC_MOC_PM_SEGMENT	62	/*		*/
#define MDC_ATTR_CONFIRM_MODE	2323	/*		*/
#define MDC_ATTR_CONFIRM_TIMEOUT	2324	/*		*/
#define MDC_ATTR_ID_HANDLE	2337	/*		*/
#define MDC_ATTR_ID_INSTNO	2338	/*		*/
#define MDC_ATTR_ID_LABEL_STRING	2343	/*		*/
#define MDC_ATTR_ID_MODEL	2344	/*		*/
#define MDC_ATTR_ID_PHYSIO	2347	/*		*/
#define MDC_ATTR_ID_PROD_SPECN	2349	/*		*/
#define MDC_ATTR_ID_TYPE	2351	/*		*/
#define MDC_ATTR_METRIC_STORE_CAPAC_CNT	2369	/*		*/
#define MDC_ATTR_METRIC_STORE_SAMPLE_ALG 2371 /*		*/
#define MDC_ATTR_METRIC_STORE_USAGE_CNT	2372	/*		*/
#define MDC_ATTR_MSMT_STAT	2375	/*			*/
#define MDC_ATTR_NU_ACCUR_MSMT	2378	/*		*/
#define MDC_ATTR_NU_CMPD_VAL_OBS	2379	/*		*/
#define MDC_ATTR_NU_VAL_OBS	2384	/*		*/
#define MDC_ATTR_NUM_SEG	2385	/*		*/
#define MDC_ATTR_OP_STAT	2387	/*		*/
#define MDC_ATTR_POWER_STAT	2389	/*		*/
#define MDC_ATTR_SA_SPECN	2413	/*		*/
#define MDC_ATTR_SCALE_SPECN_I16	2415	/*		*/
#define MDC_ATTR_SCALE_SPECN_I32	2416	/*		*/
#define MDC_ATTR_SCALE_SPECN_I8	2417	/*		*/
#define MDC_ATTR_SCAN_REP_PD	2421	/*		*/
#define MDC_ATTR_SEG_USAGE_CNT	2427	/*		*/
#define MDC_ATTR_SYS_ID 	2436	/*		*/
#define MDC_ATTR_SYS_TYPE	2438	/*		*/
#define MDC_ATTR_TIME_ABS	2439	/*		*/
#define MDC_ATTR_TIME_BATT_REMAIN	2440	/*		*/
#define MDC_ATTR_TIME_END_SEG	2442	/*		*/
#define MDC_ATTR_TIME_PD_SAMP	2445	/*		*/
#define MDC_ATTR_TIME_REL	2447	/*		*/
#define MDC_ATTR_TIME_STAMP_ABS	2448	/*		*/
#define MDC_ATTR_TIME_STAMP_REL	2449	/*		*/
#define MDC_ATTR_TIME_START_SEG	2450	/*		*/
#define MDC_ATTR_TX_WIND	2453	/*		*/
#define MDC_ATTR_UNIT_CODE	2454	/*		*/
#define MDC_ATTR_UNIT_LABEL_STRING	2457	/*		*/
#define MDC_ATTR_VAL_BATT_CHARGE	2460	/*		*/
#define MDC_ATTR_VAL_ENUM_OBS	2462	/*		*/
#define MDC_ATTR_TIME_REL_HI_RES	2536	/*		*/
#define MDC_ATTR_TIME_STAMP_REL_HI_RES	2537	/*		*/
#define MDC_ATTR_DEV_CONFIG_ID	2628	/*		*/
#define MDC_ATTR_MDS_TIME_INFO	2629	/*		*/
#define MDC_ATTR_METRIC_SPEC_SMALL	2630	/*		*/
#define MDC_ATTR_SOURCE_HANDLE_REF	2631	/*		*/
#define MDC_ATTR_SIMP_SA_OBS_VAL	2632	/*		*/
#define MDC_ATTR_ENUM_OBS_VAL_SIMP_OID	2633	/*		*/
#define MDC_ATTR_ENUM_OBS_VAL_SIMP_STR	2634	/*		*/
#define MDC_ATTR_REG_CERT_DATA_LIST	2635	/*		*/
#define MDC_ATTR_NU_VAL_OBS_BASIC	2636	/*		*/
#define MDC_ATTR_PM_STORE_CAPAB	2637	/*		*/
#define MDC_ATTR_PM_SEG_MAP	2638	/*		*/
#define MDC_ATTR_PM_SEG_PERSON_ID	2639	/*		*/
#define MDC_ATTR_SEG_STATS	2640	/*		*/
#define MDC_ATTR_SEG_FIXED_DATA	2641	/*		*/
#define MDC_ATTR_SCAN_HANDLE_ATTR_VAL_MAP 2643 /*		*/
#define MDC_ATTR_SCAN_REP_PD_MIN	2644	/*		*/
#define MDC_ATTR_ATTRIBUTE_VAL_MAP	2645	/*		*/
#define MDC_ATTR_NU_VAL_OBS_SIMP	2646	/*		*/
#define MDC_ATTR_PM_STORE_LABEL_STRING	2647	/*		*/
#define MDC_ATTR_PM_SEG_LABEL_STRING	2648	/*		*/
#define MDC_ATTR_TIME_PD_MSMT_ACTIVE	2649	/*		*/
#define MDC_ATTR_SYS_TYPE_SPEC_LIST	2650	/*		*/
#define MDC_ATTR_METRIC_ID_PART	2655	/*		*/
#define MDC_ATTR_ENUM_OBS_VAL_PART	2656	/*		*/
#define MDC_ATTR_SUPPLEMENTAL_TYPES	2657	/*		*/
#define MDC_ATTR_TIME_ABS_ADJUST	2658	/*		*/
#define MDC_ATTR_CLEAR_TIMEOUT	2659	/*		*/
#define MDC_ATTR_TRANSFER_TIMEOUT	2660	/*		*/
#define MDC_ATTR_ENUM_OBS_VAL_SIMP_BIT_STR 2661 /*		*/
#define MDC_ATTR_ENUM_OBS_VAL_BASIC_BIT_STR 2662 /*		*/
#define MDC_ATTR_METRIC_STRUCT_SMALL	2675	/*		*/
#define MDC_ATTR_NU_CMPD_VAL_OBS_SIMP	2676	/*		*/
#define MDC_ATTR_NU_CMPD_VAL_OBS_BASIC	2677	/*		*/
#define MDC_ATTR_ID_PHYSIO_LIST	2678	/*		*/
#define MDC_ATTR_SCAN_HANDLE_LIST	2679	/*		*/
#define MDC_ATTR_TIME_BO	2689	/*		*/
#define MDC_ATTR_TIME_STAMP_BO	2690	/*		*/
#define MDC_ATTR_TIME_START_SEG_BO	2691	/*		*/
#define MDC_ATTR_TIME_END_SEG_BO	2692	/*		*/
#define MDC_ATTR_CONTEXT_KEY 2680 /* Context Key */

/* Partition: ACT */
#define MDC_ACT_SEG_CLR    3084    /*        */
#define MDC_ACT_SEG_GET_INFO    3085    /*        */
#define MDC_ACT_SET_TIME    3095    /*        */
#define MDC_ACT_DATA_REQUEST    3099    /*        */
#define MDC_ACT_SEG_TRIG_XFER    3100    /*        */
#define MDC_ACT_SET_BO_TIME    3101    /*        */

#define MDC_ACT_BAD_ACTION 0xFFFF /* dummy for testing */

#define MDC_ACT_DATA_REQUEST	3099	/*		*/
#define MDC_ACT_SEG_TRIG_XFER	3100	/*		*/


/* Partition: NOTI */
#define MDC_NOTI_CONFIG	3356	/*		*/
#define MDC_NOTI_SCAN_REPORT_FIXED	3357	/*		*/
#define MDC_NOTI_SCAN_REPORT_VAR	3358	/*		*/
#define MDC_NOTI_SCAN_REPORT_MP_FIXED	3359	/*		*/
#define MDC_NOTI_SCAN_REPORT_MP_VAR	3360	/*		*/
#define MDC_NOTI_SEGMENT_DATA	3361	/*		*/
#define MDC_NOTI_UNBUF_SCAN_REPORT_VAR	3362	/*		*/
#define MDC_NOTI_UNBUF_SCAN_REPORT_FIXED	3363	/*		*/
#define MDC_NOTI_UNBUF_SCAN_REPORT_GROUPED	3364 /*		*/
#define MDC_NOTI_UNBUF_SCAN_REPORT_MP_VAR	3365 /*		*/
#define MDC_NOTI_UNBUF_SCAN_REPORT_MP_FIXED	3366 /*		*/
#define MDC_NOTI_UNBUF_SCAN_REPORT_MP_GROUPED	3367 /*		*/
#define MDC_NOTI_BUF_SCAN_REPORT_VAR	3368	/*		*/
#define MDC_NOTI_BUF_SCAN_REPORT_FIXED	3369	/*		*/
#define MDC_NOTI_BUF_SCAN_REPORT_GROUPED	3370 /*		*/
#define MDC_NOTI_BUF_SCAN_REPORT_MP_VAR	3371 /*		*/
#define MDC_NOTI_BUF_SCAN_REPORT_MP_FIXED	3372 /*		*/
#define MDC_NOTI_BUF_SCAN_REPORT_MP_GROUPED	3373 /*		*/

/*********************************************************************************
* From Medical supervisory control and data acquisition (MDC_PART_SCADA)
**********************************************************************************/
#define MDC_PULS_RATE_NON_INV 18474 /* */
#define MDC_PRESS_BLD_NONINV 18948 /* NIBP */
#define MDC_PRESS_BLD_NONINV_SYS 18949 /* */
#define MDC_PRESS_BLD_NONINV_DIA 18950 /* */
#define MDC_PRESS_BLD_NONINV_MEAN 18951 /* */
#define MDC_TEMP_BODY	19292	/*TEMPbody		*/
#define MDC_PULS_OXIM_PULS_RATE 18458 /* */
#define MDC_SAT_O2_QUAL 19248 /* */
#define MDC_PULS_OXIM_PERF_REL 19376 /* */
#define MDC_PULS_OXIM_PLETH 19380 /* */
#define MDC_PULS_OXIM_SAT_O2 19384 /* */
#define MDC_PULS_OXIM_PULS_CHAR 19512 /* */
#define MDC_PULS_OXIM_DEV_STATUS 19532 /* */
#define MDC_TRIG 53250 /* */
#define MDC_TRIG_BEAT 53251 /* */
#define MDC_TRIG_BEAT_MAX_INRUSH 53259 /* */
#define MDC_METRIC_NOS 61439 /* */
#define MDC_MODALITY_FAST 19508 /* */
#define MDC_MODALITY_SLOW 19512 /* */
#define MDC_MODALITY_SPOT 19516 /* */
#define MDC_MASS_BODY_ACTUAL	57664	/*  		*/
#define MDC_BODY_FAT	57676	/*		*/

/*********************************************************************************
* From Dimensions (MDC_PART_DIM)
**********************************************************************************/
#define MDC_DIM_PERCENT 	544	/*  %		*/
#define MDC_DIM_KILO_G 	1731	/*  kg		*/
#define MDC_DIM_MIN	2208	/*  min		*/
#define MDC_DIM_HR	2240	/*  h		*/
#define MDC_DIM_DAY	2272	/*  d		*/
#define MDC_DIM_DEGC	6048	/* oC		*/
#define MDC_DIM_MILLI_L 1618 /* ml */
#define MDC_DIM_MILLI_G 1746 /* mg */
#define MDC_DIM_INTL_UNIT 5472 /* i.u. */

/*********************************************************************************
* From Communication Infrastructure (MDC_PART_INFRA)
**********************************************************************************/
#define MDC_DEV_SPEC_PROFILE_PULS_OXIM	4100	/*		*/
#define MDC_DEV_SPEC_PROFILE_MIN_ECG	4102	/*		*/
#define MDC_DEV_SPEC_PROFILE_BP	4103	/*		*/
#define MDC_DEV_SPEC_PROFILE_TEMP	4104	/*		*/
#define MDC_DEV_SPEC_PROFILE_RESP_RATE       4109   /* Respiration rate                            */
#define MDC_DEV_SPEC_PROFILE_SCALE	4111	/*  		*/
#define MDC_DEV_SPEC_PROFILE_GLUCOSE	4113	/*		*/
#define MDC_DEV_SPEC_PROFILE_INR	4114	/* International normalized ratio	*/
#define MDC_DEV_SPEC_PROFILE_INSULIN_PUMP	4115	/*		*/
#define MDC_DEV_SPEC_PROFILE_BCA	4116	/* Body composition analyzer	*/
#define MDC_DEV_SPEC_PROFILE_PEAK_FLOW	4117	/* 		*/
#define MDC_DEV_SPEC_PROFILE_HF_CARDIO	4137	/*		*/
#define MDC_DEV_SPEC_PROFILE_HF_STRENGTH	4138	/*		*/
#define MDC_DEV_SPEC_PROFILE_AI_ACTIVITY_HUB 4167 /*		*/
#define MDC_DEV_SPEC_PROFILE_AI_MED_MINDER    4168 /*		*/
/* The range from 4196 to 5119 is reserved for sub classifying devices within other specializations (profiles).  For instance in the -10441 (Cardio) specialization defines step counters as a profile		*/

/* 4196 through 4211 used for IEEE Std 11073-10441 (Cardio)			*/
#define MDC_DEV_SUB_SPEC_PROFILE_STEP_COUNTER	4200	/* Step counter	*/

/* 4212 through 4235 used for IEEE Std 11073-10471 (Activity hub)                                                   */
#define MDC_DEV_SUB_SPEC_PROFILE_FALL_SENSOR	4213	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_PERS_SENSOR	4214	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_SMOKE_SENSOR	4215	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_CO_SENSOR	4216 	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_WATER_SENSOR	4217  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_GAS_SENSOR	4218  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_MOTION_SENSOR	4219  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_PROPEXIT_SENSOR	4220  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_ENURESIS_SENSOR	4221  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_CONTACTCLOSURE_SENSOR 4222  /*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_USAGE_SENSOR	4223  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_SWITCH_SENSOR	4224  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_DOSAGE_SENSOR	4225  	/*	*/
#define MDC_DEV_SUB_SPEC_PROFILE_TEMP_SENSOR	4226  	/*	*/

/* Placed 256 back from the start of the last Partition: OptionalPackageIdentifiers (i.e., 8192-256). */
#define MDC_TIME_SYNC_NONE	7936	/* no time synchronization protocol supported */
#define MDC_TIME_SYNC_NTPV3	7937	/* RFC 1305	1992 Mar	obs: 1119,1059,958 */
#define MDC_TIME_SYNC_NTPV4	7938	/* <under development at ntp.org>	*/
#define MDC_TIME_SYNC_SNTPV4	7939	/* RFC 2030	1996 Oct	obs: 1769	*/
#define MDC_TIME_SYNC_SNTPV4330	7940	/* RFC 4330	2006 Jan	obs: 2030,1769	*/
#define MDC_TIME_SYNC_BTV1                 7941       /* Bluetooth Medical Device Profile 		*/

/*********************************************************************************
* From Return Codes (MDC_PART_RET_CODE)
**********************************************************************************/
#define MDC_RET_CODE_UNKNOWN	1	 /* Generic error code		*/

/* Partition MDC_PART_RET_CODE/OBJ Object errors				*/
#define MDC_RET_CODE_OBJ_BUSY	1000	 /* Object is busy so cannot handle the request */

/* Partition MDC_PART_RETURN_CODES/STORE Storage errors		*/
#define MDC_RET_CODE_STORE_EXH	2000	 /* Storage such as disk is full		*/
#define MDC_RET_CODE_STORE_OFFLN	2001	 /* Storage such as disk is offline		*/


/*********************************************************************************
* All of the following are from NomPartition (MDC_PART_PHD_AI)
**********************************************************************************/
/**********************************************************************************
* All of the following are from NomPartition (MDC_PART_PHD_AI) *
**********************************************************************************/
#define MDC_AI_TYPE_SENSOR_FALL 1 /* */
#define MDC_AI_TYPE_SENSOR_PERS 2 /* */
#define MDC_AI_TYPE_SENSOR_SMOKE 3 /* */
#define MDC_AI_TYPE_SENSOR_CO 4 /* */
#define MDC_AI_TYPE_SENSOR_WATER 5 /* */
#define MDC_AI_TYPE_SENSOR_GAS 6 /* */
#define MDC_AI_TYPE_SENSOR_MOTION 7 /* */
#define MDC_AI_TYPE_SENSOR_PROPEXIT 8 /* */
#define MDC_AI_TYPE_SENSOR_ENURESIS 9 /* */
#define MDC_AI_TYPE_SENSOR_CONTACTCLOSURE 10 /* */
#define MDC_AI_TYPE_SENSOR_USAGE 11 /* */
#define MDC_AI_TYPE_SENSOR_SWITCH 12 /* */
#define MDC_AI_TYPE_SENSOR_DOSAGE 13 /* */
#define MDC_AI_TYPE_SENSOR_TEMP 14 /* */
#define MDC_AI_TYPE_SENSOR_HUMIDITY 15 /* */
/* The range 15-1024 is reserved for future expansion */

/**********************************************************************************
* Locations are encoded within 16 bits as….. *
* upper 10 bits are the location type (for example bedroom - MDC_AI_LOCATION_BEDROOM) *
* lower 6 bits are the location type instance identifier (for example bedroom 0, bedroom 1, etc.) *
* therefore, location viewed as a 16 bit entity would have the types assigned in blocks of 64 *
* The location type instance identifier allows for both a single dwelling with multiple rooms of that *
* type, as well as a multiple family dwelling that may contain that type room in each subunit *
* **********************************************************************************/
/* general */
#define MDC_AI_LOCATION_START 1024 /* */
#define MDC_AI_LOCATION_UNKNOWN 1024 /* */
#define MDC_AI_LOCATION_UNSPECIFIED 1088 /* */
#define MDC_AI_LOCATION_RESIDENT 1152 /* */
#define MDC_AI_LOCATION_LOCALUNIT 1216 /* */
/* The range 1217-3071 is reserved for future expansion */
/* rooms */
#define MDC_AI_LOCATION_BEDROOM 3072 /* */
#define MDC_AI_LOCATION_BEDROOMMASTER 3136 /* */
#define MDC_AI_LOCATION_TOILET 3200 /* */
#define MDC_AI_LOCATION_TOILETMAIN 3264 /* */
#define MDC_AI_LOCATION_OUTSIDETOILET 3328 /* */
#define MDC_AI_LOCATION_SHOWERROOM 3392 /* */
#define MDC_AI_LOCATION_KITCHEN 3456 /* */
#define MDC_AI_LOCATION_KITCHENMAIN 3520 /* */
#define MDC_AI_LOCATION_LIVINGAREA 3584 /* */
#define MDC_AI_LOCATION_LIVINGROOM 3648 /* */
#define MDC_AI_LOCATION_DININGROOM 3712 /* */
#define MDC_AI_LOCATION_STUDY 3776 /* */
#define MDC_AI_LOCATION_HALL 3840 /* */
#define MDC_AI_LOCATION_LANDING 3904 /* */
#define MDC_AI_LOCATION_STAIRS 3968 /* */
#define MDC_AI_LOCATION_HALLLANDINGSTAIRS 4032 /* */
#define MDC_AI_LOCATION_GARAGE 4096 /* */
#define MDC_AI_LOCATION_GARDENGARAGE 4160 /* */
#define MDC_AI_LOCATION_GARDENGARAGEAREA 4224 /* */
#define MDC_AI_LOCATION_FRONTGARDEN 4288 /* */
#define MDC_AI_LOCATION_BACKGARDEN 4352 /* */
#define MDC_AI_LOCATION_SHED 4416 /* */
/* The range 4417-7167 is reserved for future expansion */
/* appliances */
#define MDC_AI_APPLIANCE_KETTLE 7168 /* Note: Self heating */
#define MDC_AI_APPLIANCE_TELEVISION 7232 /* */
#define MDC_AI_APPLIANCE_STOVE 7296 /* */
#define MDC_AI_APPLIANCE_MICROWAVE 7360 /* */
#define MDC_AI_APPLIANCE_TOASTER 7424 /* */
#define MDC_AI_APPLIANCE_VACUUM 7488 /* */
#define MDC_AI_APPLIANCE_APPLIANCE 7552 /* */
#define MDC_AI_APPLIANCE_FAUCET 7616 /* */
/* The range 7617-9215 is reserved for future expansion */
/* doors */
#define MDC_AI_LOCATION_FRONTDOOR 9216 /* */
#define MDC_AI_LOCATION_BACKDOOR 9280 /* */
#define MDC_AI_LOCATION_FRIDGEDOOR 9344 /* */
#define MDC_AI_LOCATION_MEDCABDOOR 9408 /* */
#define MDC_AI_LOCATION_WARDROBEDOOR 9472 /* */
#define MDC_AI_LOCATION_FRONTCUPBOARDDOOR 9536 /* */
#define MDC_AI_LOCATION_OTHERDOOR 9600 /* */
/* The range 9601-11263 is reserved for future expansion */
/* usage */
#define MDC_AI_LOCATION_BED 11264 /* */
#define MDC_AI_LOCATION_CHAIR 11328 /* */
#define MDC_AI_LOCATION_SOFA 11392 /* */
#define MDC_AI_LOCATION_TOILET_SEAT 11456 /* */
#define MDC_AI_LOCATION_STOOL 11520 /* */
/* The range 11521-13311 is reserved for future expansion */
/* The range 13312-61439 (0x3400-0xEFFF) is reserved for future expansion */


#define MDC_AI_MED_DISPENSED_FIXED 13312 /* Fixed-dosage dispensed */
#define MDC_AI_MED_DISPENSED_VARIABLE 13313 /* Variable-dosage dispensed */
#define MDC_AI_MED_DISPENSED_TAKEN 13321 /* Variable-dosage dispensed */
#define MDC_AI_MED_STATUS 13314 /* Medication monitor status */
#define MDC_AI_MED_FEEDBACK 13315 /* User feedback */
#define MDC_AI_MED_UF_LOCATION 13316 /* User feedback - location */
#define MDC_AI_MED_UF_RESPONSE 13317 /* User feedback - response */
#define MDC_AI_MED_UF_TYPE_YESNO 13318 /* User feedback type – yes/no */
#define MDC_AI_MED_UF_TYPE_1_5 13319		/* User feedback type – */
																				/* interval 1-5 */
#define MDC_AI_MED_UF_TYPE_1_100 13320	/* User feedback type – */
																				/* interval 1-100 */

/*********************************************************************************
* From Medical supervisory control and data acquisition (MDC_PART_SCADA)
**********************************************************************************/
#define MDC_CONC_GLU_GEN 28948/* */
#define MDC_CONC_GLU_CAPILLARY_WHOLEBLOOD 29112/* */
#define MDC_CONC_GLU_CAPILLARY_PLASMA 29116/* */
#define MDC_CONC_GLU_VENOUS_WHOLEBLOOD 29120/* */
#define MDC_CONC_GLU_VENOUS_PLASMA 29124/* */
#define MDC_CONC_GLU_ARTERIAL_WHOLEBLOOD 29128/* */
#define MDC_CONC_GLU_ARTERIAL_PLASMA 29132/* */
#define MDC_CONC_GLU_CONTROL 29136/* */
#define MDC_CONC_GLU_ISF 29140/* */
#define MDC_CONC_HBA1C 29148/* */
/*********************************************************************************
* From Personal Health Device Disease Management (MDC_PART_PHD_DM)
**********************************************************************************/
#define MDC_GLU_METER_DEV_STATUS 29144/* */
#define MDC_CTXT_GLU_EXERCISE 29152/* */
#define MDC_CTXT_GLU_CARB 29156/* */
#define MDC_CTXT_GLU_CARB_BREAKFAST 29160/* */
#define MDC_CTXT_GLU_CARB_LUNCH 29164/* */
#define MDC_CTXT_GLU_CARB_DINNER 29168/* */
#define MDC_CTXT_GLU_CARB_SNACK 29172/* */
#define MDC_CTXT_GLU_CARB_DRINK 29176/* */
#define MDC_CTXT_GLU_CARB_SUPPER 29180/* */
#define MDC_CTXT_GLU_CARB_BRUNCH 29184/* */
#define MDC_CTXT_MEDICATION 29188/* */
#define MDC_CTXT_MEDICATION_RAPIDACTING 29192/* */
#define MDC_CTXT_MEDICATION_SHORTACTING 29196/* */
#define MDC_CTXT_MEDICATION_INTERMEDIATEACTING 29200/* */
#define MDC_CTXT_MEDICATION_LONGACTING 29204/* */
#define MDC_CTXT_MEDICATION_PREMIX 29208/* */
#define MDC_CTXT_GLU_HEALTH 29212/* */
#define MDC_CTXT_GLU_HEALTH_MINOR 29216/* */
#define MDC_CTXT_GLU_HEALTH_MAJOR 29220/* */
#define MDC_CTXT_GLU_HEALTH_STRESS 29228/* */
#define MDC_CTXT_GLU_HEALTH_NONE 29232/* */
#define MDC_CTXT_GLU_SAMPLELOCATION 29236/* */
#define MDC_CTXT_GLU_SAMPLELOCATION_FINGER 29240/* */
#define MDC_CTXT_GLU_SAMPLELOCATION_AST 29244/* */
#define MDC_CTXT_GLU_SAMPLELOCATION_EARLOBE 29248/* */
#define MDC_CTXT_GLU_SAMPLELOCATION_CTRLSOLUTION 29252/* */
#define MDC_CTXT_GLU_MEAL 29256/* */
#define MDC_CTXT_GLU_MEAL_PREPRANDIAL 29260/* */
#define MDC_CTXT_GLU_MEAL_POSTPRANDIAL 29264/* */
#define MDC_CTXT_GLU_MEAL_FASTING 29268/* */
#define MDC_CTXT_GLU_MEAL_CASUAL 29272/* */
#define MDC_CTXT_GLU_TESTER 29276/* */
#define MDC_CTXT_GLU_TESTER_SELF 29280/* */
#define MDC_CTXT_GLU_TESTER_HCP 29284/* */
#define MDC_CTXT_GLU_TESTER_LAB 29288/* */
/*********************************************************************************
* From Dimensions (MDC_PART_DIM)
**********************************************************************************/
#define MDC_DIM_MILLI_L 1618 /* mL */
#define MDC_DIM_MILLI_G 1746 /* mg */
#define MDC_DIM_MILLI_G_PER_DL 2130 /* mg dL-1 */
#define MDC_DIM_MILLI_MOLE_PER_L 4722 /* mmol L-1 */
#define MDC_DIM_X_G 1728 /* g */

/*********************************************************************************
* From Specializations
* These are defined between zz*100 to zz*100+99 for each specialization,
* where specializations are numbered 104zz
**********************************************************************************/
#define STANDARD_CONFIG_SPO2 400
#define STANDARD_CONFIG_SPO2_SPOT 401
#define STANDARD_CONFIG_ECG 600
#define STANDARD_CONFIG_BP 700
#define STANDARD_CONFIG_THERMOMETER 800
#define STANDARD_CONFIG_SCALE 1500
#define STANDARD_CONFIG_GLUCOSE 1700
#define STANDARD_CONFIG_INR 1800
#define STANDARD_CONFIG_INSULIN_PUMP 1900
#define STANDARD_CONFIG_BCA 2000
#define STANDARD_CONFIG_PEAK_FLOW 2100
#define STANDARD_CONFIG_URINE 2200
#define STANDARD_CONFIG_CARDIO 4100
#define STANDARD_CONFIG_STRENGHT 4200
#define STANDARD_CONFIG_ILAH 7100
#define STANDARD_CONFIG_MEDICATION 7200

/*********************************************************************************
* From Medical supervisory control and data acquisition (MDC_PART_SCADA)
**********************************************************************************/
#define MDC_LEN_BODY_ACTUAL 57668 /* */
#define MDC_RATIO_MASS_BODY_LEN_SQ 57680 /* */
/*********************************************************************************
* From Dimensions (MDC_PART_DIM)
**********************************************************************************/
#define MDC_DIM_CENTI_M 1297 /* cm */
#define MDC_DIM_INCH 1376 /* in */
#define MDC_DIM_LB 1760 /* lb */
#define MDC_DIM_KG_PER_M_SQ 1952 /* kg m-2 */


/*********************************************************************************
* From Medical supervisory control and data acquisition (MDC_PART_SCADA)
**********************************************************************************/
#define MDC_PULS_RATE_NON_INV 18474 /* */
#define MDC_PRESS_BLD_NONINV 18948 /* NIBP */
#define MDC_PRESS_BLD_NONINV_SYS 18949 /* */
#define MDC_PRESS_BLD_NONINV_DIA 18950 /* */
#define MDC_PRESS_BLD_NONINV_MEAN 18951 /* */
/*********************************************************************************
* From Dimensions (MDC_PART_DIM)
**********************************************************************************/
#define MDC_DIM_BEAT_PER_MIN 2720 /* bpm */
#define MDC_DIM_KILO_PASCAL 3843 /* kPa */
#define MDC_DIM_MMHG 3872 /* mmHg */


/*********************************************************************************
* From Independent Living Activity Hub - ASN.1 definitions
**********************************************************************************/
#define AUTO_PRESENCE_RECEIVED 0x00008000L
#define AUTO_PRESENCE_FAILED 0x00004000L
#define LOW_BATTERY 0x00002000L
#define FAULT 0x00001000L
#define END_OF_LIFE 0x00000800L

#define FALL_DETECTED 0x80000000L

#define PERS_ACTIVATED 0x80000000L

#define CONDITION_DETECTED 0x80000000L

#define MOTION_DETECTED 0x80000000L
#define MOTION_DETECTED_DELAYED 0x40000000L
#define TAMPER_DETECTED 0x20000000L

#define OCCUPANT_EXIT_PROPERTY 0x80000000L
#define EXIT_DOOR_LEFT_OPEN 0x80000000L

#define ENURESIS_DETECTED 0x80000000L

#define CONTACT_OPENED 0x80000000L
#define CONTACT_CLOSED 0x40000000L

#define USAGE_STARTED 0x80000000L
#define USAGE_ENDED 0x40000000L
#define EXPECTED_USE_START_VIOLATION 0x20000000L
#define EXPECTED_USE_STOP_VIOLATION 0x10000000L
#define ABSENCE_VIOLATION 0x08000000L

#define ALARM 0x00000000L /* for Tynetec */

#define IGNORE 0x00000000L

#define SWITCH_ON 0x80000000L
#define SWITCH_OFF 0x40000000L

#define DOSAGE_TAKEN 0x80000000L
#define DOSAGE_MISSED 0x40000000L
#define DOSAGE_PRESENTED 0x20000000L /* for Pivotell */

#define HIGH_TEMPERATURE_DETECTED 0x80000000L
#define LOW_TEMPERATURE_DETECTED 0x40000000L
#define RATE_OF_CHANGE_TOO_FAST 0x20000000L

#define HIGH_HUMIDITY_DETECTED 0x80000000L

#endif /*  NOMENCLATURE */
