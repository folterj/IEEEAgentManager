#pragma once

#include "DevSpec.h"
#include "SendState.h"
#include "DelimLine.h"
#include "PrecisionFloat.h"
#include "DevObservation.h"

using namespace System;

ref class DevHL7
{
private:
	// general constants
	static String^ headerHeader = "MSH";
	static String^ requestHeader = "OBR";
	static String^ obsHeader = "OBX";

	static String^ numericType = "NM";
	static String^ codedType = "CWE";
	static String^ stringType = "ST";
	static String^ productionId = "P";
	static String^ debuggingId = "D";
	static String^ trainingId = "T";
	static String^ statusResult = "R";
	static String^ statusFixed = "X";

	// specific constants
	static String^ gatewayNameSpace = "AMGateway";
	static String^ serviceIdentifier = "182777000^^SNOMED-CT";
	static String^ serviceIdentifierFull = "182777000^monitoring of patient^SNOMED-CT";

	static String^ arbOrderString = "AB12345";
	static String^ versionId = "2.6";
	static String^ encodingChars = "^~\\&";
	static String^ msgType = "ORU^R01^ORU_R01";
	static String^ msgIdPrefix = "MSGID";
	static String^ processingId = productionId;
	static String^ alwaysString = "AL";
	static String^ neverString = "NE";
	static String^ msgProfile = "IHE PCD ORU-R012006^HL7^2.16.840.1.113883.9.n.m^HL7";

	int hier1,hier2,hier3,hier4,hier5;

public:
	String^ hl7;
	DateTimeOffset timeStamp;
	SendState state;
	List<DelimLine^> hl7lines;
	int msgId;
	bool fullTextConstants;

	DevHL7();

	void construct(List<DevObservation^>^ observations,DevSpec^ devSpec,UInt64 eui,int msgId0,bool fullTextConstants0);
	void buildHL7();

	DelimLine^ createHeader(UInt64 eui);
	DelimLine^ createRequest(int i,UInt64 eui,DateTimeOffset^ start,DateTimeOffset^ end);
	DelimLine^ createDevObs(int i,DevSpec^ devSpec);
	DelimLine^ createObs(int i,UInt32 type,UInt32 unit,String^ value,DateTimeOffset^ dt);
	void hierInit();
	String^ createHier();
	bool isValidDateTime(DateTimeOffset^ dateTime);
};
