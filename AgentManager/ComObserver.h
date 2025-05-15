#pragma once

using namespace System;

ref class ComObserver abstract
{
public:
	virtual void connected() = 0;
	virtual void disconnected() = 0;
	virtual void removed() = 0;
	virtual Object^ dataReceived(Object^ data,bool expectResponse) = 0;
	virtual void confReceived() = 0;
};
