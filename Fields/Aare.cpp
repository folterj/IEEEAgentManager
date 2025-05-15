#include "StdAfx.h"
#include "Aare.h"
#include "phd_constants.h"

Aare::Aare()
{
	assocResult = gcnew Field(2);
	protoId = gcnew Field(2);
	protoInfoLen = gcnew Field(2);
	protoInfo = gcnew ProtoInfo();
}

bool Aare::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= assocResult->decode(data,index);
	ok &= protoId->decode(data,index);
	ok &= protoInfoLen->decode(data,index);
	ok &= protoInfo->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ Aare::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ protoInfoData = protoInfo->encode();

	protoInfoLen->set(protoInfo->getLen());

	data = addData(data,assocResult->encode());
	data = addData(data,protoId->encode());
	data = addData(data,protoInfoLen->encode());
	data = addData(data,protoInfoData);

	len = data->Length;

	return data;
}

String^ Aare::getResultType()
{
	String^ desc;

	switch (assocResult->get()) {
		case ACCEPTED:								desc = "ACCEPTED";								break;
		case REJECTED_PERMANENT:					desc = "REJECTED_PERMANENT";					break;
		case REJECTED_TRANSIENT:					desc = "REJECTED_TRANSIENT";					break;
		case ACCEPTED_UNKNOWN_CONFIG:				desc = "ACCEPTED_UNKNOWN_CONFIG";				break;
		case REJECTED_NO_COMMON_PROTOCOL:			desc = "REJECTED_NO_COMMON_PROTOCOL";			break;
		case REJECTED_NO_COMMON_PARAMETER:			desc = "REJECTED_NO_COMMON_PARAMETER";			break;
		case REJECTED_UNKNOWN:						desc = "REJECTED_UNKNOWN";						break;
		case REJECTED_UNAUTHORIZED:					desc = "REJECTED_UNAUTHORIZED";					break;
		case REJECTED_UNSUPPORTED_ASSOC_VERSION:	desc = "REJECTED_UNSUPPORTED_ASSOC_VERSION";	break;
		default:									desc = assocResult->getShortDesc();				break;
	}
	return desc;
}

String^ Aare::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add("assocResult:" + getResultType());
	desc->add(String::Format("protoId:{0}",protoId->get()));
	desc->addChild("",protoInfo->getShortDesc());

	return desc->string;
}

String^ Aare::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();
	UInt16 result = (UInt16)assocResult->get();

	// simple fields
	desc->add("assocResult:" + getResultType());
	desc->add(String::Format("protoId:{0}",protoId->get()));
	desc->add(String::Format("protoInfoLen:{0}",protoInfoLen->get()));

	// composite fields
	desc->addChild("protoInfo",protoInfo->getFullDesc());

	return desc->string;
}
