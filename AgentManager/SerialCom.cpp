#include "StdAfx.h"
#include "SerialCom.h"
#include "defines.h"

using namespace System::Text;
using namespace System::Collections::Generic;

SerialCom::SerialCom(SerialPort^ port0)
	: ComInterface()
{
	setPort(port0);
	connected();
}

void SerialCom::close()
{
	port->Close();
}

void SerialCom::setPort(SerialPort^ port0)
{
	port = port0;
	port->DataReceived += gcnew SerialDataReceivedEventHandler(this,&SerialCom::receivedHandler);
}

bool SerialCom::pathExists(String^ path)
{
	return true;
}

bool SerialCom::checkCom()
{
	return port->IsOpen;
}

bool SerialCom::send(Object^ data)
{
	array<Byte>^ dataArray;
	ComCommand command;

	try {
		if (data->GetType() == String::typeid) {
			// string
			String^ s = data->ToString();
			port->Write(s);
		} else {
			if (data->GetType() == ComCommand::typeid) {
				// command
				command = (ComCommand)data;
				dataArray = gcnew array<Byte>(1);
				dataArray[0] = (Byte)command;
			} else {
				// byte array
				dataArray = (array<Byte>^)data;
			}
			port->Write(dataArray,0,dataArray->Length);
		}
		return true;
	} catch (Exception^ e) {
		errorMessage = e->Message;
	}
	return false;
}

bool SerialCom::sendToSelf(Object^ data)
{
	return true;
}

void SerialCom::consume()
{
}

void SerialCom::receivedHandler(Object^ sender,SerialDataReceivedEventArgs^ e)
{
	List<Byte> data;
	array<Byte>^ dataArray;
	String^ datas;
	UTF8Encoding enc;
	bool isCommand = false;
	bool isAscii = false;

	while (port->BytesToRead > 0) {
		data.Add((Byte)port->ReadByte());
	}
	if (data.Count > 0) {
		dataArray = data.ToArray();
		datas = enc.GetString(dataArray);
		isCommand = (data.Count == 1);
		if (!isCommand) {
			isAscii = true;
			for each (Char c in datas) {
				if (c < 32 || c > 127) {
					isAscii = false;
				}
			}
		}
		
		if (isCommand) {
			// command
			switch (data[0]) {
				case ComCommand::Connect:		connected();	break;
				case ComCommand::Disconnect:	disconnected();	break;
				case ComCommand::Remove:		removed();		break;
			}
		} else if (isAscii) {
			// ascii
			dataReceived(datas,false);
		} else {
			// byte array
			dataReceived(dataArray,false);
		}
	}
}
