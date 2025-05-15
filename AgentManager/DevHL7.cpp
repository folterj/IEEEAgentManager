#include "StdAfx.h"
#include "DevHL7.h"
#include "DevObservation.h"
#include "util.h"
#include "nomenclature.h"
#include "conversion.h"


DevHL7::DevHL7()
{
	hl7 = "";
	timeStamp = DateTimeOffset::Now;
	state = SendState::New;
	hierInit();
}

void DevHL7::construct(List<DevObservation^>^ observations,DevSpec^ devSpec,UInt64 eui,int msgId0,bool fullTextConstants0)
{
	// construct HL7 lines
	DateTimeOffset^ start = gcnew DateTimeOffset();
	DateTimeOffset^ end = gcnew DateTimeOffset();
	DevObject^ object;
	DevAttribute^ attribute;
	ArrayList^ list;
	String^ value;
	UInt32 type,unit,unit0;
	int obsi = 0;
	int listi;
	bool firstObservation = true;

	msgId = msgId0;
	fullTextConstants = fullTextConstants0;

	hl7lines.Clear();
	hierInit();

	hl7lines.Add(createDevObs(++obsi,devSpec));

	for each (DevObservation^ observation in observations) {

		if (observation->state == SendState::New) {

			object = devSpec->findObject(observation->objectHandle);
			type = 0;
			if (object) {
				type = object->getType();
			}
			unit = 0;
			if (object) {
				// check if unit attribute is present
				attribute = object->findAttribute(MDC_ATTR_UNIT_CODE);
				if (attribute) {
					unit = (UInt32)object->getUnit() | (MDC_PART_DIM * 0x10000);
				}
			}
			if (observation->compound) {
				// hide value and unit in compound observations header obs line
				value = "";
				unit0 = 0;
				hier3 = observation->objectHandle;
				hier4 = 0;
			} else {
				value = observation->ToString(observation->value,type,fullTextConstants);
				unit0 = unit;
				hier3 = 0;
				hier4 = observation->objectHandle;
			}

			hl7lines.Add(createObs(++obsi,type,unit0,value,observation->timeStamp));

			if (observation->compound) {
				// compound observation
				list = nullptr;
				if (object) {
					list = object->findList();
				}
				listi = 0;
				for each (UInt32 compValue in observation->compoundValues) {
					if (list) {
						attribute = (DevAttribute^)list[listi++];
						type = attribute->id | (MDC_PART_SCADA * 0x10000);
					}
					value = observation->ToString(compValue,type,fullTextConstants);
					hier4 = listi;
					hl7lines.Add(createObs(++obsi,type,unit,value,nullptr));
				}
			}

			if (observation->timeStamp.CompareTo(*start) < 0 || firstObservation) {
				start = observation->timeStamp;
			}
			if (observation->timeStamp.CompareTo(*end) > 0 || firstObservation) {
				end = observation->timeStamp;
			}
			observation->state = SendState::Sending;
			firstObservation = false;
		}
	}
	hl7lines.Insert(0,createRequest(1,eui,start,end));
	hl7lines.Insert(0,createHeader(eui));

	buildHL7();
}

void DevHL7::buildHL7()
{
	// build hl7 string
	hl7 = "";
	for each (DelimLine^ line in hl7lines) {
		hl7 += line->toString();
		hl7 += "\r\n";
	}
}

DelimLine^ DevHL7::createHeader(UInt64 eui)
{
	DelimLine^ header = gcnew DelimLine();

	header[0] = headerHeader;
	header[1] = encodingChars;
	header[2] = String::Format("{0}^{1:X16}^EUI-64",gatewayNameSpace,eui);
	header[6] = toHL7String(timeStamp);
	header[8] = msgType;
	header[9] = String::Format("{0}{1:00000}",msgIdPrefix,msgId);
	header[10] = processingId;
	header[11] = versionId;
	header[14] = neverString;
	header[15] = alwaysString;
	header[20] = msgProfile;

	return header;
}

