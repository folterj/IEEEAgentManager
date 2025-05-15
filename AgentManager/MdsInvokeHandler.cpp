#include "StdAfx.h"
#include "MdsInvokeHandler.h"
#include "DevObject.h"
#include "Prst.h"
#include "MdsAttributeList.h"
#include "nomenclature.h"
#include "phd_constants.h"


MdsInvokeHandler::MdsInvokeHandler(AMState minimumState0)
	: InvokeHandler(minimumState0,true)
{
}

Apdu^ MdsInvokeHandler::construct(DevSpec^ devSpec,int invokeId,List<DevObservation^>^ observations)
{
	this->invokeId = invokeId;

	Apdu^ apdu = gcnew Apdu();
	Prst^ prst = gcnew Prst();
	IAcse^ iacse = prst->iacse;
	MdsAttributeList^ attributeList = gcnew MdsAttributeList(0);

	attributeList->attributeCount->set(0);
	attributeList->attributeLen->set(0);

	iacse->invokeId->set(invokeId);
	iacse->roseType->set(ROIV_CMIP_GET_CHOSEN);
	iacse->rose = attributeList;

	apdu->acseType->set(PRST_CHOSEN);
	apdu->acse = prst;

	sentApdu = apdu;
	return apdu;
}

ReturnInfo^ MdsInvokeHandler::processResponse(IAcse^ iacse,UInt16 roseType,UInt16 type,List<DevObservation^>^ observations)
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
