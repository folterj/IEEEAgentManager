#pragma once

#include "Apdu.h"
#include "IAcse.h"
#include "DevSpec.h"
#include "ReturnInfo.h"
#include "SendState.h"
#include "DevObservation.h"

using namespace System::Collections::Generic;

ref class InvokeHandler abstract
{
public:
	int invokeId;
	AMState minimumState;
	bool confirmed;
	SendState state;

	Apdu^ sentApdu;

	InvokeHandler(AMState minimumState0,bool confirmed0);

	virtual Apdu^ construct(DevSpec^ devSpec,int invokeId,List<DevObservation^>^ observations) = 0;
	virtual ReturnInfo^ processResponse(IAcse^ iacse,UInt16 roseType,UInt16 type,List<DevObservation^>^ observations) = 0;
};
