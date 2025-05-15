#pragma once

#include "AMModelInterface.h"
#include "ComInterface.h"
#include "DevSpec.h"
#include "AMApp.h"

ref class AMModel abstract : public AMModelInterface
{
protected:
	List<AMApp^> apps;
	List<ComInterface^> coms;

	List<String^> manPaths;
	List<UInt64> manEuis;

	String^ id;
	ComInterface^ connectCom;
	ComType comType;
	String^ basePath;
	AMApp^ selectedApp;
	String^ selftitle;
	UInt64 manEui;

	bool closing;

public:
	AMModel();
	~AMModel();
	virtual void init() override;

	virtual void connected() override;
	virtual void disconnected() override;
	virtual void removed() override;

	virtual void disconnectAll() override;
	virtual void reconnectAll() override;
	virtual void selectSpec(UInt64 eui) override;

	virtual void updateSpec(UInt64 eui,String^ spec,String^ state,ComCommand command) override;
	virtual void newCom(UInt64 eui,DateTime dt,array<Byte>^ data,String^ shortdesc,String^ fulldesc,bool rec,bool ok) override;
	virtual void newObs(UInt64 eui,DevObservation^ observation) override;
	virtual void updateObs() override;
	virtual void newHL7(UInt64 eui,DevHL7^ hl7) override;
	virtual void updateHL7s() override;
	virtual void updateTitle(String^ title) override;

	virtual void createScanReport(ReportType reportType) override;

	bool amPathExists(String^ basePath,UInt64 eui);
	
	void clearQueried();
	void storeQueried(String^ manPath,UInt64 manEui0);
};
