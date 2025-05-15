#pragma once

#include "ComObserver.h"

using namespace System;
using namespace System::Collections;

ref class ComInterface abstract
{
protected:
	ArrayList comObservers;
public:
	bool isConnected;
	String^ errorMessage;

public:
	ComInterface();
	virtual bool pathExists(String^ path) = 0;
	virtual bool checkCom() = 0;
	virtual bool send(Object^ data) = 0;
	virtual bool sendToSelf(Object^ data) = 0;
	virtual void consume() = 0;
	virtual void close() = 0;

	void registerObserver(ComObserver^ observer);
	void unregisterObserver(ComObserver^ observer);

	void connected();
	void disconnected();
	void removed();
	Object^ dataReceived(Object^ data,bool expectResponse);
	void confReceived();
};
