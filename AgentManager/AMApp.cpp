#include "StdAfx.h"
#include "AMApp.h"
#include "MdsInvokeHandler.h"
#include "ConfigInvokeHandler.h"
#include "ActionInvokeHandler.h"
#include "ObservationInvokeHandler.h"
#include "nomenclature.h"
#include "phd_constants.h"
#include "EventReport.h"
#include "ObjectList.h"
#include "ScanList.h"
#include "ValMap.h"
#include "ValList.h"
#include "Report.h"
#include "MdsAttributeList.h"
#include "ActionMethod.h"
#include "ActionResult.h"
#include "util.h"


AMApp::AMApp(AMModelInterface^ model0,ComInterface^ com0,UInt64 eui0,String^ spec0)
{
	model = model0;
	com = com0;
	eui = eui0;
	spec = spec0;
	specType = (SpecType)Enum::Parse(SpecType::typeid,spec);
	state = AMState::Disconnected;
	invokeSending = false;
	newInvokeId = 0;
	newHL7MsgId = 0;
	newReportNo = 0;

	com->registerObserver(this);
	sender = gcnew ApduSender(com);

	invokeTimer.Interval = 500;	// 500 ms time out; to prevent lock up
	invokeTimer.AutoReset = false;
	invokeTimer.Elapsed += gcnew ElapsedEventHandler(this,&AMApp::invokeTimer_Elapsed);
}

void AMApp::removed()
{
	isconnected = false;
	state = AMState::NoChange;
	model->updateSpec(eui,spec,getState(),ComCommand::Remove);
	// this app will get deleted now
}

UInt64 AMApp::getEui()
{
	return eui;
}

DevSpec^ AMApp::getDevSpec()
{
	return devSpec;
}

String^ AMApp::getSpec()
{
	return spec;
}

String^ AMApp::getState()
{
	return Enum::GetName(AMState::typeid,state);
}

ComInterface^ AMApp::getCom()
{
	return com;
}

bool AMApp::send(Apdu^ apdu)
{
	bool ok;
	String^ shortdesc;
	String^ fulldesc;

	array<Byte>^ data = apdu->encode();
	shortdesc = apdu->getShortDesc();
	fulldesc = apdu->getFullDesc();

	ok = sender->addSend(data);
	model->newCom(eui,DateTime::Now,data,shortdesc,fulldesc,false,ok);
	return ok;
}

Object^ AMApp::dataReceived(Object^ data0,bool expectResponse)
{
	if (data0->GetType() != String::typeid) {
		// Make sure format is not a string
		array<Byte>^ data = (array<Byte>^)data0;
		String^ shortdesc;
		String^ fulldesc;
		bool valid;

		Apdu^ apdu = gcnew Apdu();
		valid = apdu->decode(data);

		shortdesc = apdu->getShortDesc();
		fulldesc = apdu->getFullDesc();

		model->newCom(eui,DateTime::Now,data,shortdesc,fulldesc,true,valid);

		processApdu(apdu,valid);
	}
	return nullptr;
}

void AMApp::confReceived()
{
	sender->confReceived();
}

void AMApp::createScanReport(ReportType reportType,bool confirmed)
{
	if (reportType == ReportType::Attribute) {
		createScanAttribute(reportType,confirmed);
	} else {
		createScanObservation(reportType,confirmed);
	}
}

void AMApp::createScanObservation(ReportType reportType,bool confirmed)
{
	DevObservation^ observation;
	ArrayList^ map;
	int dataLen;

	for each (DevObject^ object in devSpec->objects) {
		if (object->objectHandle != 0) {
			dataLen = 0;
			// find map
			map = object->findMap();
			// find data length
			for each (DevAttribute^ mapAttr in map) {
				if (!object->compound && mapAttr->id != MDC_ATTR_TIME_STAMP_ABS) {
					dataLen = mapAttr->len;
				}
			}

			observation = gcnew DevObservation(object->objectHandle);
			if (object->objectClass == MDC_MOC_VMO_METRIC_ENUM) {
				// enum
				if (object->compound) {
				} else {
					observation->setEnum((UInt32)1);
				}
			} else {
				// numeric
				// ** asume 16 bit, but could be 32 bit, and therefor decoded like 32 bit! (i.e. scales)
				if (object->compound) {
					observation->addCompoundNum16(120,0);
					observation->addCompoundNum16(80,0);
					observation->addCompoundNum16(100,0);
				} else {
					if (dataLen == 2) {
						observation->setNum16(60,1);
					} else if (dataLen == 4) {
						observation->setNum32(60,1);
					}
				}
			}
			observations.Add(observation);
			model->newObs(eui,observation);
		}
	}

	if (reportType == ReportType::ObservationFixed) {
		sendScanObservationFixed(confirmed);
	} else {
		sendScanObservationVar(confirmed);
	}
	model->updateObs();
}

