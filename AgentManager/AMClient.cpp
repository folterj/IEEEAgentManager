#include "StdAfx.h"
#include "AMClient.h"
#include "Agent.h"
#include "MQCom.h"
#include "SerialCom.h"
#include "TCPCom.h"
#include "HTTPCom.h"
#include "util.h"

using namespace System::Globalization;
using namespace System::Diagnostics;

AMClient::AMClient()
	: AMModel()
{
}

bool AMClient::comInit(ComType comType0,Object^ comInfo)
{
	comType = comType0;
	switch (comType) {
		case ComType::MessageQueue:
			connectCom = gcnew MQCom(connectRespLabel,connectReqLabel,true);
			break;
		case ComType::TCP:
			connectCom = gcnew TCPCom((TCPInfo^)comInfo,false);
			break;
		case ComType::HTTP:
			connectCom = gcnew HTTPCom((IPInfo^)comInfo,connectRespLabel,"");
			break;
		case ComType::SerialPort:
			connectCom = gcnew SerialCom((SerialPort^)comInfo);
			break;
	}
	if (connectCom->isConnected) {
		connectCom->registerObserver(this);
		return queryManagers();
	}
	return false;
}

bool AMClient::queryManagers()
{
	Stopwatch sw;

	clearQueried();
	sendQueryManagers();
	// wait for managers to respond / store information
	sw.Start();
	while (sw.ElapsedMilliseconds < 1000) {
		Application::DoEvents();
	}
	return (manEuis.Count > 0);
}

bool AMClient::connect(array<ConnectInfo^>^ devices)
{
	connectDevices = devices;
	// start connecting
	return checkConnect();
}

void AMClient::checkConnectDelayed()
{
	connectTimer.Interval = 100;	// 100 ms
	connectTimer.Elapsed += gcnew ElapsedEventHandler(this,&AMClient::checkConnect_Tick);
	connectTimer.Start();
}

void AMClient::checkConnect_Tick(Object^ sender, ElapsedEventArgs^ e)
{
	connectTimer.Stop();
	checkConnect();
}

bool AMClient::checkConnect()
{
	for each (ConnectInfo^ device in connectDevices) {
		if (!device->init) {
			// find first uninitialised device
			device->init = true;
			return connectAgent(device);
		}
	}
	return false;
}

bool AMClient::connectAgent(ConnectInfo^ device)
{
	String^ agentPath = createPath(basePath,device->eui);
	String^ spec = Enum::GetName(SpecType::typeid,device->specType);
	return sendConnectReq(id,agentPath,device);
}

Object^ AMClient::dataReceived(Object^ connectData,bool expectResponse)
{
	String^ clientid;
	String^ manPath;
	UInt64 manEui0,eui;
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

			if (command == ComCommand::QueryResp && nparams >= 1) {
				// query response
				clientid = data[i++];
				if (clientid == id) {
					// message addressed to this client
					connectCom->consume();	// consume message
					manPath = data[i++];
					manEui0 = UInt64::Parse(data[i++],NumberStyles::HexNumber);
					storeQueried(manPath,manEui0);
				}
			} else if (command == ComCommand::ConnectResp && nparams >= 4) {
				// connect response
				clientid = data[i++];
				if (clientid == id) {
					// message addressed to this client
					connectCom->consume();	// consume message
					manPath = data[i++];
					manEui = UInt64::Parse(data[i++],NumberStyles::HexNumber);
					eui = UInt64::Parse(data[i++],NumberStyles::HexNumber);
					spec = data[i++];
					createComAgent(manPath,eui,spec);
					// check for other devices
					checkConnectDelayed();
				}
			}
		}
	}
	return nullptr;
}

void AMClient::confReceived()
{
}

bool AMClient::sendQueryManagers()
{
	String^ msg = String::Format("{0}:{1}",ComCommand::Query,id);
	return connectCom->send(msg);
}

bool AMClient::sendConnectReq(String^ srcId,String^ agentPath,ConnectInfo^ device)
{
	// client: send guid/srcId,agentPath,agentEui,devSpec(,prefManEui)
	String^ msg = String::Format("{0}:{1}:{2}:{3:X16}:{4}",
								ComCommand::Connect,srcId,agentPath,device->eui,device->specType);
	if (manEui != 0) {
		msg+= String::Format(":{0:X16}",manEui);
	}
	return connectCom->send(msg);
}

bool AMClient::createComAgent(String^ manPath,UInt64 eui,String^ spec)
{
	// create connection & instantiate Agent
	ComInterface^ com;
	String^ agentPath;

	switch (comType) {
		case ComType::MessageQueue:
			agentPath = createPath(basePath,eui);
			com = gcnew MQCom(manPath,agentPath,false);
			break;
		case ComType::HTTP:
			agentPath = createPath(basePath,eui);
			com = gcnew HTTPCom((HTTPCom^)connectCom,manPath,agentPath);
			break;
		default:
			com = connectCom;
			break;
	}
	return createAgent(com,eui,spec);
}

bool AMClient::createAgent(ComInterface^ com,UInt64 eui,String^ spec)
{
	AMApp^ agent;

	coms.Add(com);
	if (com->checkCom()) {
		agent = gcnew Agent(this,com,eui,spec);
		apps.Add(agent);
		return true;
	}
	return false;
}
