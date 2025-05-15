#include "StdAfx.h"
#include "ApduSender.h"

ApduSender::ApduSender(ComInterface^ com)
{
	queue = gcnew Generic::Queue<array<Byte>^>();
	sending = false;
	this->com = com;

	sendTimer.Interval = 100;	// 100 ms time out; to prevent lock up
	sendTimer.Elapsed += gcnew ElapsedEventHandler(this,&ApduSender::sendTimer_Tick);
}

bool ApduSender::addSend(array<Byte>^ apdu)
{
	queue->Enqueue(apdu);
	return sendNext();
}

bool ApduSender::sendNext()
{
	bool ok = true;
	array<Byte>^ apdu;

	if (!sending) {
		if (queue->Count > 0) {
			apdu = queue->Dequeue();	// taken of queue before sending
			ok = com->send(apdu);
			sending = ok;
			if (ok) {
				sendTimer.Stop();
				sendTimer.Start();
			}
		}
	}
	return ok;
}

void ApduSender::confReceived()
{
	sendTimer.Stop();
	sending = false;
	sendNext();
}

void ApduSender::sendTimer_Tick(Object^ sender, ElapsedEventArgs^ e)
{
	// send time out; prevent lock up
	sendTimer.Stop();
	sending = false;
	// * display / log error?
	sendNext();
}

void ApduSender::clearAll()
{
	queue->Clear();
	sendTimer.Stop();
	sending = false;
}