void AMApp::createScanAttribute(ReportType reportType,bool confirmed)
{
	// mark attributes: report
	// * for now: report all (except map/list)
	for each (DevObject^ object in devSpec->objects) {
		for each (DevAttribute^ attr in object->attributes) {
			if (attr->id != MDC_ATTR_ATTRIBUTE_VAL_MAP && attr->id != MDC_ATTR_ID_PHYSIO_LIST) {
				// don't mark map/list
				attr->report = true;
			}
		}
	}
	sendScanAttribute(confirmed);
}

void AMApp::sendMdsGet()
{
	addInvoke(gcnew MdsInvokeHandler(AMState::Config_Sending));
}

void AMApp::sendConfig()
{
	addInvoke(gcnew ConfigInvokeHandler(AMState::Config_Sending));
}

void AMApp::sendAction(bool confirmed)
{
	addInvoke(gcnew ActionInvokeHandler(AMState::Operating,confirmed));
}

void AMApp::sendScanObservationFixed(bool confirmed)
{
	ObservationInvokeHandler^ obsInvokeHandler = gcnew ObservationInvokeHandler(
		AMState::Operating,
		ReportType::ObservationFixed,
		newReportNo++,
		confirmed);

	addInvoke(obsInvokeHandler);
}

void AMApp::sendScanObservationVar(bool confirmed)
{
	ObservationInvokeHandler^ obsInvokeHandler = gcnew ObservationInvokeHandler(
		AMState::Operating,
		ReportType::ObservationVar,
		newReportNo++,
		confirmed);

	addInvoke(obsInvokeHandler);
}

void AMApp::sendScanAttribute(bool confirmed)
{
	ObservationInvokeHandler^ obsInvokeHandler = gcnew ObservationInvokeHandler(
		AMState::Operating,
		ReportType::Attribute,
		newReportNo++,
		confirmed);

	addInvoke(obsInvokeHandler);
}

bool AMApp::addInvoke(InvokeHandler^ invoke)
{
	invokes.Add(invoke);
	return sendNextInvoke();
}

bool AMApp::sendNextInvoke()
{
	InvokeHandler^ sentInvoke;
	bool ok = true;

	if (!invokeSending) {
		for each (InvokeHandler^ invoke in invokes) {
			if (invoke->state == SendState::New && state >= invoke->minimumState) {
				// check pending invokes; suitable state to send
				invokeSending = true;
				Apdu^ apdu = invoke->construct(devSpec,newInvokeId++,%observations);
				ok = send(apdu);
				if (ok) {
					invoke->state = SendState::Sending;
					sentInvoke = invoke;
				}
				invokeTimer.Stop();
				invokeTimer.Start();
				break;
			}
		}
		if (sentInvoke) {
			if (!sentInvoke->confirmed) {
				// invoke that was sent does not expect response -> remove
				invokes.Remove(sentInvoke);
			}
		}
	}
	return ok;
}

void AMApp::invokeTimer_Elapsed(Object^ sender, ElapsedEventArgs^ e)
{
	// invoke time out; prevent lock up
	invokeSending = false;
	// * display / log error?
	sendNextInvoke();
}

void AMApp::clearInvokes()
{
	invokes.Clear();
	invokeTimer.Stop();
	invokeSending = false;
}

void AMApp::clearQueues()
{
	clearInvokes();
	sender->clearAll();
}

void AMApp::processApdu(Apdu^ apdu,bool valid)
{
	ReturnCode returnCode;

	Apdu^ responseApdu = gcnew Apdu();
	Field^ responseAcse;
	IAcse^ responseIAcse;
	UInt16 acseType;
	UInt16 responseType = PRST_CHOSEN;
	bool mdsGet = false;

	if (!valid) {
		handleEvent(AMEvent::Req_AssocAbort);
		return;
	}

	acseType = (UInt16)apdu->acseType->get();

	switch (acseType) {
		case AARQ_CHOSEN:
			returnCode = handleEvent(AMEvent::Rx_Aarq);
			if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
				responseType = AARE_CHOSEN;
				responseAcse = processAssocReq((Aarq^)apdu->acse);
				mdsGet = true;
			}
			break;

		case AARE_CHOSEN:
			returnCode = handleEvent(AMEvent::Rx_Aare);
			if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
				processAssocResp((Aare^)apdu->acse);
			}
			break;

		case RLRQ_CHOSEN:
			returnCode = handleEvent(AMEvent::Rx_Rlrq);
			if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
				responseType = RLRE_CHOSEN;
				responseAcse = processReleaseReq((Rlrq^)apdu->acse);
			}
			break;

		case RLRE_CHOSEN:
			returnCode = handleEvent(AMEvent::Rx_Rlre);
			if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
				processReleaseResp((Rlre^)apdu->acse);
			}
			break;

		case ABRT_CHOSEN:
			returnCode = handleEvent(AMEvent::Rx_Abrt);
			processAbort((Abrt^)apdu->acse);
			break;

		case PRST_CHOSEN:
			IAcse^ iacse = ((Prst^)apdu->acse)->iacse;
			if (iacse) {
				responseIAcse = processRose(iacse);
				if (responseIAcse) {
					responseType = PRST_CHOSEN;
					Prst^ prst = gcnew Prst();
					prst->iacse = responseIAcse;
					responseAcse = prst;
				}
			}
			break;
	}

	if (responseAcse) {
		responseApdu->acse = responseAcse;
		responseApdu->acseType->set(responseType);
		send(responseApdu);
	}
	if (mdsGet) {
		sendMdsGet();
	}
}

