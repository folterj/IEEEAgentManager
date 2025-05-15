#pragma once

#include "AMViewInterface.h"
#include "AMControllerInterface.h"
#include "AMModelInterface.h"
#include "MainForm.h"
#include "PortForm.h"
#include "TCPForm.h"
#include "IPForm.h"
#include "DevAttribute.h"
#include "DevObservation.h"
#include "DevHl7.h"
#include "TreeString.h"

using namespace System::Net;
using namespace System::Collections::Generic;
using namespace AgentManager;

ref class ComMsg
{
public:
	UInt64 eui;
	DateTime dt;
	array<Byte>^ data;
	String^ shortdesc;
	String^ fulldesc;
	array<TreeNode^>^ tree;
	bool rec;
	bool ok;

	ComMsg(UInt64 eui0,DateTime dt0,array<Byte>^ data0,String^ shortdesc0,String^ fulldesc0,bool rec0,bool ok0)
	{
		eui = eui0;
		dt = dt0;
		data = data0;
		shortdesc = shortdesc0;
		fulldesc = fulldesc0;
		tree = TreeString::getTree(fulldesc);
		rec = rec0;
		ok = ok0;
	}
};

ref class AMView : public AMViewInterface
{
private:
	AMControllerInterface^ controller;
	AMModelInterface^ model;
	MainForm^ mainForm;
	PortForm^ portForm;
	TCPForm^ tcpForm;
	IPForm^ ipForm;
	List<ComMsg^> comMsgs;
	List<DevObservation^> observations;
	List<UInt64> obsOwner;
	List<DevHL7^> hl7s;
	List<UInt64> hl7Owner;
	UInt64 selectedEui;
	DevSpec^ selectedSpec;
	DevObject^ selectedObject;

public:
	AMView(AMControllerInterface^ controller0,AMModelInterface^ model0);
	void createView();
	Form^ getMainForm();

	void setComInitialised(bool set);
	SerialPort^ openPortDialog();
	TCPInfo^ openTCPDialog();
	IPInfo^ openIPDialog();
	virtual void selectSpec(UInt64 eui,DevSpec^ devSpec) override;
	virtual void updateSpec(UInt64 eui,String^ spec,String^ state,ComCommand command) override;

	virtual void newCom(UInt64 eui,DateTime dt,array<Byte>^ data,String^ shortdesc,String^ fulldesc,bool rec,bool ok) override;
	void updateComs();
	void updateObjs();

	virtual void newObs(UInt64 eui,DevObservation^ observation) override;
	virtual void updateObs() override;
	void addObs(DevObservation^ observation);

	virtual void newHL7(UInt64 eui,DevHL7^ hl7) override;
	virtual void updateHL7s() override;
	void addHL7(DevHL7^ hl7);

	virtual void updateTitle(String^ title) override;

	void selectComMsg(int selectedIndex);
	void selectObject(int selectedIndex);
	void selectAttribute(int selectedIndex);
	void selectObs(int selectedIndex);
	void selectHL7(int selectedIndex);
};
