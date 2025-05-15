#pragma once

#include "ComInterface.h"

using namespace System::IO::Ports;

ref class SerialCom : public ComInterface
{
public:
	SerialPort^ port;

	SerialCom(SerialPort^ port0);

	void setPort(SerialPort^ port0);

	virtual bool pathExists(String^ path) override;
	virtual bool checkCom() override;
	virtual bool send(Object^ data) override;
	virtual bool sendToSelf(Object^ data) override;
	virtual void consume() override;
	virtual void close() override;

	void receivedHandler(Object^ sender,SerialDataReceivedEventArgs^ e);
};
