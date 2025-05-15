#pragma once

#include "defines.h"
#include "DevAttribute.h"
#include "DevObservation.h"
#include "DevHL7.h"
#include "DevSpec.h"

using namespace System;
using namespace System::Windows::Forms;

ref class AMObserver abstract
{
public:
	virtual void selectSpec(UInt64 eui,DevSpec^ devSpec) = 0;
	virtual void updateSpec(UInt64 eui,String^ spec,String^ state,ComCommand command) = 0;

	virtual void newCom(UInt64 eui,DateTime dt,array<Byte>^ data,String^ shortdesc,String^ fulldesc,bool rec,bool ok) = 0;

	virtual void newObs(UInt64 eui,DevObservation^ observation) = 0;
	virtual void updateObs() = 0;

	virtual void newHL7(UInt64 eui,DevHL7^ hl7) = 0;
	virtual void updateHL7s() = 0;

	virtual void updateTitle(String^ title) = 0;
};