IAcse^ AMApp::processRose(IAcse^ iacse)
{
	IAcse^ response;
	ReturnCode returnCode;
	ReturnInfo^ info;
	UInt16 roseType;
	UInt16 type;
	UInt16 invokeId;
	bool doSendNextInvoke = false;
	bool noResponse = false;

	roseType = (UInt16)iacse->roseType->get();
	type = roseType / 0x100;
	invokeId = (UInt16)iacse->invokeId->get();

	if (type == ROIV) {
		returnCode = handleEvent(AMEvent::Rx_Roiv);
	} else {
		returnCode = handleEvent(AMEvent::Rx_RorsRoerRorj);
		if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
			// process invoke response
			for each (InvokeHandler^ invoke in invokes.ToArray()) {
				if (invokeId == invoke->invokeId) {
					// found invoke id in invoke list; process
					info = invoke->processResponse(iacse,roseType,type,%observations);
					if (info->event != AMEvent::None) {
						handleEvent(info->event);
					}
					if (info->code == ReturnCode::Ok) {
						invoke->state = SendState::Sent;
						invokes.Remove(invoke);
						invokeTimer.Stop();
						invokeSending = false;
						doSendNextInvoke = true;
					}
					model->updateObs();	// in case observation was received
				}
			}
		}
	}

	if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
		switch (roseType) {
			case ROIV_CMIP_EVENT_REPORT_CHOSEN:
				noResponse = true;
				// no break!
			case ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN:
				returnCode = handleEvent(AMEvent::Rx_Roiv_EventReport);
				if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
					response = processEventReport(iacse);
				}
				break;
			case ROIV_CMIP_GET_CHOSEN:
				returnCode = handleEvent(AMEvent::Rx_Roiv_Mds);
				if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
					response = processMdsGet(iacse);
				}
				break;
			case RORS_CMIP_GET_CHOSEN:
				processMds(iacse);
				break;
			case ROIV_CMIP_ACTION_CHOSEN:
				noResponse = true;
				// no break!
			case ROIV_CMIP_CONFIRMED_ACTION_CHOSEN:
				response = processAction(iacse);
				break;
			case ROIV_CMIP_SET_CHOSEN:
				noResponse = true;
				// no break!
			case ROIV_CMIP_CONFIRMED_SET_CHOSEN:
			case RORS_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN:
			case RORS_CMIP_CONFIRMED_SET_CHOSEN:
			case RORS_CMIP_CONFIRMED_ACTION_CHOSEN:
			case ROER_CHOSEN:
			case RORJ_CHOSEN:
				break;
		}
	}
	if (doSendNextInvoke) {
		// see if another invoke is waiting
		sendNextInvoke();
	}
	if (!noResponse) {
		return response;
	}
	return nullptr;
}

void AMApp::sendAssocReq()
{
	Apdu^ apdu = gcnew Apdu();
	Aarq^ aarq = gcnew Aarq();
	UInt16 configId;

	configId = devSpec->configId;
	if (configId == STANDARD_CONFIG_ILAH) {
		// independent living hub: motion / usage: not standard configs
		configId = EXTENDED_CONFIG_START;
	}

	apdu->acse = aarq;
	Proto^ proto = aarq->proto;
	ProtoInfo^ protoInfo = proto->protoInfo[0];

	apdu->acseType->set(AARQ_CHOSEN);

	aarq->assocVer->set(ASSOC_VERSION1);
	aarq->protoCount->set(1);

	proto->protoId->set(DATA_PROTO_ID_20601);

	protoInfo->protoVer->set(PROTOCOL_VERSION1);
	protoInfo->encoding->set(MDER|PER);					// At least the MDER shall be supported
	protoInfo->nomVer->set(NOM_VERSION1);
	protoInfo->funcUnits->set(0);						// The field functional-units may have the test association bits set but shall not have any other bits set
	protoInfo->systemType->set(SYS_TYPE_AGENT);
	protoInfo->systemId->setLen(8);
	protoInfo->systemId->set(eui);						// Same as MDS System-Id attribute
	protoInfo->configId->set(configId);					// Same as MDS Dev-Configuration-Id attribute
	protoInfo->reqMode->set(DATA_REQ_SUPP_INIT_AGENT);	// Single specialisation: data request modes = data-req-supp-init-agent
	protoInfo->reqAgentCount->set(1);					// Single specialisation: data-req-init-agent-count = 1
	protoInfo->reqManagerCount->set(0);					// Single specialisation: data-req-initmanager-count = 0
	protoInfo->optionCount->set(0);
	protoInfo->optionLen->set(0);

	send(apdu);
}

