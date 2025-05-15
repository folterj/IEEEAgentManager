#pragma once

#include "InvokeHandler.h"
#include "DevSpec.h"

ref class ConfigInvokeHandler : public InvokeHandler
{
public:
	ConfigInvokeHandler(AMState minimumState0);

	virtual Apdu^ construct(DevSpec^ devSpec,int invokeId,List<DevObservation^>^ observations) override;
	virtual ReturnInfo^ processResponse(IAcse^ iacse,UInt16 roseType,UInt16 type,List<DevObservation^>^ observations) override;
};
