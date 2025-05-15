#pragma once

#include "AMControllerInterface.h"
#include "AMModelInterface.h"
#include "AMView.h"

ref class AMController : public AMControllerInterface
{
private:
	AMModelInterface^ model;
	AMView^ view;
	bool created;
	bool connected;

public:
	AMController(AMModelInterface^ model0);
	AMView^ getView();

	virtual bool comInit(ComType comType) override;
	virtual bool connect(array<ConnectInfo^>^ devices) override;
	virtual void selectSpec(UInt64 eui) override;
	virtual void selectComMsg(int index) override;
	virtual void selectObject(int index) override;
	virtual void selectAttribute(int index) override;
	virtual void selectObs(int index) override;
	virtual void selectHL7(int index) override;
	virtual void obsFixedButton() override;
	virtual void obsVarButton() override;
	virtual void attrButton() override;
};
