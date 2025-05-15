#pragma once

public enum class ComCommand
{
	None,
	Query,
	QueryResp,
	Connect,
	ConnectResp,
	Disconnect,
	DisconnectResp,
	Remove
};

enum class ReturnCode
{
	Ok,
	Reject,
	Error,
	Abort,
	Nothing
};

enum class AMState
{
	NoChange,
	Disconnected,
	Unassociated,
	Associating,
	Config_Sending,
	Config_Checking,
	Operating,
	Disassociating
};

enum class AMEvent
{
	None,
	Ind_Trans_Con,
	Ind_Trans_Discon,
	Ind_Timeout,
	Ind_TimeoutMax,
	Req_Assoc,
	Req_AssocRelease,
	Req_AssocAbort,
	Rx_Aarq,
	Req_ConfigAcceptKnown,
	Req_ConfigAcceptUnknown,
	Req_ConfigReject,
	Rx_Aare,
	Rx_Aare_AcceptKnown,
	Rx_Aare_AcceptUnknown,
	Rx_Aare_Reject,
	Rx_Rlrq,
	Rx_Rlre,
	Rx_Abrt,
	Rx_Apdu_Other,
	Req_ConfigEvent,
	Rx_Roiv,
	Rx_Roiv_Mds,
	Rx_Roiv_NonMds,
	Rx_Roiv_EventReport,
	Rx_Roiv_Other,
	Rx_RorsRoerRorj,
	Rx_Rors_EventReport_Unsup_AddConfig,
	Rx_Rors_EventReport_Unsup,
	Rx_Rors_EventReport_Accept,
	Rx_RorsRoerRorj_Other,
	Req_ConfigUnsup,
	Req_ConfigSup,
	Ind_App_EventReport,
	Req_Roiv_Other
};

enum AMAction
{
	None,
	OK,
	AB,		// abort
	SAB,	// send abort
	SAR,	// send abort (Response Timeout)
	SAC,	// send abort (Config Timeout)
	ERR,	// send error response
	AS,		// associate request
	DIS,	// associate release
	CFG
};

public enum class ComType
{
	None,
	MessageQueue,
	SerialPort,
	TCP,
	HTTP
};

public enum class ReportType
{
	Unknown,
	ObservationFixed,
	ObservationVar,
	Attribute
};

public enum class MDC_AI_TYPE_SENSOR_FALL_flags
{
	fall_detected			= 0,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_PERS_flags
{
	pers_activated			= 0,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_substance_flags
{
	condition_detected		= 0,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_MOTION_flags
{
	motion_detected			= 0,
	motion_detected_delayed	= 1,
	tamper_detected			= 2,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_PROPEXIT_flags
{
	occupant_exit_property	= 0,
	exit_door_left_open		= 1,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_ENURESIS_flags
{
	enuresis_detected		= 0,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_CONTACTCLOSURE_flags
{
	contact_opened			= 0,
	contact_closed			= 1,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_USAGE_flags
{
	usage_started					= 0,
	usage_ended						= 1,
	expected_use_start_violation	= 2,
	expected_use_stop_violation		= 3,
	absence_violation				= 4,
	auto_presence_received			= 16,
	auto_presence_failed			= 17,
	low_battery						= 18,
	fault							= 19,
	end_of_life						= 20
};

public enum class MDC_AI_TYPE_SENSOR_SWITCH_flags
{
	switch_on				= 0,
	switch_off				= 1,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_DOSAGE_flags
{
	dosage_taken			= 0,
	dosage_missed			= 1,
	auto_presence_received	= 16,
	auto_presence_failed	= 17,
	low_battery				= 18,
	fault					= 19,
	end_of_life				= 20
};

public enum class MDC_AI_TYPE_SENSOR_TEMP_flags
{
	high_temperature_detected	= 0,
	low_temperature_detected	= 1,
	rate_of_change_too_fast		= 2,
	auto_presence_received		= 16,
	auto_presence_failed		= 17,
	low_battery					= 18,
	fault						= 19,
	end_of_life					= 20
};
