#pragma once

#include "ComInterface.h"
#include "IPInfo.h"

using namespace System::IO;
using namespace System::Net;
using namespace System::Text;
using namespace System::Threading;

ref class HTTPCom : public ComInterface
{
public:
	IPInfo^ portInfo;
	String^ sendUrl;
	String^ listenUrl;
	HttpListener^ listener;
	Thread^ listenThread;

	HTTPCom(IPInfo^ portInfo0,String^ sendUrl0,String^ listenUrl0);
	HTTPCom(HTTPCom^ httpCom,String^ sendUrl0,String^ listenUrl0);
	~HTTPCom();

	bool start(String^ sendUrl0,String^ listenUrl0);
	bool createListener();

	virtual bool pathExists(String^ path) override;
	virtual bool checkCom() override;
	virtual bool send(Object^ data) override;
	virtual bool sendToSelf(Object^ data) override;
	virtual void consume() override;
	virtual void close() override;

	void writeOut(Stream^ outStream,Object^ data);
	Object^ processReceiving(Stream^ recStream,Encoding^ encoding,String^ contentType,Int64 contentLength,bool expectResponse);
	void listenThreadFunction();
};
