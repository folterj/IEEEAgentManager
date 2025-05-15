
// ERROR
#define NO_SUCH_OBJECT_INSTANCE		1
#define NO_SUCH_ACTION				9
#define INVALID_OBJECT_INSTANCE		17
#define PROTOCOL_VIOLATION			23
#define NOT_ALLOWED_BY_OBJECT		24
#define ACTION_TIMED_OUT			25
#define ACTION_ABORTED				26

// RORJ problem
#define UNRECOGNIZED_APDU			0
#define BADLY_STRUCTURED_APDU		2
#define UNRECOGNIZED_OPERATION		101
#define RESOURCE_LIMITATION			103
#define UNEXPECTED_ERROR			303

// APDU choice
#define         AARQ_CHOSEN             0xE200
#define         AARE_CHOSEN             0xE300
#define         RLRQ_CHOSEN             0xE400
#define         RLRE_CHOSEN             0xE500
#define         ABRT_CHOSEN             0xE600
#define         PRST_CHOSEN             0xE700

// ROSE choice
#define         ROIV_CMIP_EVENT_REPORT_CHOSEN           0x0100
#define         ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN 0x0101
#define         ROIV_CMIP_GET_CHOSEN                    0x0103
#define         ROIV_CMIP_SET_CHOSEN                    0x0104
#define         ROIV_CMIP_CONFIRMED_SET_CHOSEN          0x0105
#define         ROIV_CMIP_ACTION_CHOSEN                 0x0106
#define         ROIV_CMIP_CONFIRMED_ACTION_CHOSEN       0x0107
#define         RORS_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN 0x0201
#define         RORS_CMIP_GET_CHOSEN                    0x0203
#define         RORS_CMIP_CONFIRMED_SET_CHOSEN          0x0205
#define         RORS_CMIP_CONFIRMED_ACTION_CHOSEN       0x0207
#define         ROER_CHOSEN                             0x0300
#define         RORJ_CHOSEN                             0x0400

// ROSE remote operation
#define         ROIV									0x01
#define         RORS									0x02
#define         ROER									0x03
#define         RORJ									0x04

// ROSE protocol
#define         CMIP_EVENT_REPORT_CHOSEN				0x01
#define         CMIP_GET_CHOSEN							0x03
#define         CMIP_SET_CHOSEN							0x04
#define         CMIP_CONFIRMED_SET_CHOSEN				0x05
#define         CMIP_ACTION_CHOSEN						0x06
#define         CMIP_CONFIRMED_ACTION_CHOSEN			0x07

// NomenclatureVersion
#define         NOM_VERSION1            0x80000000

// FunctionalUnits
#define         FUN_UNITS_UNIDIRECTIONAL	0x80000000
#define         FUN_UNITS_HAVETESTCAP		0x40000000
#define         FUN_UNITS_CREATETESTASSOC	0x20000000

// SystemType
#define         SYS_TYPE_MANAGER        0x80000000
#define         SYS_TYPE_AGENT          0x00800000

// ConfigId
#define         MANAGER_CONFIG_RESPONSE             0x0000
#define         STANDARD_CONFIG_START               0x0001
#define         STANDARD_CONFIG_END                 0x3FFF
#define         EXTENDED_CONFIG_START               0x4000
#define         EXTENDED_CONFIG_END                 0x7FFF
#define         RESERVED_START                      0x8000
#define         RESERVED_END                        0xFFFF

// DataReqModeFlags
#define         DATA_REQ_SUPP_STOP                  0x8000
#define         DATA_REQ_SUPP_SCOPE_ALL             0x0800
#define         DATA_REQ_SUPP_SCOPE_CLASS           0x0400
#define         DATA_REQ_SUPP_SCOPE_HANDLE          0x0200
#define         DATA_REQ_SUPP_MODE_SINGLE_RSP       0x0080
#define         DATA_REQ_SUPP_MODE_TIME_PERIOD      0x0040
#define         DATA_REQ_SUPP_MODE_TIME_NO_LIMIT    0x0020
#define         DATA_REQ_SUPP_PERSON_ID             0x0010
#define         DATA_REQ_SUPP_INIT_AGENT            0x0001

// AssociationVersion;
#define         ASSOC_VERSION1               0x80000000

// ProtocolVersion;
#define         PROTOCOL_VERSION1            0x80000000

// EncodingRules;
#define         MDER      0x8000
#define         XER       0x4000
#define         PER       0x2000

// DataProtoId;
#define         DATA_PROTO_ID_20601          20601
#define         DATA_PROTO_ID_EXTERNAL       0xFFFF

