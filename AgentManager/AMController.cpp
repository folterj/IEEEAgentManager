#include "StdAfx.h"
#include "AMController.h"

AMController::AMController(AMModelInterface^ model0)
{
	model = model0;
#ifdef MANAGER
	created = true;
	connected = true;
#else
	created = false;
	connected = false;
#endif
	view = gcnew AMView(this,model);
	view->createView();
	model->init();
}

AMView^ AMController::getView()
{
	return view;
}

bool AMController::comInit(ComType comType)
{
	Object^ portInfo;
	bool ok;

	if (comType == ComType::SerialPort) {
		portInfo = view->openPortDialog();
		if (!portInfo) {
			return false;
		}
	} else if (comType == ComType::TCP) {
		portInfo = view->openTCPDialog();
		if (!portInfo) {
			return false;
		}
	} else if (comType == ComType::HTTP) {
		portInfo = view->openIPDialog();
		if (!portInfo) {
			return false;
		}
	}
	ok = model->comInit(comType,portInfo);
	view->setComInitialised(ok);
	return ok;
}

bool AMController::connect(array<ConnectInfo^>^ devices)
{
	if (!created) {
		// connect
		model->connect(devices);
		created = true;
		connected = true;
	} else {
		if (!connected) {
			// reconnect
			model->reconnectAll();
			connected = true;
		} else {
			// disconnect
			model->disconnectAll();
			connected = false;
		}
	}
	return connected;
}

void AMController::selectSpec(UInt64 eui)
{
	model->selectSpec(eui);
	// if spec changed, deselect any com msg (from old spec)
	selectComMsg(-1);
}

void AMController::selectComMsg(int index)
{
	view->selectComMsg(index);
}

void AMController::selectObject(int index)
{
	view->selectObject(index);
}

void AMController::selectAttribute(int index)
{
	view->selectAttribute(index);
}

void AMController::selectObs(int index)
{
	view->selectObs(index);
}

void AMController::selectHL7(int index)
{
	view->selectHL7(index);
}

void AMController::obsFixedButton()
{
	model->createScanReport(ReportType::ObservationFixed);
}

void AMController::obsVarButton()
{
	model->createScanReport(ReportType::ObservationVar);
}

void AMController::attrButton()
{
	model->createScanReport(ReportType::Attribute);
}
