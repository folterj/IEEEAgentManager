#pragma once

#include "AMModel.h"
#include "DevSpec.h"

using namespace System;

ref class AMClient : public AMModel
{
public:
	Timers::Timer connectTimer;
	array<ConnectInfo^>^ connectDevices;

	AMClient();

	bool createComAgent(String^ manPath,UInt64 eui,String^ spec);
	bool createAgent(ComInterface^ com,UInt64 eui,String^ spec);
	bool connectAgent(ConnectInfo^ device);

	bool queryManagers();
	virtual bool comInit(ComType comType0,Object^ comInfo) override;

	virtual bool connect(array<ConnectInfo^>^ devices) override;
	void checkConnectDelayed();
	void checkConnect_Tick(Object^ sender, ElapsedEventArgs^ e);
	bool checkConnect();

	virtual Object^ dataReceived(Object^ data,bool expectResponse) override;
	virtual void confReceived() override;

	bool sendQueryManagers();
	bool sendConnectReq(String^ srcId,String^ agentPath,ConnectInfo^ device);
};
