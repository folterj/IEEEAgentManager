#include "StdAfx.h"
#include "TCPCom.h"
#include "defines.h"
#include "util.h"

using namespace System::IO;
using namespace System::Windows::Forms;

TCPCom::TCPCom(TCPInfo^ portInfo0,bool listen)
	: ComInterface()
{
	portInfo = portInfo0;
	if (!start(listen)) {
		MessageBox::Show(errorMessage,"Connect Error");
		return;
	}
	connected();
}

TCPCom::TCPCom(TCPCom^ tcpCom,bool listen)
{
	portInfo = tcpCom->portInfo;
	if (!start(listen)) {
		MessageBox::Show(errorMessage,"Connect Error");
		return;
	}
	connected();
}

TCPCom::~TCPCom()
{
	if (listenThread) {
		listenThread->Abort();
	}
	closing = true;
}

bool TCPCom::start(bool listen)
{
	targetIpInfo = portInfo->targetIpInfo;
	listenPort = portInfo->listenPort;
	closing = false;
	try {
		socket = gcnew Socket(targetIpInfo->Address->AddressFamily,SocketType::Stream,ProtocolType::Tcp);
		if (listen) {
			socket->Bind(gcnew IPEndPoint(IPAddress::Any,listenPort));
			socket->Listen(10);
			listenThread = gcnew Thread(gcnew ThreadStart(this,&TCPCom::listenThreadFunction));
		} else {
			listenThread = gcnew Thread(gcnew ThreadStart(this,&TCPCom::simpleReceiveThreadFunction));
		}
		listenThread->Start();
		return true;
	} catch (Exception^ e) {
		errorMessage = e->Message;
	}
	return false;
}

bool TCPCom::pathExists(String^ path)
{
	return true;
}

bool TCPCom::checkCom()
{
	if (socket) {
		return true;
	}
	return false;
}

bool TCPCom::send(Object^ data)
{
	bool ok = false;

	try {
		if (socket) {
			if (socket->Connected) {
				ok = true;
			}
		}
		if (!ok) {
			// create
			socket->Connect(targetIpInfo);
		}
		writeOut(socket,data);

		confReceived();
	
	} catch (Exception^ e) {
		errorMessage = e->Message;
		ok = false;
	}
	return ok;
}

void TCPCom::writeOut(Socket^ outSocket,Object^ data)
{
	array<Byte>^ dataArray;
	ComCommand command;

	if (data->GetType() == String::typeid) {
		// string
		dataArray = stringToBytes((String^)data);
	} else {
		// binary
		if (data->GetType() == ComCommand::typeid) {
			// command
			command = (ComCommand)data;
			dataArray = gcnew array<Byte>(1);
			dataArray[0] = (Byte)command;
		} else {
			// byte array
			dataArray = (array<Byte>^)data;
		}
	}
	outSocket->Send(dataArray);
}

Object^ TCPCom::processReceiving(Socket^ receiveSocket,bool expectResponse)
{
	Object^ content;
	array<Byte>^ dataArray;
	String^ datas;
	bool isCommand = false;
	bool isAscii = false;

	int bytesRead = 0;
	int MAX_BUFFER_SIZE = 4096;
	array<Byte>^ buffer = gcnew array<Byte>(MAX_BUFFER_SIZE);

	try {
		//blocks until a client sends a message
		bytesRead = receiveSocket->Receive(buffer);
	} catch (Exception^ e) {
		//a socket error has occured
		errorMessage = e->Message;
		return nullptr;
	}

	if (bytesRead > 0)
	{
		dataArray = gcnew array<Byte>(bytesRead);
		Array::Copy(buffer,dataArray,bytesRead);
		datas = bytesToString(dataArray);
		isCommand = (bytesRead == 1);
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
			switch (buffer[0]) {
				case ComCommand::Connect:		connected();	break;
				case ComCommand::Disconnect:	disconnected();	break;
				case ComCommand::Remove:		removed();		break;
			}
		} else if (isAscii) {
			// ascii
			content = datas;
		} else {
			// byte array
			content = dataArray;
		}
	}
	if (content && !isCommand) {
		return dataReceived(content,expectResponse);
	}
	return nullptr;
}

bool TCPCom::sendToSelf(Object^ data)
{
	return true;
}

void TCPCom::consume()
{
}

void TCPCom::close()
{
	if (socket) {
		socket->Close();
	}
}

void TCPCom::listenThreadFunction()
{
	bool ok = true;

	while (ok && !closing) {
		try {
			// blocks until a client has connected to the server
			Socket^ receiveSocket = socket->Accept();

			Thread^ receiveThread = gcnew Thread(gcnew ParameterizedThreadStart(this,&TCPCom::multiReceiveThreadFunction));
			receiveThread->Start(receiveSocket);

		} catch(Exception^ e) {
			errorMessage = e->Message;
			ok = false;
		}
	}
}

void TCPCom::multiReceiveThreadFunction(Object^ receiveSocket0)
{
	Object^ responseData;
	Socket^ receiveSocket;
	bool ok = true;

	try {
		receiveSocket = (Socket^)receiveSocket0;
	} catch(Exception^ e) {
		String^ error = e->Message;
		ok = false;
	}

	while (ok && !closing) {
		try {
			if (receiveSocket->Available > 0) {
				responseData = processReceiving(receiveSocket,true);
				if (responseData) {
					writeOut(receiveSocket,responseData);
				}
			} else {
				Thread::Sleep(100);
			}
		} catch(Exception^ e) {
			errorMessage = e->Message;
			ok = false;
		}
	}
}

void TCPCom::simpleReceiveThreadFunction()
{
	bool ok = true;

	while (ok && !closing) {
		try {
			if (socket->Available > 0) {
				processReceiving(socket,false);
			} else {
				Thread::Sleep(100);
			}
		} catch(Exception^ e) {
			errorMessage = e->Message;
			ok = false;
		}
	}
}
