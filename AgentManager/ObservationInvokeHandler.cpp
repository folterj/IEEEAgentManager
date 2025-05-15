#include "StdAfx.h"
#include "ObservationInvokeHandler.h"
#include "DevObservation.h"
#include "Prst.h"
#include "EventReport.h"
#include "ScanList.h"
#include "ScanItemList.h"
#include "ValList.h"
#include "nomenclature.h"
#include "phd_constants.h"
#include "util.h"


ObservationInvokeHandler::ObservationInvokeHandler(AMState minimumState0,ReportType reportType0,int reportNo0,bool confirmed0)
	: InvokeHandler(minimumState0,confirmed0)
{
	reportType = reportType0;
	reportNo = reportNo0;
}

Apdu^ ObservationInvokeHandler::construct(DevSpec^ devSpec,int invokeId,List<DevObservation^>^ observations)
{
	this->invokeId = invokeId;

	switch (reportType) {
		case ReportType::ObservationFixed:
		case ReportType::ObservationVar:
			return constructScanReportObservation(devSpec,observations);
			break;
		case ReportType::Attribute:
			return constructScanReportAttribute(devSpec);
			break;
	}

	return nullptr;
}

Apdu^ ObservationInvokeHandler::constructScanReportObservation(DevSpec^ devSpec,List<DevObservation^>^ observations)
{
	Apdu^ apdu = gcnew Apdu();
	Prst^ prst = gcnew Prst();
	IAcse^ iacse = prst->iacse;
	EventReport^ eventReport = gcnew EventReport(1,true);
	ScanList^ scanList;
	array<Field^>^ scanItems;
	bool fixedObs = (reportType == ReportType::ObservationFixed);

	int nobs = 0;
	int obsi = 0;

	// Count # observations to encode
	for each (DevObservation^ observation in observations->ToArray()) {
		if (observation->state == SendState::New) {
			nobs++;
		}
	}

	if (fixedObs) {
		scanList = gcnew ScanList(MDC_NOTI_SCAN_REPORT_FIXED);
	} else {
		scanList = gcnew ScanList(MDC_NOTI_SCAN_REPORT_VAR);
	}

	scanItems = gcnew array<Field^>(nobs);

	for each (DevObservation^ observation in observations->ToArray()) {

		if (observation->state == SendState::New) {
			// only encode new observation

			if (fixedObs) {
				scanItems[obsi] = createScanFixedObs(devSpec,observation);
			} else {
				scanItems[obsi] = createScanVarObs(devSpec,observation,true);
			}

			observation->invokeId = invokeId;
			observation->reportNo = reportNo;
			observation->state = SendState::Sending;

			obsi++;
		}
	}
	scanList->reqId->set(DATA_REQ_ID_AGENT_INITIATED);
	scanList->reportNo->set(reportNo);
	scanList->obsCount->set(nobs);
	scanList->items = scanItems;

	eventReport->objHandle->set(0);
	if (fixedObs) {
		eventReport->eventType->set(MDC_NOTI_SCAN_REPORT_FIXED);
	} else {
		eventReport->eventType->set(MDC_NOTI_SCAN_REPORT_VAR);
	}
	eventReport->eventTime->set(0xFFFFFFFF);
	eventReport->eventItems[0] = scanList;

	iacse->invokeId->set(invokeId);
	if (confirmed) {
		iacse->roseType->set(ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN);
	} else {
		iacse->roseType->set(ROIV_CMIP_EVENT_REPORT_CHOSEN);
	}
	iacse->rose = eventReport;

	apdu->acseType->set(PRST_CHOSEN);
	apdu->acse = prst;

	sentApdu = apdu;
	return apdu;
}

Apdu^ ObservationInvokeHandler::constructScanReportAttribute(DevSpec^ devSpec)
{
	Apdu^ apdu = gcnew Apdu();
	Prst^ prst = gcnew Prst();
	IAcse^ iacse = prst->iacse;
	EventReport^ eventReport = gcnew EventReport(1,true);
	ScanList^ scanList;
	array<Field^>^ scanItems;

	bool reportObject;
	int nobs = 0;
	int obsi = 0;

	// Count # attribute objects to encode
	for each (DevObject^ object in devSpec->objects) {
		reportObject = false;
		for each (DevAttribute^ attr in object->attributes) {
			if (attr->report) {
				reportObject = true;
			}
		}
		if (reportObject) {
			nobs++;
		}
	}

	scanList = gcnew ScanList(MDC_NOTI_SCAN_REPORT_VAR);

	scanItems = gcnew array<Field^>(nobs);

	for each (DevObject^ object in devSpec->objects) {
		reportObject = false;
		for each (DevAttribute^ attr in object->attributes) {
			if (attr->report) {
				reportObject = true;
			}
		}

		if (reportObject) {
			scanItems[obsi] = createScanVarAttr(devSpec,object);
			obsi++;
		}
	}
	scanList->reqId->set(DATA_REQ_ID_AGENT_INITIATED);
	scanList->reportNo->set(reportNo);
	scanList->obsCount->set(nobs);
	scanList->items = scanItems;

	eventReport->objHandle->set(0);
	eventReport->eventType->set(MDC_NOTI_SCAN_REPORT_VAR);
	eventReport->eventTime->set(0xFFFFFFFF);
	eventReport->eventItems[0] = scanList;

	iacse->invokeId->set(invokeId);
	if (confirmed) {
		iacse->roseType->set(ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN);
	} else {
		iacse->roseType->set(ROIV_CMIP_EVENT_REPORT_CHOSEN);
	}
	iacse->rose = eventReport;

	apdu->acseType->set(PRST_CHOSEN);
	apdu->acse = prst;

	sentApdu = apdu;
	return apdu;
}