DelimLine^ DevHL7::createRequest(int i,UInt64 eui,DateTimeOffset^ start,DateTimeOffset^ end)
{
	DelimLine^ request = gcnew DelimLine();

	request[0] = requestHeader;
	request[1] = String::Format("{0}",i);
	request[2] = String::Format("{0}^{1}^{2:X16}^EUI-64",arbOrderString,gatewayNameSpace,eui);
	request[3] = String::Format("{0}^{1}^{2:X16}^EUI-64",arbOrderString,gatewayNameSpace,eui);
	if (fullTextConstants) {
		request[4] = serviceIdentifierFull;
	} else {
		request[4] = serviceIdentifier;
	}
	if (start) {
		if (isValidDateTime(start)) {
			request[7] = toHL7String(start);
		}
	}
	if (end) {
		if (isValidDateTime(end)) {
			request[8] = toHL7String(end);
		}
	}
	
	return request;
}

DelimLine^ DevHL7::createDevObs(int i,DevSpec^ devSpec)
{
	DelimLine^ obs = gcnew DelimLine();
	DevObject^ object;
	DevAttribute^ attribute;
	array<UInt16>^ val;
	UInt32 sysType;
	UInt64 devEUI;
	String^ text;

	object = devSpec->findObject(0);
	if (object) {
		// get sysType
		attribute = object->findAttribute(MDC_ATTR_SYS_TYPE_SPEC_LIST);
		if (attribute) {
			val = attribute->val;
			sysType = val[2] | (MDC_PART_INFRA * 0x10000);
		}
		// get EUI64
		attribute = object->findAttribute(MDC_ATTR_SYS_ID);
		if (attribute) {
			devEUI = attribute->getVal();
		}
	}

	obs[0] = obsHeader;
	obs[1] = String::Format("{0}",i);
	text = "";
	if (fullTextConstants) {
		text = devTypeIdFull(sysType);
	}
	obs[3] = String::Format("{0}^{1}^MDC",sysType,text);
	obs[4] = createHier();
	obs[11] = statusFixed;
	obs[18] = String::Format("{0:X16}^EUI-64",devEUI);

	return obs;
}

DelimLine^ DevHL7::createObs(int i,UInt32 type,UInt32 unit,String^ value,DateTimeOffset^ dt)
{
	DelimLine^ obs = gcnew DelimLine();
	String^ text;

	obs[0] = obsHeader;
	obs[1] = String::Format("{0}",i);
	if (type != 0) {
		text = "";
		if (fullTextConstants) {
			text = typeIdFull(type);
		}
		obs[3] = String::Format("{0}^{1}^MDC",type,text);
	}
	obs[4] = createHier();
	if (value) {
		obs[2] = numericType;
		obs[5] = value;
	}
	if (unit != 0) {
		text = "";
		if (fullTextConstants) {
			text = unitIdFull(unit);
		}
		obs[6] = String::Format("{0}^{1}^MDC",unit,text);
	}
	obs[11] = statusResult;
	if (dt) {
		if (isValidDateTime(dt)) {
			obs[14] = toHL7String(dt);
		}
	}

	return obs;
}

void DevHL7::hierInit()
{
	hier1 = 1;
	hier2 = 0;
	hier3 = 0;
	hier4 = 0;
	hier5 = 0;
}

String^ DevHL7::createHier()
{
	String^ format = "";

	if (hier5 != 0) {
		format = "{0}.{1}.{2}.{3}.{4}";
	} else if (hier4 != 0) {
		format = "{0}.{1}.{2}.{3}";
	} else if (hier3 != 0) {
		format = "{0}.{1}.{2}";
	} else if (hier2 != 0) {
		format = "{0}.{1}";
	} else if (hier1 != 0) {
		format = "{0}";
	}
	return String::Format(format,hier1,hier2,hier3,hier4,hier5);
}

bool DevHL7::isValidDateTime(DateTimeOffset^ dateTime)
{
	return (dateTime->Year > 1);
}
