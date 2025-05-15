#include "StdAfx.h"
#include "AMServer.h"
#include "Manager.h"
#include "MQCom.h"
#include "SerialCom.h"
#include "TCPCom.h"
#include "HTTPCom.h"

using namespace System::Globalization;
using namespace System::Diagnostics;

AMServer::AMServer()
	: AMModel()
{
	Random^ rnd = gcnew Random();
	for (int i=0;i<64/8;i++) {
		manEui *= 0x100;
		manEui |= rnd->Next(0xFF);
	}
	selftitle = String::Format("{0:X16}",manEui);
}

AMServer::~AMServer()
{
	Stopwatch sw;

	closing = true;
	if (connectCom) {
		// try to close connectCom
		String^ msg = String::Format("{0}",ComCommand::Disconnect);
		connectCom->sendToSelf(msg);
		sw.Start();
		while (sw.ElapsedMilliseconds < 1000) {
			// wait for any live manager to respond
			Application::DoEvents();
		}
		connectCom->consume();	// consume event
		if (closing) {
			// no live managers
			connectCom->close();
		}
		sw.Stop();
	}
}

bool AMServer::comInit(ComType comType0,Object^ comInfo)
{
	comType = comType0;
	switch (comType) {
		case ComType::MessageQueue:
			connectCom = gcnew MQCom(connectReqLabel,connectRespLabel,true);
			break;
		case ComType::TCP:
			connectCom = gcnew TCPCom((TCPInfo^)comInfo,true);
			break;
		case ComType::HTTP:
			connectCom = gcnew HTTPCom((IPInfo^)comInfo,connectReqLabel,connectRespLabel);
			break;
		case ComType::SerialPort:
			connectCom = gcnew SerialCom((SerialPort^)comInfo);
			break;
	}
	if (connectCom->isConnected) {
		connectCom->registerObserver(this);
		return true;
	}
	return false;
}

bool AMServer::connect(array<ConnectInfo^>^ devices)
{
	// dummy
	return true;
}

Object^ AMServer::dataReceived(Object^ connectData,bool expectResponse)
{
	Object^ responseData;
	String^ clientid;
	String^ manPath = createManPath(0);
	String^ agentPath;
	UInt64 eui;
	UInt64 prefManEui = 0;
	String^ spec;
	ComCommand command = ComCommand::None;
	int nparams = 0;
	int i = 0;

	if (connectData->GetType() == String::typeid) {
		// Make sure format is string
		String^ msg = connectData->ToString();
		if (msg != "") {
			array<String^>^ data = msg->Split(':');

			nparams = data->Length;
			if (nparams > 0) {
				command = (ComCommand)Enum::Parse(ComCommand::typeid,data[i++]);
				nparams--;
			}

			if (command == ComCommand::Query && nparams >= 1) {
				// query managers
				connectCom->consume();	// consume message
				clientid = data[i++];
				responseData = createQueryResp(clientid,manPath,manEui);
				if (expectResponse) {
					return responseData;
				} else {
					connectCom->send(responseData);
				}
				// lazy consume to allow other managers to receive message too
			} else if (command == ComCommand::Connect && nparams >= 4) {
				// client connect request
				clientid = data[i++];
				agentPath = data[i++];
				eui = UInt64::Parse(data[i++],NumberStyles::HexNumber);
				spec = data[i++];
				if (nparams >= 5) {
					// check preferred manager EUI
					prefManEui = UInt64::Parse(data[i++],NumberStyles::HexNumber);
				}
				if (prefManEui == manEui || prefManEui == 0) {
					connectCom->consume();	// consume message
					// instantiate manager
					manPath = createComManager(manEui,agentPath,eui,spec);
					// send back response with manager path
					responseData = createConnectResp(clientid,manPath,manEui,eui,spec);
					if (expectResponse) {
						return responseData;
					} else {
						connectCom->send(responseData);
					}
				}
			} else if (command == ComCommand::Disconnect && !closing) {
				// received by live manager (ignore if this is the closing manager itself!)
				// disconnecting com channel; respond to keep alive
				connectCom->consume();	// consume message
				String^ msg = String::Format("{0}",ComCommand::DisconnectResp);
				connectCom->sendToSelf(msg);
			} else if (command == ComCommand::DisconnectResp && closing) {
				// received by closing manager
				// live managers still out there; don't close connectCom
				closing = false;
			}
		}
	}
	return nullptr;
}

String^ AMServer::createComManager(UInt64 manEui,String^ agentPath,UInt64 eui,String^ spec)
{
	ComInterface^ com;
	String^ manPath;

	switch (comType) {
		case ComType::MessageQueue:
			manPath = createManPath(eui);
			com = gcnew MQCom(agentPath,manPath,false);
			break;
		case ComType::HTTP:
			manPath = createManPath(eui);
			com = gcnew HTTPCom((HTTPCom^)connectCom,agentPath,manPath);
			break;
		default:
			com = connectCom;
			break;
	}
	createManager(com,eui,spec);
	return manPath;
}

bool AMServer::createManager(ComInterface^ com,UInt64 eui,String^ spec)
{
	AMApp^ manager;

	coms.Add(com);
	if (com->checkCom()) {
		manager = gcnew Manager(this,com,manEui,eui,spec);
		apps.Add(manager);
		return true;
	}
	return false;
}

void AMServer::confReceived()
{
}

String^ AMServer::createQueryResp(String^ destId,String^ manPath,UInt64 eui)
{
	return String::Format("{0}:{1}:{2}:{3:X16}",ComCommand::QueryResp,destId,manPath,eui);
}

String^ AMServer::createConnectResp(String^ destId,String^ manPath,UInt64 manEui0,UInt64 eui,String^ spec)
{
	// server: respond with guid/destId,manPath,manEui,agentEui,devSpec
	return String::Format("{0}:{1}:{2}:{3:X16}:{4:X16}:{5}",ComCommand::ConnectResp,destId,manPath,manEui0,eui,spec);
}

String^ AMServer::createManPath(UInt64 eui)
{
	if (eui != 0) {
		return String::Format("{0}{1:X16}_{2:X16}",basePath,manEui,eui);
	}
	return String::Format("{0}{1:X16}",basePath,manEui);
}