Field^ ObservationInvokeHandler::createScanFixedObs(DevSpec^ devSpec,DevObservation^ observation)
{
	ObservationField^ observationField = gcnew ObservationField();
	DevObject^ object;
	ArrayList^ map;
	int objectHandle;
	array<UInt16>^ val;

	objectHandle = observation->objectHandle;	// find object definition in spec

	observationField->objectHandle->set(objectHandle);

	object = devSpec->findObject(objectHandle);
	if (object) {
		// object defined in spec
		val = gcnew array<UInt16>(0);
		// find map
		map = object->findMap();

		for each (DevAttribute^ mapAttr in map) {
			// encode observation according to map
			val = serialiseScanObsValue(val,observation,object,mapAttr);
		}
		observationField->value = gcnew Field(val->Length * 2);
		observationField->value->set(val);
	}
	return observationField;
}

Field^ ObservationInvokeHandler::createScanVarObs(DevSpec^ devSpec,DevObservation^ observation,bool addUnit)
{
	ScanItemList^ itemList = gcnew ScanItemList();
	DevObject^ object;
	ArrayList^ map;
	int objectHandle;
	AttributeField^ attrField;
	array<AttributeField^>^ attrFields;
	array<UInt16>^ val;
	int nfields;
	int i = 0;

	objectHandle = observation->objectHandle;	// find object definition in spec

	itemList->objectHandle->set(objectHandle);

	object = devSpec->findObject(objectHandle);
	if (object) {
		// object defined in spec
		// find map
		map = object->findMap();

		nfields = map->Count;
		if (addUnit) {
			nfields++;
		}

		attrFields = gcnew array<AttributeField^>(nfields);

		for each (DevAttribute^ mapAttr in map) {
			// encode observation according to map

			attrField = gcnew AttributeField();
			attrField->id->set(mapAttr->id);
			
			val = gcnew array<UInt16>(0);
			val = serialiseScanObsValue(val,observation,object,mapAttr);

			attrField->value = gcnew Field(val->Length * 2);
			attrField->value->set(val);

			attrFields[i++] = attrField;
		}
		if (addUnit) {
			// add unit attribute
			attrField = gcnew AttributeField();
			attrField->id->set(MDC_ATTR_UNIT_CODE);

			attrField->value = gcnew Field(2);
			attrField->value->set(object->getUnit());

			attrFields[i++] = attrField;
		}
	}

	itemList->items = attrFields;

	return itemList;
}

Field^ ObservationInvokeHandler::createScanVarAttr(DevSpec^ devSpec,DevObject^ object)
{
	ScanItemList^ itemList = gcnew ScanItemList();
	AttributeField^ attrField;
	array<AttributeField^>^ attrFields;
	int nfields = 0;
	int i = 0;

	for each (DevAttribute^ attr in object->attributes) {
		if (attr->report) {
			nfields++;
		}
	}

	attrFields = gcnew array<AttributeField^>(nfields);

	for each (DevAttribute^ attr in object->attributes) {
		if (attr->report) {
			attrField = gcnew AttributeField();
			attrField->id->set(attr->id);

			attrField->value = gcnew Field(attr->len);
			attrField->value->set(attr->val);

			attrFields[i++] = attrField;

			attr->report = false;
		}
	}

	itemList->objectHandle->set(object->objectHandle);
	itemList->items = attrFields;

	return itemList;
}

array<UInt16>^ ObservationInvokeHandler::serialiseScanObsValue(array<UInt16>^ val,DevObservation^ observation,DevObject^ object,DevAttribute^ mapAttr)
{
	ArrayList^ list;
	int valLen;

	if (mapAttr->id == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC || mapAttr->id == MDC_ATTR_NU_CMPD_VAL_OBS_SIMP) {
		// compound
		if (mapAttr->id == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC) {
			valLen = 2;
		} else {
			valLen = 4;
		}
		// compound; find list
		list = object->findList();
		if (list && observation->compound) {
			// compound observation
			val = serialise(val,(UInt16)list->Count);				// count
			val = serialise(val,(UInt16)(list->Count * valLen));	// length
			// * could iterate through list (...list->Count)
			// and even match id against compound observation id

			for each (UInt32 value in observation->compoundValues) {
				if (valLen == 2) {
					val = serialise(val,(UInt16)value);
				} else {
					val = serialise(val,value);
				}
			}
		}
	} else if (mapAttr->id == MDC_ATTR_TIME_STAMP_ABS) {
		// timestamp
		val = serialise(val,dateTimeToHexString(observation->timeStamp));
	} else {
		// normal observation
		valLen = mapAttr->len;
		if (valLen == 2) {
			val = serialise(val,(UInt16)observation->value);
		} else {
			val = serialise(val,observation->value);
		}
	}
	return val;
}

ReturnInfo^ ObservationInvokeHandler::processResponse(IAcse^ iacse,UInt16 roseType,UInt16 type,List<DevObservation^>^ observations)
{
	ReturnInfo^ info = gcnew ReturnInfo();

	for each (DevObservation^ observation in observations) {
		if (observation->invokeId == invokeId) {

			switch (type) {
				case RORS:
					// ok
					if (observation) {
						observation->state = SendState::Sent;
						//observations->Remove(observation);
					}
					info->code = ReturnCode::Ok;
					break;
				case RORJ:
					// reject
					if (observation) {
						observation->state = SendState::Sent;
						//observations->Remove(observation);
					}
					info->code = ReturnCode::Ok;
					break;
				case ROER:
					// error
					if (observation) {
						observation->state = SendState::Sent;
						//observations->Remove(observation);
					}
					info->code = ReturnCode::Ok;
					break;
			}
		}
	}
	return info;
}
