#pragma once

#include "ComInterface.h"
#include "TCPInfo.h"

using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;

ref class TCPCom : public ComInterface
{
public:
	TCPInfo^ portInfo;
	IPEndPoint^ targetIpInfo;
	int listenPort;
	Socket^ socket;
	Thread^ listenThread;
	bool closing;

	TCPCom(TCPInfo^ portInfo0,bool listen);
	TCPCom(TCPCom^ tcpCom,bool listen);
	~TCPCom();

	bool start(bool listen);

	virtual bool pathExists(String^ path) override;
	virtual bool checkCom() override;
	virtual bool send(Object^ data) override;
	virtual bool sendToSelf(Object^ data) override;
	virtual void consume() override;
	virtual void close() override;

	void writeOut(Socket^ outSocket,Object^ data);
	Object^ processReceiving(Socket^ receiveSocket,bool expectResponse);
	void listenThreadFunction();
	void multiReceiveThreadFunction(Object^ receiveSocket0);
	void simpleReceiveThreadFunction();
};
