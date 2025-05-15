#include "StdAfx.h"
#include "AMView.h"
#include "DevObject.h"
#include "ValMap.h"
#include "ValList.h"
#include "MapField.h"
#include "ListField.h"
#include "conversion.h"
#include "nomenclature.h"
#include "util.h"


AMView::AMView(AMControllerInterface^ controller0,AMModelInterface^ model0)
{
	controller = controller0;
	model = model0;
	model->registerObserver(this);
	selectedEui = 0;
	selectedSpec = gcnew DevSpec();
	selectedObject = gcnew DevObject();
}

void AMView::createView()
{
	mainForm = gcnew MainForm(controller);
	portForm = gcnew PortForm();
	tcpForm = gcnew TCPForm();
	ipForm = gcnew IPForm();
}

Form^ AMView::getMainForm()
{
	return mainForm;
}

void AMView::setComInitialised(bool set)
{
	mainForm->setComInitialised(set);
}

SerialPort^ AMView::openPortDialog()
{
	SerialPort^ port;
	if (portForm->ShowDialog() == DialogResult::OK) {
		port = portForm->port;
	}
	return port;
}


TCPInfo^ AMView::openTCPDialog()
{
	TCPInfo^ portInfo;
	if (tcpForm->ShowDialog() == DialogResult::OK) {
		portInfo = tcpForm->portInfo;
	}
	return portInfo;
}

IPInfo^ AMView::openIPDialog()
{
	IPInfo^ portInfo;
	if (ipForm->ShowDialog() == DialogResult::OK) {
		portInfo = ipForm->portInfo;
	}
	return portInfo;
}

void AMView::selectSpec(UInt64 eui,DevSpec^ devSpec)
{
	selectedEui = eui;
	selectedSpec = devSpec;

	updateComs();
	updateObjs();
	updateObs();
	updateHL7s();
}

void AMView::updateSpec(UInt64 eui,String^ spec,String^ state,ComCommand command)
{
	mainForm->updateSpec(eui,spec,state,command);
}

void AMView::newCom(UInt64 eui,DateTime dt,array<Byte>^ data,String^ shortdesc,String^ fulldesc,bool rec,bool ok)
{
	comMsgs.Add(gcnew ComMsg(eui,dt,data,shortdesc,fulldesc,rec,ok));
	if (eui == selectedEui) {
		mainForm->addCom(toString(dt),shortdesc,data->Length,rec,ok);
	}
}

void AMView::updateComs()
{
	mainForm->clearComList();
	for each (ComMsg^ commsg in comMsgs) {
		if (commsg->eui == selectedEui) {
			mainForm->addCom(toString(commsg->dt),commsg->shortdesc,commsg->data->Length,commsg->rec,commsg->ok);
		}
	}
}

void AMView::updateObjs()
{
	String^ objInfo;

	mainForm->clearObjList();
	if (selectedSpec != nullptr) {
		for each (DevObject^ object in selectedSpec->objects) {
			if (object->objectHandle == 0) {
				objInfo = "MDS";
			} else {
				objInfo = objClass(object->objectClass);
			}
			mainForm->addObj(object->objectHandle.ToString(),objInfo);
		}
	} else {
		selectObject(-1);
	}
}

void AMView::newObs(UInt64 eui,DevObservation^ obs)
{
	if (!observations.Contains(obs)) {
		observations.Add(obs);
		obsOwner.Add(eui);
		if (eui == selectedEui) {
			addObs(obs);
		}
	}
}

void AMView::updateObs()
{
	mainForm->clearObsList();

	if (selectedSpec) {
		for (int i=0;i<observations.Count;i++) {
			if (obsOwner[i] == selectedEui) {
				addObs(observations[i]);
			}
		}
	} else {
		selectObs(-1);
	}
}

void AMView::addObs(DevObservation^ obs)
{
	mainForm->addObs(
		toString(obs->timeStamp),
		obs->reportNo.ToString(),
		obs->objectHandle.ToString(),
		obs->state.ToString(),
		obs->state != SendState::Sent);
}

void AMView::newHL7(UInt64 eui,DevHL7^ hl7)
{
	if (!hl7s.Contains(hl7)) {
		hl7s.Add(hl7);
		hl7Owner.Add(eui);
		if (eui == selectedEui) {
			addHL7(hl7);
		}
	}
}

void AMView::updateHL7s()
{
	mainForm->clearHL7List();

	if (selectedSpec) {
		for (int i=0;i<hl7s.Count;i++) {
			if (hl7Owner[i] == selectedEui) {
				addHL7(hl7s[i]);
			}
		}
	} else {
		selectHL7(-1);
	}
}