// DataReqModeFlags
#define         DATA_REQ_SUPP_STOP                  0x8000
#define         DATA_REQ_SUPP_SCOPE_ALL             0x0800
#define         DATA_REQ_SUPP_SCOPE_CLASS           0x0400
#define         DATA_REQ_SUPP_SCOPE_HANDLE          0x0200
#define         DATA_REQ_SUPP_MODE_SINGLE_RSP       0x0080
#define         DATA_REQ_SUPP_MODE_TIME_PERIOD      0x0040
#define         DATA_REQ_SUPP_MODE_TIME_NO_LIMIT    0x0020
#define         DATA_REQ_SUPP_PERSON_ID             0x0010
#define         DATA_REQ_SUPP_INIT_AGENT            0x0001

// DataReqId
#define			DATA_REQ_ID_MANAGER_INITIATED_MIN	0x0000
#define			DATA_REQ_ID_MANAGER_INITIATED_MAX	0xEFFF
#define			DATA_REQ_ID_AGENT_INITIATED			0xF000

// MdsTimeCapState
#define         MDS_TIME_CAPAB_REAL_TIME_CLOCK              0x8000
#define         MDS_TIME_CAPAB_SET_CLOCK                    0x4000
#define         MDS_TIME_CAPAB_RELATIVE_TIME                0x2000
#define         MDS_TIME_CAPAB_HIGH_RES_RELATIVE_TIME       0x1000
#define         MDS_TIME_CAPAB_SYNC_ABS_TIME                0x0800
#define         MDS_TIME_CAPAB_SYNC_REL_TIME                0x0400
#define         MDS_TIME_CAPAB_SYNC_HI_RES_RELATIVE_TIME    0x0200
#define         MDS_TIME_CAPAB_BO_TIME                      0x0100
#define         MDS_TIME_STATE_ABS_TIME_SYNCED              0x0080
#define         MDS_TIME_STATE_REL_TIME_SYNCED              0x0040
#define         MDS_TIME_STATE_HI_RES_RELATIVE_TIME_SYNCED  0x0020
#define         MDS_TIME_MGR_SET_TIME                       0x0010
#define         MDS_TIME_CAPAB_SYNC_BO_TIME                 0x0008
#define         MDS_TIME_STATE_BO_TIME_SYNCED               0x0004

// MetricSpecSmall
#define         MSS_AVAIL_INTERMITTENT          0x8000
#define         MSS_AVAIL_STORED_DATA           0x4000
#define         MSS_UPD_APERIODIC               0x2000
#define         MSS_MSMT_APERIODIC              0x1000
#define         MSS_MSMT_PHYS_EV_ID             0x0800
#define         MSS_MSMT_BTB_METRIC             0x0400
#define         MSS_ACC_MANAGER_INITIATED       0x0080
#define         MSS_ACC_AGENT_INITIATED         0x0040
#define         MSS_CAT_MANUAL                  0x0008
#define         MSS_CAT_SETTING                 0x0004
#define         MSS_CAT_CALCULATION             0x0002

// MetricStructureSmall
#define MS_STRUCT_SIMPLE		0
#define MS_STRUCT_COMPOUND		1
#define MS_STRUCT_RESERVED		2
#define MS_STRUCT_COMPOUND_FIX	3

// Associate_result
#define         ACCEPTED                             0
#define         REJECTED_PERMANENT                   1
#define         REJECTED_TRANSIENT                   2
#define         ACCEPTED_UNKNOWN_CONFIG              3
#define         REJECTED_NO_COMMON_PROTOCOL          4
#define         REJECTED_NO_COMMON_PARAMETER         5
#define         REJECTED_UNKNOWN                     6
#define         REJECTED_UNAUTHORIZED                7
#define         REJECTED_UNSUPPORTED_ASSOC_VERSION   8

// ConfigResult
#define         ACCEPTED_CONFIG                     0x0000
#define         UNSUPPORTED_CONFIG                  0x0001
#define         STANDARD_CONFIG_UNKNOWN             0x0002

// Abort_reason
#define         ABORT_REASON_UNDEFINED                0
#define         ABORT_REASON_BUFFER_OVERFLOW          1
#define         ABORT_REASON_RESPONSE_TIMEOUT         2
#define         ABORT_REASON_CONFIGURATION_TIMEOUT    3

// Release_request_reason
#define         RELEASE_REQUEST_REASON_NORMAL                 0
#define         RELEASE_REQUEST_REASON_NO_MORE_CONFIGURATIONS 1
#define         RELEASE_REQUEST_REASON_CONFIGURATION_CHANGED  2

// Release_response_reason
#define         RELEASE_RESPONSE_REASON_NORMAL        0
