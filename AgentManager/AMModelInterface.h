#pragma once

#include "ComObserver.h"
#include "AMObserver.h"
#include "DevSpec.h"
#include "ConnectInfo.h"

using namespace System::Collections;

ref class AMModelInterface abstract : public ComObserver
{
protected:
	ArrayList amObservers;

public:
	virtual void init() = 0;
	virtual bool comInit(ComType comType,Object^ comInfo) = 0;
	virtual bool connect(array<ConnectInfo^>^ devices) = 0;
	virtual void disconnectAll() = 0;
	virtual void reconnectAll() = 0;
	virtual void selectSpec(UInt64 eui) = 0;

	virtual void updateSpec(UInt64 eui,String^ spec,String^ state,ComCommand command) = 0;
	virtual void newCom(UInt64 eui,DateTime dt,array<Byte>^ data,String^ shortdesc,String^ fulldesc,bool rec,bool ok) = 0;
	virtual void newObs(UInt64 eui,DevObservation^ observation) = 0;
	virtual void updateObs() = 0;
	virtual void newHL7(UInt64 eui,DevHL7^ hl7) = 0;
	virtual void updateHL7s() = 0;
	virtual void updateTitle(String^ title) = 0;

	virtual void createScanReport(ReportType reportType) = 0;

	void registerObserver(AMObserver^ observer);
	void unregisterObserver(AMObserver^ observer);
};
