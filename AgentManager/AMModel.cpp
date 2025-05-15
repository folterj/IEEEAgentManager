#include "StdAfx.h"
#include "AMModel.h"
#include "AMApp.h"
#include "Manager.h"
#include "Agent.h"
#include "MQCom.h"
#include "util.h"


AMModel::AMModel()
{
	manEui = 0;
	id = Guid::NewGuid().ToString();
	basePath = "";
	selftitle = "";
	closing = false;
}

AMModel::~AMModel()
{
	if (connectCom) {
		delete connectCom;
	}
	for each (ComInterface^ com in coms.ToArray()) {
		com->removed();
		com->close();
	}
	coms.Clear();
}

void AMModel::init()
{
	updateTitle("");
}

void AMModel::connected()
{
	// connectCom connected
}

void AMModel::disconnected()
{
	// connectCom disconnected
}

void AMModel::removed()
{
	// connectCom removed
}

void AMModel::disconnectAll()
{
	for each (ComInterface^ com in coms.ToArray()) {
		com->send(ComCommand::Disconnect);
		com->disconnected();
	}
}

void AMModel::reconnectAll()
{
	for each (ComInterface^ com in coms.ToArray()) {
		com->send(ComCommand::Connect);
		com->connected();
	}
}

void AMModel::selectSpec(UInt64 eui)
{
	String^ title;
	DevSpec^ devspec = nullptr;

	if (eui != 0) {
		for each (AMApp^ app in apps.ToArray()) {
			if (app->getEui() == eui) {
				selectedApp = app;
				devspec = selectedApp->getDevSpec();
				break;
			}
		}
	} else {
		// eui is not set
		selectedApp = nullptr;
	}
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->selectSpec(eui,devspec);
	}
	if (selectedApp) {
		title = String::Format("{0:X16}:{1}",eui,selectedApp->getSpec());
		updateTitle(title);
	} else {
		// eui is not set
		updateTitle("");
	}
}

void AMModel::updateSpec(UInt64 eui,String^ spec,String^ state,ComCommand command)
{
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->updateSpec(eui,spec,state,command);
	}
	// if command = remove: delete app / com as well
	if (command == ComCommand::Remove) {
		for each (AMApp^ app in apps.ToArray()) {
			// find matching app
			if (app->getEui() == eui) {
				for each (ComInterface^ com in coms.ToArray()) {
					// find matching com
					if ((ComInterface^)com == app->getCom()) {
						coms.Remove(com);
						break;
					}
				}
				apps.Remove(app);
				break;
			}
		}
	}
}

void AMModel::newCom(UInt64 eui,DateTime dt,array<Byte>^ data,String^ shortdesc,String^ fulldesc,bool rec,bool ok)
{
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->newCom(eui,dt,data,shortdesc,fulldesc,rec,ok);
	}
}

void AMModel::newObs(UInt64 eui,DevObservation^ observation)
{
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->newObs(eui,observation);
	}
}

void AMModel::updateObs()
{
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->updateObs();
	}
}

void AMModel::newHL7(UInt64 eui,DevHL7^ hl7)
{
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->newHL7(eui,hl7);
	}
}

void AMModel::updateHL7s()
{
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->updateHL7s();
	}
}

void AMModel::updateTitle(String^ title)
{
	String^ fulltitle = "";
	if (selftitle != "") {
		fulltitle+= "(" + selftitle + ")";
	}
	if (fulltitle != "" && title != "") {
		fulltitle+= " - ";
	}
	fulltitle+= title;
	for (int i=0;i<amObservers.Count;i++) {
		((AMObserver^)amObservers[i])->updateTitle(fulltitle);
	}
}

void AMModel::createScanReport(ReportType reportType)
{
	if (selectedApp) {
		selectedApp->createScanReport(reportType,true);
	}
}

bool AMModel::amPathExists(String^ basePath,UInt64 eui)
{
	String^ path0 = createPath(basePath,eui);
	return (connectCom->pathExists(path0));
}

void AMModel::clearQueried()
{
	manPaths.Clear();
	manEuis.Clear();
}

void AMModel::storeQueried(String^ manPath,UInt64 manEui0)
{
	manPaths.Add(manPath);
	manEuis.Add(manEui0);
}