Field^ AMApp::processAssocReq(Aarq^ aarq)
{
	UInt64 configId;
	UInt64 assocResult;
	bool known = false;

	configId = aarq->proto->protoInfo[0]->configId->get();

	if (configId != EXTENDED_CONFIG_START) {
		// check if known configId
		switch (configId) {
			case STANDARD_CONFIG_SCALE:		devSpec = gcnew ScalesSpec(eui);		known = true;	break;
			case STANDARD_CONFIG_BP:		devSpec = gcnew BloodPressureSpec(eui);	known = true;	break;
			case STANDARD_CONFIG_GLUCOSE:	devSpec = gcnew BloodGlucoseSpec(eui);	known = true;	break;
			case STANDARD_CONFIG_SPO2:		devSpec = gcnew PulseOximSpec(eui);		known = true;	break;
		}
	}
	if (!devSpec) {
		devSpec = gcnew DevSpec();
	}

	if (known) {
		handleEvent(AMEvent::Req_ConfigAcceptKnown);
		assocResult = ACCEPTED;
	} else {
		handleEvent(AMEvent::Req_ConfigAcceptUnknown);
		assocResult = ACCEPTED_UNKNOWN_CONFIG;
	}

	return createAssocResp(assocResult);
}

Field^ AMApp::createAssocResp(UInt64 assocResult)
{
	Aare^ aare = gcnew Aare();
	ProtoInfo^ protoInfo = aare->protoInfo;

	aare->assocResult->set(assocResult);
	aare->protoId->set(DATA_PROTO_ID_20601);

	protoInfo->protoVer->set(PROTOCOL_VERSION1);
	protoInfo->encoding->set(MDER);						// Single selected encoding rule supported by both agent and manager; shall support at least MDER
	protoInfo->nomVer->set(NOM_VERSION1);
	protoInfo->funcUnits->set(0);						// shall have all bits reset except for those relating to a test association
	protoInfo->systemType->set(SYS_TYPE_MANAGER);
	protoInfo->systemId->setLen(8);
	protoInfo->systemId->set(eui);						// the unique system ID of the manager device, which shall be a valid EUI-64 type identifier
	protoInfo->configId->set(MANAGER_CONFIG_RESPONSE);
	protoInfo->reqMode->set(0);							// always 0
	protoInfo->reqAgentCount->set(0);					// always 0
	protoInfo->reqManagerCount->set(0);					// always 0
	protoInfo->optionCount->set(0);
	protoInfo->optionLen->set(0);

	return aare;
}

void AMApp::processAssocResp(Aare^ aare)
{
	UInt64 assocResult;
	ReturnCode returnCode;
	bool rejected = false;
	bool known = false;

	assocResult = aare->assocResult->get();

	switch (assocResult) {
		case ACCEPTED:
			known = true;
			returnCode = handleEvent(AMEvent::Rx_Aare_AcceptKnown);
			break;
		case ACCEPTED_UNKNOWN_CONFIG:
			returnCode = handleEvent(AMEvent::Rx_Aare_AcceptUnknown);
			if (returnCode == ReturnCode::Ok || returnCode == ReturnCode::Nothing) {
				handleEvent(AMEvent::Req_ConfigSup);
			}
			break;
		case REJECTED_PERMANENT:
		case REJECTED_TRANSIENT:
		case REJECTED_NO_COMMON_PROTOCOL:
		case REJECTED_NO_COMMON_PARAMETER:
		case REJECTED_UNKNOWN:
		case REJECTED_UNAUTHORIZED:
		case REJECTED_UNSUPPORTED_ASSOC_VERSION:
		default:
			rejected = true;
			returnCode = handleEvent(AMEvent::Rx_Aare_Reject);
			// send alternative configuration?
			break;
	}
}

void AMApp::sendReleaseReq(UInt16 reason)
{
	Apdu^ apdu = gcnew Apdu();

	apdu->acse = createReleaseReq(reason);
	apdu->acseType->set(RLRQ_CHOSEN);
	
	send(apdu);
}

Field^ AMApp::createReleaseReq(UInt16 reason)
{
	Rlrq^ rlrq = gcnew Rlrq();

	rlrq->reason->set(reason);

	clearQueues();

	return rlrq;
}

Field^ AMApp::processReleaseReq(Rlrq^ rlrq)
{
	Rlre^ rlre = gcnew Rlre();
	UInt16 reason;

	reason = (UInt16)rlrq->reason->get();

	clearQueues();

	rlre->reason->set(RELEASE_RESPONSE_REASON_NORMAL);

	return rlre;
}

Field^ AMApp::createReleaseResp(UInt16 reason)
{
	Rlre^ rlre = gcnew Rlre();

	rlre->reason->set(reason);

	return rlre;
}

void AMApp::processReleaseResp(Rlre^ rlre)
{
	UInt16 reason;

	reason = (UInt16)rlre->reason->get();
}

