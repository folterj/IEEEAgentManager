#pragma once

#include "AMApp.h"

ref class Manager : public AMApp
{
public:
	Manager(AMModelInterface^ model0,ComInterface^ com0,UInt64 manEui0,UInt64 eui0,String^ spec0);

	virtual void connected() override;
	virtual void disconnected() override;
};