void AMView::addHL7(DevHL7^ hl7)
{
	mainForm->addHL7(hl7->timeStamp.ToString(),hl7->msgId.ToString(),hl7->state.ToString(),hl7->state != SendState::Sent);
}

void AMView::updateTitle(String^ title)
{
	String^ fulltitle = "";
#ifdef AGENT
	fulltitle += "Agent";
#endif
#ifdef MANAGER
	fulltitle += "Manager";
#endif
	if (title != "") {
		fulltitle += " - " + title;
	}
	mainForm->setTitle(fulltitle);
}

void AMView::selectComMsg(int selectedIndex)
{
	int i = 0;
	int dispi = 0;

	if (selectedIndex >= 0) {
		for each (ComMsg^ commsg in comMsgs) {
			if (commsg->eui == selectedEui) {
				if (dispi == selectedIndex) {
					mainForm->dispComMsg(toString(comMsgs[i]->data),comMsgs[i]->tree);
					return;
				}
				dispi++;
			}
			i++;
		}
	}
	mainForm->clearComMsg();
}

void AMView::selectObject(int selectedIndex)
{
	DevObject^ object;

	mainForm->clearAttrList();

	if (selectedIndex >= 0) {
		if (selectedIndex < selectedSpec->objects.Count) {
			object = (DevObject^)selectedSpec->objects[selectedIndex];
			selectedObject = object;
			for each (DevAttribute^ attribute in object->attributes) {
				mainForm->addAttr(attrId(attribute->id));
			}
			return;
		}
	}
	selectedObject = nullptr;
	selectAttribute(-1);
}

void AMView::selectAttribute(int selectedIndex)
{
	DevAttribute^ attribute;
	String^ vals = "";
	UInt64 val;
	UInt16 val16;
	array<UInt16>^ valarray;

	if (selectedIndex >= 0 && selectedObject != nullptr) {
		if (selectedIndex < selectedObject->attributes.Count) {
			attribute = (DevAttribute^)selectedObject->attributes[selectedIndex];
			for each (DevAttribute^ map in attribute->map) {
				vals += attrId(map->id) + String::Format(" len:{0}",map->len) + "\n";
			}
			for each (DevAttribute^ list in attribute->list) {
				vals += attrId(list->id) + "\n";
			}
			if (attribute->id == MDC_ATTR_DEV_CONFIG_ID) {
				// configId
				vals += configId((UInt16)attribute->getVal());
			} else if (attribute->id == MDC_ATTR_SYS_TYPE_SPEC_LIST) {
				// specList
				valarray = attribute->val;
				vals += String::Format("{2} V{3}",valarray[0],valarray[1],devTypeId(valarray[2]),valarray[3]);
			} else if (attribute->id == MDC_ATTR_ID_MODEL) {
				// idModel
				vals += manModelBytesToString(attribute->val);
			} else if (attribute->id == MDC_ATTR_SYS_ID) {
				// sysId
				vals += String::Format("{0:X16}",attribute->getVal());
			} else if (attribute->id == MDC_ATTR_ID_TYPE) {
				// idType
				val = attribute->getVal();
				val16 = (UInt16)(val / 0x10000);
				if (val16 != 0) {
					vals += partId(val16);
					vals += "|";
				}
				val16 = val & 0xFFFF;
				vals += typeId(val16);
			} else if (attribute->id == MDC_ATTR_UNIT_CODE) {
				// unitCode
				vals += unitId((UInt16)attribute->getVal());
			} else if (attribute->id == MDC_ATTR_METRIC_SPEC_SMALL) {
				// metric spec small
				vals += metricSpecSmallToString((UInt16)attribute->getVal());
			} else if (attribute->id == MDC_ATTR_MDS_TIME_INFO) {
				// MDS time info
				vals += metricMdsTimeInfoToString((UInt16)attribute->getVal());
			} else {
				vals += toString(attribute->val);
			}
		}
	}
	mainForm->dispAttrText(vals);
}

void AMView::selectObs(int selectedIndex)
{
	int dispi = 0;

	if (selectedIndex >= 0) {
		for (int i=0;i<observations.Count;i++) {
			if (obsOwner[i] == selectedEui) {
				if (dispi == selectedIndex) {
					mainForm->dispObsText(observations[i]->ToString());
					return;
				}
				dispi++;
			}
		}
	}
	mainForm->dispObsText("");
}

void AMView::selectHL7(int selectedIndex)
{
	int dispi = 0;

	if (selectedIndex >= 0) {
		for (int i=0;i<hl7s.Count;i++) {
			if (hl7Owner[i] == selectedEui) {
				if (dispi == selectedIndex) {
					mainForm->dispHL7Text(hl7s[i]->hl7);
					return;
				}
				dispi++;
			}
		}
	}
	mainForm->dispHL7Text("");
}