void AMApp::sendAbort(UInt16 reason)
{
	Apdu^ apdu = gcnew Apdu();

	apdu->acse = createAbort(reason);
	apdu->acseType->set(ABRT_CHOSEN);
	
	send(apdu);
}

Field^ AMApp::createAbort(UInt16 reason)
{
	Abrt^ abrt = gcnew Abrt();

	abrt->reason->set(reason);

	clearQueues();

	return abrt;
}

void AMApp::processAbort(Abrt^ abrt)
{
	UInt16 reason;

	reason = (UInt16)abrt->reason->get();

	clearQueues();
}

IAcse^ AMApp::processMdsGet(IAcse^ iacse)
{
	// respond to MDS get by sending MDS attributes
	IAcse^ response;
	ReturnCode returnCode = ReturnCode::Ok;
	UInt16 invokeId;
	UInt16 roseType;
	UInt16 returnType;
	MdsAttributeList^ attributeList;
	AttributeField^ attr;
	ValMap^ valMap;
	ValList^ valList;

	int nattr;
	int attri;
	int nmap;
	int nlist;
	int mapi;
	int listi;

	invokeId = (UInt16)iacse->invokeId->get();
	roseType = (UInt16)iacse->roseType->get();

	for each (DevObject^ object in devSpec->objects) {
		if (object->objectHandle == 0) {
			nattr = object->attributes.Count;
			attributeList = gcnew MdsAttributeList(nattr);
			attributeList->objectHandle->set(object->objectHandle);

			attri = 0;

			for each (DevAttribute^ attribute in object->attributes) {
				attr = gcnew AttributeField();
				attr->id->set(attribute->id);
				nmap = attribute->map.Count;
				nlist = attribute->list.Count;
				if (nmap > 0) {
					// map attribute
					valMap = gcnew ValMap(nmap);
					mapi = 0;

					for each (DevAttribute^ mapattr in attribute->map) {
						valMap->maps[mapi]->id->set(mapattr->id);
						valMap->maps[mapi]->valLen->set(mapattr->len);
						mapi++;
					}
					attr->value = valMap;
				} else if (nlist > 0) {
					// list attribute
					valList = gcnew ValList(nlist,2);	// *** 2 comes from where?
					listi = 0;

					for each (DevAttribute^ listattr in attribute->list) {
						valList->vals[listi]->content->set(listattr->id);
						listi++;
					}
					attr->value = valList;
				} else {
					// simple attribute
					attr->value = gcnew Field(attribute->getLen());
					attr->value->set(attribute->val);
				}
				attributeList->attributes[attri] = attr;
				attri++;
			}
		}
	}
	if (!attributeList) {
		attributeList = gcnew MdsAttributeList(0);
		attributeList->objectHandle->set(0);
	}

	response = gcnew IAcse();
	response->rose = attributeList;
	response->invokeId->set(invokeId);
	switch (returnCode) {
		case ReturnCode::Ok:		returnType = RORS;	break;
		case ReturnCode::Reject:	returnType = RORJ;	break;
		case ReturnCode::Abort:		returnType = ROER;	break;
	}
	response->roseType->set((roseType & 0xFF) + 0x100 * returnType);

	return response;
}

void AMApp::processMds(IAcse^ iacse)
{
	MdsAttributeList^ attributeList;

	DevObject^ devobject;
	DevAttribute^ devattribute;
	DevAttribute^ mapattribute;
	DevAttribute^ listattribute;

	attributeList = (MdsAttributeList^)iacse->rose;

	devobject = gcnew DevObject();
	devobject->objectClass = 0;
	devobject->objectHandle = (UInt16)attributeList->objectHandle->get();

	for each (AttributeField^ attribute in attributeList->attributes) {
		devattribute = gcnew DevAttribute();
		devattribute->id = (UInt32)attribute->id->get();
		devattribute->len = (UInt32)attribute->valLen->get();
		if (devattribute->id == MDC_ATTR_ATTRIBUTE_VAL_MAP) {
			// map attribute
			ValMap^ valMap = (ValMap^)attribute->value;

			for each (MapField^ mapField in valMap->maps) {
				mapattribute = gcnew DevAttribute();
				mapattribute->id = (UInt32)mapField->id->get();
				mapattribute->len = (UInt32)mapField->valLen->get();
				devattribute->map.Add(mapattribute);
			}
		} else if (devattribute->id == MDC_ATTR_ID_PHYSIO_LIST) {
			// list attribute
			ValList^ valList = (ValList^)attribute->value;

			for each (ListField^ listField in valList->vals) {
				listattribute = gcnew DevAttribute();
				listattribute->id = (UInt32)listField->content->get();
				devattribute->list.Add(listattribute);
			}
		} else {
			// simple attribute
			devattribute->len = (UInt32)attribute->valLen->get();
			devattribute->val = attribute->value->get16array();
		}
		devobject->attributes.Add(devattribute);
	}
	devSpec->addObject(devobject);

	if (getManSetTime()) {
		// agent requests manager to set time
		sendAction(true);
	}
}

