#pragma once

#include "ComInterface.h"

#using <system.messaging.dll>

using namespace System;
using namespace System::Messaging;
using namespace System::Threading;

#define privatePrefix		".\\Private$\\"
#define connectReqLabel		"conreq"
#define connectRespLabel	"conresp"
#define connectReqPath		privatePrefix + connectReqLabel
#define connectRespPath		privatePrefix + connectRespLabel

ref class MQCom : public ComInterface
{
private:
	String^ sendPath;
	String^ sendconfPath;
	String^	recPath;
	MessageQueue^ sendQueue;
	MessageQueue^ sendconfQueue;
	MessageQueue^ recQueue;
	bool peekMode;

	Thread^ receiveThread;
	Thread^ receiveconfThread;

public:
	MQCom(String^ sendPath0,String^ recPath0,bool peekMode0);
	~MQCom();

	MessageQueue^ connectQueue(String^ path);
	virtual bool pathExists(String^ path) override;
	virtual bool checkCom() override;
	virtual bool send(Object^ data) override;
	virtual void close() override;
	virtual bool sendToSelf(Object^ data) override;
	virtual void consume() override;
	void receiveThreadFunction();
	void peekThreadFunction();
	void receiveconfThreadFunction(Object^ id);
};
