#pragma once

#include "AMModel.h"

using namespace System;

ref class AMServer : public AMModel
{
public:
	AMServer();
	~AMServer();

	String^ createComManager(UInt64 manEui,String^ agentPath,UInt64 eui,String^ spec);
	bool createManager(ComInterface^ com,UInt64 eui,String^ spec);

	virtual bool comInit(ComType comType0,Object^ comInfo) override;
	virtual bool connect(array<ConnectInfo^>^ devices) override;	// dummy
	virtual Object^ dataReceived(Object^ connectData,bool expectResponse) override;
	virtual void confReceived() override;

	String^ createQueryResp(String^ destId,String^ manPath,UInt64 eui);
	String^ createConnectResp(String^ destId,String^ manPath,UInt64 manEui0,UInt64 eui,String^ spec);

	String^ createManPath(UInt64 eui);
};