bool AMApp::getManSetTime()
{
	DevObject^ object;
	DevAttribute^ attribute;

	object = devSpec->getMdsObject();
	if (object) {
		attribute = object->findAttribute(MDC_ATTR_MDS_TIME_INFO);
		if (attribute) {
			if (attribute->getVal() & MDS_TIME_MGR_SET_TIME) {
				// agent requests manager to set time
				return true;
			}
		}
	}
	return false;
}

IAcse^ AMApp::processAction(IAcse^ iacse)
{
	IAcse^ response;
	ActionResult^ actionResult;
	ReturnCode returnCode = ReturnCode::Ok;
	ActionMethod^ action;
	UInt16 invokeId;
	UInt16 roseType;
	UInt16 returnType;
	UInt16 objectHandle;
	UInt16 actionType;
	UInt16 result;
	array<UInt16>^ val;

	action = (ActionMethod^)iacse->rose;

	invokeId = (UInt16)iacse->invokeId->get();
	roseType = (UInt16)iacse->roseType->get();
	objectHandle = (UInt16)action->objHandle->get();
	actionType = (UInt16)action->type->get();
	val = action->value->get16array();

	switch (actionType) {
		case MDC_ACT_SET_TIME:
			// * set date time
			DateTime^ newDateTime = hexStringToDateTime(val,0);
			break;
	}

	result = 0;	// Ok
	actionResult = gcnew ActionResult();
	actionResult->objHandle->set(objectHandle);
	actionResult->type->set(actionType);
	actionResult->result->set(result);

	response = gcnew IAcse();
	response->rose = actionResult;
	response->invokeId->set(invokeId);
	switch (returnCode) {
		case ReturnCode::Reject:	returnType = RORJ;	break;
		case ReturnCode::Abort:		returnType = ROER;	break;
		default:					returnType = RORS;	break;
	}
	response->roseType->set((roseType & 0xFF) + 0x100 * returnType);

	return response;
}

IAcse^ AMApp::processEventReport(IAcse^ iacse)
{
	IAcse^ response;
	EventReport^ eventReport = (EventReport^)iacse->rose;
	UInt16 eventType = (UInt16)eventReport->eventType->get();

	switch (eventType) {
		case MDC_NOTI_CONFIG:
			response = processConfig(iacse);
			break;
		case MDC_NOTI_SCAN_REPORT_FIXED:
		case MDC_NOTI_SCAN_REPORT_VAR:
			response = processScanReport(iacse);
			break;
	}

	return response;
}

IAcse^ AMApp::processConfig(IAcse^ iacse)
{
	IAcse^ response;
	EventReport^ responseReport;
	ReturnCode returnCode = ReturnCode::Ok;
	EventReport^ eventReport;
	Report^ report;
	UInt16 invokeId;
	UInt16 roseType;
	UInt16 eventType;
	UInt16 returnType;
	UInt16 reportResult;

	DevObject^ devobject;
	DevAttribute^ devattribute;
	DevAttribute^ mapattribute;
	DevAttribute^ listattribute;

	eventReport = (EventReport^)iacse->rose;

	invokeId = (UInt16)iacse->invokeId->get();
	roseType = (UInt16)iacse->roseType->get();
	eventType = (UInt16)eventReport->eventType->get();

	for each (ObjectList^ objectList in eventReport->eventItems) {

		for each (AttributeList^ attributeList in objectList->attributeLists) {
			devobject = gcnew DevObject();
			devobject->objectClass = (UInt16)attributeList->objectClass->get();
			devobject->objectHandle = (UInt16)attributeList->objectHandle->get();

			for each (AttributeField^ attribute in attributeList->attributes) {
				devattribute = gcnew DevAttribute();
				devattribute->id = (UInt32)attribute->id->get();
				devattribute->len = (UInt32)attribute->valLen->get();

				if (devattribute->id == MDC_ATTR_ATTRIBUTE_VAL_MAP) {
					// map attribute
					ValMap^ valMap = (ValMap^)attribute->value;

					for each (MapField^ mapField in valMap->maps) {
						mapattribute = gcnew DevAttribute();
						mapattribute->id = (UInt32)mapField->id->get();
						mapattribute->len = (UInt32)mapField->valLen->get();
						devattribute->map.Add(mapattribute);
					}
				} else if (devattribute->id == MDC_ATTR_ID_PHYSIO_LIST) {
					// list attribute
					ValList^ valList = (ValList^)attribute->value;

					for each (ListField^ listField in valList->vals) {
						listattribute = gcnew DevAttribute();
						listattribute->id = (UInt32)listField->content->get();
						devattribute->list.Add(listattribute);
					}
				} else {
					// simple attribute
					devattribute->val = attribute->value->get16array();
				}
				devobject->attributes.Add(devattribute);
			}
			devSpec->addObject(devobject);
		}
	}

	// config is ok:
	handleEvent(AMEvent::Req_ConfigSup);
	reportResult = ACCEPTED_CONFIG;

	// else:
	//handleEvent(AMEvent::Req_ConfigUnsup);
	//reportResult = UNSUPPORTED_CONFIG;

	report = gcnew Report();
	report->reportId->set(EXTENDED_CONFIG_START);
	report->reportResult->set(reportResult);

	responseReport = gcnew EventReport(1,false);
	responseReport->objHandle->set(0);
	responseReport->eventTime->set(0);
	responseReport->eventType->set(eventType);
	responseReport->eventItems[0] = report;

	response = gcnew IAcse();
	response->rose = responseReport;
	response->invokeId->set(invokeId);
	switch (returnCode) {
		case ReturnCode::Reject:	returnType = RORJ;	break;
		case ReturnCode::Abort:		returnType = ROER;	break;
		default:					returnType = RORS;	break;
	}
	response->roseType->set((roseType & 0xFF) + 0x100 * returnType);

	return response;
}

