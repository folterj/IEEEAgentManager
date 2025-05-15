#pragma once

#include "ComInterface.h"

using namespace System;
using namespace System::Timers;
using namespace System::Collections::Generic;

ref class ApduSender
{
public:
	Generic::Queue<array<Byte>^>^ queue;
	ComInterface^ com;
	Timers::Timer sendTimer;	// to prevent lock up
	bool sending;

	ApduSender(ComInterface^ com);
	bool addSend(array<Byte>^ apdu);
	bool sendNext();
	void confReceived();
	void sendTimer_Tick(Object^ sender, ElapsedEventArgs^ e);
	void clearAll();
};
