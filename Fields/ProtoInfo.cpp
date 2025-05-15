#include "StdAfx.h"
#include "ProtoInfo.h"
#include "phd_constants.h"

ProtoInfo::ProtoInfo()
{
	protoVer = gcnew Field(4);
	encoding = gcnew Field(2);
	nomVer = gcnew Field(4);
	funcUnits = gcnew Field(4);
	systemType = gcnew Field(4);
	systemIdLen = gcnew Field(2);
	systemId = gcnew Field();
	configId = gcnew Field(2);
	reqMode = gcnew Field(2);
	reqAgentCount = gcnew Field(1);
	reqManagerCount = gcnew Field(1);
	optionCount = gcnew Field(2);
	optionLen = gcnew Field(2);
}

bool ProtoInfo::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= protoVer->decode(data,index);
	ok &= encoding->decode(data,index);
	ok &= nomVer->decode(data,index);
	ok &= funcUnits->decode(data,index);
	ok &= systemType->decode(data,index);
	ok &= systemIdLen->decode(data,index);
	systemId->setLen((int)systemIdLen->get());
	ok &= systemId->decode(data,index);
	ok &= configId->decode(data,index);
	ok &= reqMode->decode(data,index);
	ok &= reqAgentCount->decode(data,index);
	ok &= reqManagerCount->decode(data,index);
	ok &= optionCount->decode(data,index);
	ok &= optionLen->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ ProtoInfo::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);

	systemIdLen->set(systemId->getLen());

	data = addData(data,protoVer->encode());
	data = addData(data,encoding->encode());
	data = addData(data,nomVer->encode());
	data = addData(data,funcUnits->encode());
	data = addData(data,systemType->encode());
	data = addData(data,systemIdLen->encode());
	data = addData(data,systemId->encode());
	data = addData(data,configId->encode());
	data = addData(data,reqMode->encode());
	data = addData(data,reqAgentCount->encode());
	data = addData(data,reqManagerCount->encode());
	data = addData(data,optionCount->encode());
	data = addData(data,optionLen->encode());

	len = data->Length;

	return data;
}

String^ ProtoInfo::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();
	UInt32 type = (UInt32)systemType->get();
	String^ s = "";

	if (type & SYS_TYPE_MANAGER) {
		s += "Manager";
	}
	if (type & SYS_TYPE_AGENT) {
		s += "Agent";
	}
	desc->add("systemType:" + s);
	desc->add(String::Format("configId:{0}",configId->get()));

	return desc->string;
}

String^ ProtoInfo::getFullDesc()
{
	TreeString^ desc = gcnew TreeString();
	UInt32 type = (UInt32)systemType->get();
	String^ s = "";

	desc->add("protoVer:" + protoVer->getShortDesc());

	if (type & SYS_TYPE_MANAGER) {
		s += "Manager";
	}
	if (type & SYS_TYPE_AGENT) {
		s += "Agent";
	}
	desc->add("systemType:" + s);
	desc->add(String::Format("configId:{0}",configId->get()));

	return desc->string;
}
