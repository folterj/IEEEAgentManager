#include "StdAfx.h"
#include "ComInterface.h"

ComInterface::ComInterface()
{
	isConnected = false;
	errorMessage = "";
}

void ComInterface::registerObserver(ComObserver^ observer)
{
	comObservers.Add(observer);
}

void ComInterface::unregisterObserver(ComObserver^ observer)
{
	comObservers.Remove(observer);
}

void ComInterface::connected()
{
	isConnected = true;
	for (int i=0;i<comObservers.Count;i++) {
		((ComObserver^)comObservers[i])->connected();
	}
}

void ComInterface::disconnected()
{
	isConnected = false;
	for (int i=0;i<comObservers.Count;i++) {
		((ComObserver^)comObservers[i])->disconnected();
	}
}

void ComInterface::removed()
{
	for (int i=0;i<comObservers.Count;i++) {
		((ComObserver^)comObservers[i])->removed();
	}
}

Object^ ComInterface::dataReceived(Object^ data,bool expectResponse)
{
	Object^ finalResponse;
	Object^ response;
	for (int i=0;i<comObservers.Count;i++) {
		response = ((ComObserver^)comObservers[i])->dataReceived(data,expectResponse);
		if (expectResponse && response) {
			finalResponse = response;
		}
	}
	return finalResponse;
}

void ComInterface::confReceived()
{
	for (int i=0;i<comObservers.Count;i++) {
		((ComObserver^)comObservers[i])->confReceived();
	}
}
