#include "StdAfx.h"
#include "ConfigInvokeHandler.h"
#include "DevObject.h"
#include "Prst.h"
#include "EventReport.h"
#include "ObjectList.h"
#include "AttributeList.h"
#include "ValMap.h"
#include "ValList.h"
#include "nomenclature.h"
#include "phd_constants.h"


ConfigInvokeHandler::ConfigInvokeHandler(AMState minimumState0)
	: InvokeHandler(minimumState0,true)
{
}

Apdu^ ConfigInvokeHandler::construct(DevSpec^ devSpec,int invokeId,List<DevObservation^>^ observations)
{
	this->invokeId = invokeId;

	Apdu^ apdu = gcnew Apdu();
	Prst^ prst = gcnew Prst();
	IAcse^ iacse = prst->iacse;
	EventReport^ eventReport = gcnew EventReport(1,true);
	ObjectList^ objectList;
	array<AttributeList^>^ attributeLists;
	AttributeList^ attributeList;
	AttributeField^ attr;
	ValMap^ valMap;
	ValList^ valList;

	int nobjects = 0;
	int objecti = 0;
	int nattr;
	int attri;
	int nmap;
	int nlist;
	int mapi;
	int listi;

	for each (DevObject^ object in devSpec->objects) {
		if (object->objectHandle != 0) {
			nobjects++;
		}
	}

	objectList = gcnew ObjectList();
	attributeLists = gcnew array<AttributeList^>(nobjects);

	for each (DevObject^ object in devSpec->objects) {
		if (object->objectHandle != 0) {
			nattr = object->attributes.Count;
			attributeList = gcnew AttributeList(nattr);
			attributeList->objectClass->set(object->objectClass);
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
			attributeLists[objecti] = attributeList;
			objecti++;
		}
	}
	objectList->reportId->set(EXTENDED_CONFIG_START);
	objectList->attributeLists = attributeLists;

	eventReport->objHandle->set(0);
	eventReport->eventType->set(MDC_NOTI_CONFIG);
	eventReport->eventTime->set(0xFFFFFFFF);
	eventReport->eventItems[0] = objectList;

	iacse->invokeId->set(invokeId);
	iacse->roseType->set(ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN);
	iacse->rose = eventReport;

	apdu->acseType->set(PRST_CHOSEN);
	apdu->acse = prst;

	sentApdu = apdu;
	return apdu;
}

ReturnInfo^ ConfigInvokeHandler::processResponse(IAcse^ iacse,UInt16 roseType,UInt16 type,List<DevObservation^>^ observations)
{
	ReturnInfo^ info = gcnew ReturnInfo();

	switch (type) {
		case RORS:
			// ok
			info->event = AMEvent::Rx_Rors_EventReport_Accept;
			info->code = ReturnCode::Ok;
			break;
		case RORJ:
			// reject
			info->code = ReturnCode::Ok;
			break;
		case ROER:
			// error
			info->code = ReturnCode::Ok;
			break;
	}
	return info;
}
