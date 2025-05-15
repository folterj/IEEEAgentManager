#include "StdAfx.h"
#include "ActionInvokeHandler.h"
#include "Apdu.h"
#include "Prst.h"
#include "ActionMethod.h"
#include "nomenclature.h"
#include "phd_constants.h"
#include "util.h"


ActionInvokeHandler::ActionInvokeHandler(AMState minimumState0,bool confirmed0)
	: InvokeHandler(minimumState0,confirmed0)
{
}

Apdu^ ActionInvokeHandler::construct(DevSpec^ devSpec,int invokeId,List<DevObservation^>^ observations)
{
	this->invokeId = invokeId;

	Apdu^ apdu = gcnew Apdu();
	Prst^ prst = gcnew Prst();
	IAcse^ iacse = prst->iacse;
	ActionMethod^ action = gcnew ActionMethod();
	array<UInt16>^ val = gcnew array<UInt16>(0);
	UInt16 accuracy;

	val = serialise(val,dateTimeToHexString(DateTime::Now));
	accuracy = 0;
	val = serialise(val,accuracy);

	action->objHandle->set(0);
	action->type->set(MDC_ACT_SET_TIME);
	action->value = gcnew Field(val->Length * 2);
	action->value->set(val);

	iacse->invokeId->set(invokeId);
	if (confirmed) {
		iacse->roseType->set(ROIV_CMIP_CONFIRMED_ACTION_CHOSEN);
	} else {
		iacse->roseType->set(ROIV_CMIP_ACTION_CHOSEN);
	}
	iacse->rose = action;

	apdu->acseType->set(PRST_CHOSEN);
	apdu->acse = prst;

	sentApdu = apdu;
	return apdu;
}

ReturnInfo^ ActionInvokeHandler::processResponse(IAcse^ iacse,UInt16 roseType,UInt16 type,List<DevObservation^>^ observations)
{
	ReturnInfo^ info = gcnew ReturnInfo();

	switch (type) {
		case RORS:
			// ok
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