IAcse^ AMApp::processScanReport(IAcse^ iacse)
{
	IAcse^ response;
	EventReport^ responseReport;
	EventReport^ eventReport;
	ReturnCode returnCode = ReturnCode::Ok;
	UInt16 invokeId;
	UInt16 reportNo;
	UInt16 roseType;
	UInt16 eventType;
	UInt16 returnType;
	bool fixedObs;
	bool obsSet = false;
	
	DevObservation^ observation;

	DevHL7^ hl7;

	// decode into observation

	eventReport = (EventReport^)iacse->rose;

	invokeId = (UInt16)iacse->invokeId->get();
	roseType = (UInt16)iacse->roseType->get();
	eventType = (UInt16)eventReport->eventType->get();

	fixedObs = (eventType == MDC_NOTI_SCAN_REPORT_FIXED);

	for each (ScanList^ scanList in eventReport->eventItems) {
		reportNo = (UInt16)scanList->reportNo->get();
		
		for each (Field^ scanItem in scanList->items) {

			if (fixedObs) {
				observation = processFixedObservation((ObservationField^)scanItem);
			} else {
				observation = processVarObservation((ScanItemList^)scanItem);
			}
			if (observation) {
				observation->invokeId = invokeId;
				observation->reportNo = reportNo;

				observations.Add(observation);
				model->newObs(eui,observation);
				obsSet = true;
			}
		}
	}

	if (obsSet) {
		hl7 = gcnew DevHL7();
		hl7->construct(%observations,devSpec,manEui,newHL7MsgId++,true);
		// hl7->send();
		model->newHL7(eui,hl7);
		model->updateObs();
	}

	responseReport = gcnew EventReport(0,false);
	responseReport->objHandle->set(0);
	responseReport->eventTime->set(0);
	responseReport->eventType->set(eventType);

	response = gcnew IAcse();
	response->rose = responseReport;
	response->invokeId->set(invokeId);
	switch (returnCode) {
		case ReturnCode::Reject:	returnType = RORJ;	break;
		case ReturnCode::Abort:		returnType = ROER;	break;
		default:					returnType = RORS;	break;
	}
	response->roseType->set((roseType & 0xFF) + 0x100 * returnType);

	return response;
}

DevObservation^ AMApp::processFixedObservation(ObservationField^ observationField)
{
	DevObservation^ observation;
	DevObject^ object;
	ArrayList^ map;
	int maplen;
	ArrayList^ list;
	array<UInt16>^ val;
	UInt32 val32;
	UInt16 val16;
	int objectHandle;
	int valLen;
	int vali;

	objectHandle = (int)observationField->objectHandle->get();
	observation = gcnew DevObservation(objectHandle);
	val = observationField->value->get16array();
	vali = 0;

	object = devSpec->findObject(objectHandle);
	if (object) {
		// find map
		map = object->findMap();
		// check value length
		maplen = 0;
		for each (DevAttribute^ mapAttr in map) {
			maplen += mapAttr->len;
		}
		if (val->Length == maplen / 2) {

			for each (DevAttribute^ mapAttr in map) {
				// decode observation according to map
				valLen = mapAttr->len;
				// find value type in map
				if (	mapAttr->id == MDC_ATTR_ENUM_OBS_VAL_SIMP_BIT_STR ||
						mapAttr->id == MDC_ATTR_ENUM_OBS_VAL_BASIC_BIT_STR) {
					observation->type = ObservationType::Enum;
				} else if (mapAttr->id != MDC_ATTR_TIME_STAMP_ABS) {
					// skip timestamp field for value type detection
					observation->type = ObservationType::Numeric;
				}
				if (mapAttr->id == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC || mapAttr->id == MDC_ATTR_NU_CMPD_VAL_OBS_SIMP) {
					// compound
					if (mapAttr->id == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC) {
						valLen = 2;
					} else {
						valLen = 4;
					}
					// compound; find list
					list = object->findList();
					if (list) {
						observation->compound = true;
						// skip count & length
						vali += 2;

						for each(DevAttribute^ listAttribute in list) {
							// possible to store listAttribute->id in compound observation here
							if (mapAttr->id == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC) {
								val16 = val[vali];
								observation->addCompound(val16);
							} else {
								val32 = (val[vali] * 0x10000) | val[vali+1];
								observation->addCompound(val32);
							}
							vali += valLen/2;
						}
					}
				} else if (mapAttr->id == MDC_ATTR_TIME_STAMP_ABS) {
					// timestamp
					observation->timeStamp = hexStringToDateTime(val,vali);
					vali += valLen/2;
				} else {
					// normal observation
					if (valLen == 2) {
						val16 = val[vali];
						observation->set(val16);
					} else {
						val32 = (val[vali] * 0x10000) | val[vali+1];
						observation->set(val32);
					}
					vali += valLen/2;
				}
			}
		}
	}
	return observation;
}

