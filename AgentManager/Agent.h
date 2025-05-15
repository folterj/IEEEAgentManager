#pragma once

#include "AMApp.h"

ref class Agent : public AMApp
{
public:
	Agent(AMModelInterface^ model0,ComInterface^ com0,UInt64 eui0,String^ spec0);

	virtual void connected() override;
	virtual void disconnected() override;
};
