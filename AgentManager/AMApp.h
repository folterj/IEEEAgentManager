#pragma once

#include "ComObserver.h"
#include "AMModelInterface.h"
#include "ComInterface.h"
#include "ApduSender.h"
#include "DevSpec.h"
#include "InvokeHandler.h"
#include "Field.h"
#include "Apdu.h"
#include "IAcse.h"
#include "Aarq.h"
#include "Aare.h"
#include "Rlrq.h"
#include "Rlre.h"
#include "Abrt.h"
#include "Prst.h"
#include "EventReport.h"
#include "ObservationField.h"
#include "ScanItemList.h"

ref class AMApp abstract : public ComObserver
{
protected:
	AMModelInterface^ model;
	ComInterface^ com;
	ApduSender^ sender;
	UInt64 eui;
	UInt64 manEui;
	DevSpec^ devSpec;
	AMState state;
	String^ spec;
	SpecType specType;
	bool isconnected;

	bool invokeSending;
	int newInvokeId;
	int newHL7MsgId;
	int newReportNo;
	List<InvokeHandler^> invokes;
	List<DevObservation^> observations;
	Timers::Timer invokeTimer;	// to prevent lock up

	array<array<int>^>^ actions;
	array<array<int>^>^ newStates;

public:
	AMApp(AMModelInterface^ model0,ComInterface^ com0,UInt64 eui0,String^ spec0);

	virtual void removed() override;
	UInt64 getEui();
	DevSpec^ getDevSpec();
	String^ getSpec();
	String^ getState();
	ComInterface^ getCom();
	bool send(Apdu^ apdu);
	virtual Object^ dataReceived(Object^ data0,bool expectResponse) override;
	virtual void confReceived() override;

	void createScanReport(ReportType reportType,bool confirmed);
	void createScanObservation(ReportType reportType,bool confirmed);
	void createScanAttribute(ReportType reportType,bool confirmed);
	void sendMdsGet();
	void sendConfig();
	void sendAction(bool confirmed);
	void sendScanObservationFixed(bool confirmed);
	void sendScanObservationVar(bool confirmed);
	void sendScanAttribute(bool confirmed);

	bool addInvoke(InvokeHandler^ invoke);
	bool sendNextInvoke();
	void invokeTimer_Elapsed(Object^ sender, ElapsedEventArgs^ e);
	void clearInvokes();
	void clearQueues();

	void processApdu(Apdu^ apdu,bool valid);
	IAcse^ processRose(IAcse^ iacse);

	void sendAssocReq();
	Field^ processAssocReq(Aarq^ aarq);
	Field^ createAssocResp(UInt64 assocResult);
	void processAssocResp(Aare^ aare);
	void sendReleaseReq(UInt16 reason);
	Field^ processReleaseReq(Rlrq^ rlrq);
	void processReleaseResp(Rlre^ rlre);
	Field^ createReleaseReq(UInt16 reason);
	Field^ createReleaseResp(UInt16 reason);
	void sendAbort(UInt16 reason);
	Field^ createAbort(UInt16 reason);
	void processAbort(Abrt^ abrt);

	IAcse^ processMdsGet(IAcse^ iacse);
	void processMds(IAcse^ iacse);
	bool getManSetTime();
	IAcse^ processAction(IAcse^ iacse);
	IAcse^ processEventReport(IAcse^ iacse);
	IAcse^ processConfig(IAcse^ iacse);

	IAcse^ processScanReport(IAcse^ iacse);
	DevObservation^ processFixedObservation(ObservationField^ observationField);
	DevObservation^ processVarObservation(ScanItemList^ itemList);

	ReturnCode handleEvent(AMEvent event);
};
