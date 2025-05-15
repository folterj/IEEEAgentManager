#pragma once

#include "ConnectInfo.h"
#include "defines.h"

using namespace System;

public ref class AMControllerInterface abstract
{
public:
	virtual bool comInit(ComType comType) = 0;
	virtual bool connect(array<ConnectInfo^>^ devices) = 0;
	virtual void selectSpec(UInt64 eui) = 0;
	virtual void selectComMsg(int index) = 0;
	virtual void selectObject(int index) = 0;
	virtual void selectAttribute(int index) = 0;
	virtual void selectObs(int index) = 0;
	virtual void selectHL7(int index) = 0;
	virtual void obsFixedButton() = 0;
	virtual void obsVarButton() = 0;
	virtual void attrButton() = 0;
};
