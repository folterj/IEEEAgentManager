#pragma once

#include "InvokeHandler.h"
#include "DevSpec.h"

ref class ObservationInvokeHandler : public InvokeHandler
{
public:
	ReportType reportType;
	int reportNo;

	ObservationInvokeHandler(AMState minimumState0,ReportType reportType0,int reportNo0,bool confirmed0);

	virtual Apdu^ construct(DevSpec^ devSpec,int invokeId,List<DevObservation^>^ observations) override;
	Apdu^ constructScanReportObservation(DevSpec^ devSpec,List<DevObservation^>^ observations);
	Apdu^ constructScanReportAttribute(DevSpec^ devSpec);
	Field^ createScanFixedObs(DevSpec^ devSpec,DevObservation^ observation);
	Field^ createScanVarObs(DevSpec^ devSpec,DevObservation^ observation,bool addUnit);
	Field^ createScanVarAttr(DevSpec^ devSpec,DevObject^ object);
	array<UInt16>^ serialiseScanObsValue(array<UInt16>^ val,DevObservation^ observation,DevObject^ object,DevAttribute^ mapAttr);

	virtual ReturnInfo^ processResponse(IAcse^ iacse,UInt16 roseType,UInt16 type,List<DevObservation^>^ observations) override;
};
