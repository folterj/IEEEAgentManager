#include "StdAfx.h"
#include "HTTPCom.h"
#include "defines.h"

using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

HTTPCom::HTTPCom(IPInfo^ portInfo0,String^ sendUrl0,String^ listenUrl0)
	: ComInterface()
{
	portInfo = portInfo0;
	if (!start(sendUrl0,listenUrl0)) {
		MessageBox::Show(errorMessage,"Connect Error");
		return;
	}
	connected();
}

HTTPCom::HTTPCom(HTTPCom^ httpCom,String^ sendUrl0,String^ listenUrl0)
{
	portInfo = httpCom->portInfo;
	if (!start(sendUrl0,listenUrl0)) {
		MessageBox::Show(errorMessage,"Connect Error");
		return;
	}
	connected();
}

HTTPCom::~HTTPCom()
{
	if (listenUrl) {
		listenThread->Abort();
	}
}

bool HTTPCom::start(String^ sendUrl0,String^ listenUrl0)
{
	sendUrl = portInfo->targetString() + sendUrl0 + "/";
	if (listenUrl0 != "") {
		listenUrl = portInfo->selfString() + listenUrl0 + "/";
	}
	return createListener();
}

bool HTTPCom::createListener()
{
	try {
		if (listenUrl) {
			listener = gcnew HttpListener();
			listener->Prefixes->Add(listenUrl);
			listener->Start();

			listenThread = gcnew Thread(gcnew ThreadStart(this,&HTTPCom::listenThreadFunction));
			listenThread->Start();
		}
		return true;
	} catch(Exception^ e) {
		errorMessage = e->Message;
	}
	return false;
}

bool HTTPCom::pathExists(String^ path)
{
	return true;
}

bool HTTPCom::checkCom()
{
	return (sendUrl != "");
}

bool HTTPCom::send(Object^ data)
{
	HttpWebResponse^ response;

	try {
		HttpWebRequest^ request = (HttpWebRequest^)WebRequest::Create(sendUrl);
		request->UserAgent = "compatible";
		request->Timeout = 1000;
		request->Method = "POST";
		request->Accept = "*/*";
		// set content type before opening stream
		if (data->GetType() == String::typeid) {
			// string
			request->ContentType = "text/plain";
			request->ContentLength = ((String^)data)->Length;
		} else {
			// binary
			request->ContentType = "application/octet-stream";
			if (data->GetType() == ComCommand::typeid) {
				request->ContentLength = 1;
			} else {
				request->ContentLength = ((array<Byte>^)data)->Length;
			}
		}

		writeOut(request->GetRequestStream(),data);

		response = (HttpWebResponse^)request->GetResponse();

		confReceived();

		if (request->HaveResponse) {
			if (response->ContentLength > 0) {
				processReceiving(response->GetResponseStream(),gcnew UTF8Encoding,response->ContentType,response->ContentLength,false);
			}
		}
		return true;
		
	} catch (Exception^ e) {
		errorMessage = e->Message;
	} finally {
		if (response) {
			response->Close();
		}
	}
	return false;
}

void HTTPCom::writeOut(Stream^ outStream,Object^ data)
{
	array<Byte>^ dataArray;
	ComCommand command;

	if (data->GetType() == String::typeid) {
		// string
		StreamWriter^ writer = gcnew StreamWriter(outStream);
		writer->Write(data);
		writer->Close();
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
		outStream->Write(dataArray,0,dataArray->Length);
	}
	outStream->Close();
}

Object^ HTTPCom::processReceiving(Stream^ recStream,Encoding^ encoding,String^ contentType,Int64 contentLength,bool expectResponse)
{
	Object^ content;
	array<Byte>^ dataArray;
	bool isCommand = false;
	ComCommand command;

	if (contentType->Contains("text")) {
		// string
		StreamReader^ reader = gcnew StreamReader(recStream,encoding);
		content = reader->ReadToEnd();
		reader->Close();
	} else {
		// binary
		dataArray = gcnew array<Byte>((int)contentLength);
		recStream->Read(dataArray,0,(int)contentLength);
		content = dataArray;

		if (dataArray->Length == 1) {
			// command
			command = (ComCommand)dataArray[0];
			switch (command) {
				case ComCommand::Connect:		connected();	break;
				case ComCommand::Disconnect:	disconnected();	break;
				case ComCommand::Remove:		removed();		break;
			}
			isCommand = true;
		}
	}
	recStream->Close();
	if (content && !isCommand) {
		return dataReceived(content,expectResponse);
	}
	return nullptr;
}

bool HTTPCom::sendToSelf(Object^ data)
{
	return true;
}

void HTTPCom::consume()
{
}

void HTTPCom::close()
{
	if (listener) {
		listener->Stop();
	}
}

void HTTPCom::listenThreadFunction()
{
	Object^ responseData;
	bool ok = true;

	while (ok) {
		try {
			// GetContext blocks while waiting for a request
			HttpListenerContext^ context = listener->GetContext();
			HttpListenerRequest^ request = context->Request;
			HttpListenerResponse^ response = context->Response;

			responseData = processReceiving(request->InputStream,request->ContentEncoding,request->ContentType,request->ContentLength64,true);
			if (responseData) {
				// set content type before opening stream
				if (responseData->GetType() == String::typeid) {
					// string
					response->ContentType = "text/plain";
					response->ContentLength64 = ((String^)responseData)->Length;
				} else {
					// binary
					response->ContentType = "application/octet-stream";
					response->ContentLength64 = ((array<Byte>^)responseData)->Length;
				}
				writeOut(response->OutputStream,responseData);
			}
			response->Close();	// force response / release
		} catch(Exception^ e) {
			errorMessage = e->Message;
			ok = false;
		}
	}
}