DevObservation^ AMApp::processVarObservation(ScanItemList^ itemList)
{
	DevObservation^ observation;
	DevObject^ object;
	DevAttribute^ attr;
	UInt16 attrId;
	ArrayList^ list;
	array<UInt16>^ val;
	UInt32 val32;
	UInt16 val16;
	int objectHandle;
	int valLen;
	int vali;
	bool attrFound;
	bool obsSet = false;

	objectHandle = (int)itemList->objectHandle->get();
	observation = gcnew DevObservation(objectHandle);
	object = devSpec->findObject(objectHandle);

	for each (AttributeField^ attrField in itemList->items) {
		attrId = (UInt16)attrField->id->get();
		val = attrField->value->get16array();
		valLen = (int)attrField->valLen->get();
		vali = 0;

		if (	attrId == MDC_ATTR_ENUM_OBS_VAL_SIMP_BIT_STR ||
				attrId == MDC_ATTR_ENUM_OBS_VAL_BASIC_BIT_STR) {
			observation->type = ObservationType::Enum;
		} else if (attrId != MDC_ATTR_TIME_STAMP_ABS) {
			// skip timestamp field for value type detection
			observation->type = ObservationType::Numeric;
		}
		if (attrId == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC || attrId == MDC_ATTR_NU_CMPD_VAL_OBS_SIMP) {
			// compound
			if (attrId == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC) {
				valLen = 2;
			} else {
				valLen = 4;
			}
			if (object) {
				// compound; find list
				list = object->findList();
				if (list) {
					observation->compound = true;
					// skip count & length
					vali = 2;

					for each(DevAttribute^ listAttribute in list) {
						// possible to store listAttribute->id in compound observation here
						if (attrId == MDC_ATTR_NU_CMPD_VAL_OBS_BASIC) {
							val16 = val[vali];
							observation->addCompound(val16);
						} else {
							val32 = (val[vali] * 0x10000) | val[vali+1];
							observation->addCompound(val32);
						}
						obsSet = true;
						vali += valLen/2;
					}
				}
			}
		} else if (attrId == MDC_ATTR_TIME_STAMP_ABS) {
			// timestamp
			observation->timeStamp = hexStringToDateTime(val,0);
		} else {
			attrFound = false;
			if (object) {
				// check if attribute
				attr = object->findAttribute(attrId);
				if (attr) {
					// update attribute value
					attr->val = val;
					attrFound = true;
				}
			}
			if (!attrFound) {
				// normal observation
				if (valLen == 2) {
					val16 = val[vali];
					observation->set(val16);
				} else {
					val32 = (val[vali] * 0x10000) | val[vali+1];
					observation->set(val32);
				}
				obsSet = true;
			}
		}
	}
	if (obsSet) {
		return observation;
	}
	return nullptr;
}

ReturnCode AMApp::handleEvent(AMEvent event)
{
	AMState state0;

	ReturnCode returnCode = ReturnCode::Nothing;

	AMAction action = (AMAction)actions[(int)state][(int)event];

	state0 = (AMState)newStates[(int)state][(int)event];
	if (state0 != AMState::NoChange) {
		state = state0;
		// check for pending invokes
		sendNextInvoke();
		model->updateSpec(eui,spec,getState(),ComCommand::None);
	}

	switch (action) {
		case OK:
			returnCode = ReturnCode::Ok;
			break;
//		case REJ:
//			returnCode = ReturnCode::Reject;
//			break;
		case AB:
			returnCode = ReturnCode::Abort;
			break;
		case SAB:
			sendAbort(ABORT_REASON_UNDEFINED);
			break;
		case SAR:
			sendAbort(ABORT_REASON_RESPONSE_TIMEOUT);
			break;
		case SAC:
			sendAbort(ABORT_REASON_CONFIGURATION_TIMEOUT);
			break;
		case AS:
			sendAssocReq();
			break;
		case DIS:
			sendReleaseReq(RELEASE_REQUEST_REASON_NORMAL);
			break;
		case CFG:
			sendConfig();
			break;
	}
	return returnCode;
}
