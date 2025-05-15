#include "StdAfx.h"
#include "MQCom.h"
#include "defines.h"

MQCom::MQCom(String^ sendPath0,String^ recPath0,bool peekMode0)
	: ComInterface()
{
	sendPath = privatePrefix + sendPath0;
	sendconfPath = privatePrefix + sendPath0 + "conf";
	recPath = privatePrefix + recPath0;
	peekMode = peekMode0;

	sendQueue = connectQueue(sendPath);
	if (!sendQueue) {
		System::Windows::Forms::MessageBox::Show(errorMessage,"Connect Error");
		return;
	}
	sendQueue->MessageReadPropertyFilter->CorrelationId = true;
	sendconfQueue = connectQueue(sendconfPath);
	if (sendconfQueue) {
		sendconfQueue->MessageReadPropertyFilter->Acknowledgment = true;
		sendconfQueue->MessageReadPropertyFilter->CorrelationId = true;
	}
	recQueue = connectQueue(recPath);
	if (!recQueue) {
		System::Windows::Forms::MessageBox::Show(errorMessage,"Connect Error");
		return;
	}

	if (recQueue) {
		if (peekMode) {
			receiveThread = gcnew Thread(gcnew ThreadStart(this,&MQCom::peekThreadFunction));
		} else {
			receiveThread = gcnew Thread(gcnew ThreadStart(this,&MQCom::receiveThreadFunction));
		}
		receiveThread->Start();
	}
	connected();
}

MQCom::~MQCom()
{
	if (receiveThread) {
		if (Thread::CurrentThread != receiveThread) {
			receiveThread->Abort();
		}
	}
	if (sendconfQueue) {
		sendconfQueue->Close();
		try {
			if (MessageQueue::Exists(sendconfQueue->Path)) {
				MessageQueue::Delete(sendconfQueue->Path);
			}
		} catch(Exception^) {
		}
		delete sendconfQueue;
	}
}

void MQCom::close()
{
	if (sendQueue) {
		sendQueue->Close();
		if (MessageQueue::Exists(sendQueue->Path)) {
			MessageQueue::Delete(sendQueue->Path);
		}
		delete sendQueue;
	}
	if (recQueue) {
		recQueue->Close();
		if (MessageQueue::Exists(recQueue->Path)) {
			MessageQueue::Delete(recQueue->Path);
		}
		delete recQueue;
	}
}

bool MQCom::pathExists(String^ path)
{
	return MessageQueue::Exists(privatePrefix + path);
}

bool MQCom::checkCom()
{
	return (sendQueue && recQueue);
}

MessageQueue^ MQCom::connectQueue(String^ path)
{
	MessageQueue^ queue;

	try {
		if (!MessageQueue::Exists(path)) {
			MessageQueue::Create(path);
		}
		queue = gcnew MessageQueue(path);
		// Type String does not seem to be supported by the formatter by default; include all possible types
		queue->Formatter = gcnew XmlMessageFormatter(gcnew array<Type^>{String::typeid,
																		ComCommand::typeid,
																		array<Byte>::typeid});
		queue->Purge();
	} catch (ArgumentException^ e) {
		errorMessage = e->Message;
	} catch (Exception^ e) {
		errorMessage = e->Message;
		if (!errorMessage) {
			errorMessage = String::Format("Error code: 0x{0:X}",((MessageQueueException^)e)->ErrorCode);
		}
	}
	return queue;
}

bool MQCom::send(Object^ data)
{
	Message^ msg;

	try {
		msg = gcnew Message(data);
		msg->AdministrationQueue = sendconfQueue;
		msg->AcknowledgeType = AcknowledgeTypes::PositiveReceive;
		if (sendQueue) {
			sendQueue->Send(msg);
			receiveconfThread = gcnew Thread(gcnew ParameterizedThreadStart(this,&MQCom::receiveconfThreadFunction));
			receiveconfThread->Start(msg->Id);
			return true;
		}
	} catch (Exception^ e) {
		errorMessage = e->Message;
		if (!errorMessage) {
			errorMessage = String::Format("Error code: 0x{0:X}",((MessageQueueException^)e)->ErrorCode);
		}
	}
	return false;
}

bool MQCom::sendToSelf(Object^ data)
{
	Message^ msg;

	try {
		msg = gcnew Message(data);
		msg->AcknowledgeType = AcknowledgeTypes::None;
		if (recQueue) {
			recQueue->Send(msg);
			return true;
		}
	} catch (Exception^ e) {
		errorMessage = e->Message;
		if (!errorMessage) {
			errorMessage = String::Format("Error code: 0x{0:X}",((MessageQueueException^)e)->ErrorCode);
		}
	}
	return false;
}

void MQCom::receiveThreadFunction()
{
	// *** use timeout period (and check exists); if no longer valid issue disconnect event
	Message^ msg;
	Object^ object;
	ComCommand command;
	
	while (true) {
		try {
			msg = recQueue->Receive(TimeSpan::FromMilliseconds(10));
			object = msg->Body;
			if (object->GetType() == ComCommand::typeid) {
				command = (ComCommand)object;
				switch (command) {
					case ComCommand::Connect:		connected();	break;
					case ComCommand::Disconnect:	disconnected();	break;
					case ComCommand::Remove:		removed();		break;
				}
			} else {
				dataReceived(object,false);
			}
		} catch (MessageQueueException^ e) {
			if (	e->MessageQueueErrorCode == MessageQueueErrorCode::QueueDeleted ||
					e->MessageQueueErrorCode == MessageQueueErrorCode::QueueNotFound) {
				removed();
				delete this;
				break;
			}
		}
	}
}

void MQCom::peekThreadFunction()
{
	// *** use timeout period (and check exists); if no longer valid issue disconnect event
	Message^ msg;
	
	while (true) {
		try {
			msg = recQueue->Peek(TimeSpan::FromMilliseconds(10));
			dataReceived(msg->Body,false);
		} catch (MessageQueueException^ e) {
			if (	e->MessageQueueErrorCode == MessageQueueErrorCode::QueueDeleted ||
					e->MessageQueueErrorCode == MessageQueueErrorCode::QueueNotFound) {
				removed();
				delete this;
				break;
			}
		}
	}
}

void MQCom::receiveconfThreadFunction(Object^ id)
{
	Message^ msg;
	
	try {
		msg = sendconfQueue->ReceiveByCorrelationId(id->ToString(),TimeSpan::FromSeconds(10));
		confReceived();
	} catch (Exception^) {
	}
}

void MQCom::consume()
{
	try {
		recQueue->Receive(TimeSpan::FromMilliseconds(10));
	} catch (Exception^) {
	}
}
