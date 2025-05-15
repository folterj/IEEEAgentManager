#include "StdAfx.h"
#include "Proto.h"

Proto::Proto(int nProtoInfo)
{
	protoId = gcnew Field(2);
	protoInfoLen = gcnew Field(2);
	protoInfo = gcnew array<ProtoInfo^>(nProtoInfo);
	for (int i=0;i<nProtoInfo;i++) {
		protoInfo[i] = gcnew ProtoInfo();
	}
}

bool Proto::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= protoId->decode(data,index);
	ok &= protoInfoLen->decode(data,index);
	for (int i=0;i<protoInfo->Length;i++) {
		ok &= protoInfo[i]->decode(data,index);
	}

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ Proto::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);
	array<Byte>^ protoInfoData = gcnew array<Byte>(0);
	int totsublen = 0;

	for (int i=0;i<protoInfo->Length;i++) {
		protoInfoData = addData(protoInfoData,protoInfo[i]->encode());
		totsublen += protoInfo[i]->getLen();
	}
	protoInfoLen->set(totsublen);

	data = addData(data,protoId->encode());
	data = addData(data,protoInfoLen->encode());
	data = addData(data,protoInfoData);

	len = data->Length;

	return data;
}

String^ Proto::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add(String::Format("protoId:{0}",protoId->get()));
	for (int i=0;i<protoInfo->Length;i++) {
		desc->addChild("",protoInfo[i]->getShortDesc());
	}
	return desc->string;
}

String^ Proto::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();
	
	// simple fields
	desc->add(String::Format("protoId:{0}",protoId->get()));
	desc->add(String::Format("protoInfoLen:{0}",protoInfoLen->get()));

	// composite fields
	for (int i=0;i<protoInfo->Length;i++) {
		desc->addChild("protoInfo",protoInfo[i]->getFullDesc());
	}
	return desc->string;
}
