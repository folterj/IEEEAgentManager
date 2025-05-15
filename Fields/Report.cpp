#include "StdAfx.h"
#include "Report.h"
#include "conversion.h"

Report::Report()
{
	reportId = gcnew Field(2);
	reportResult = gcnew Field(2);
}

bool Report::decode(array<Byte>^ data,int% index)
{
	bool ok = true;
	int index0 = index;

	ok &= reportId->decode(data,index);
	ok &= reportResult->decode(data,index);

	len = index - index0;

	ok &= (len <= data->Length);

	return ok;
}

array<Byte>^ Report::encode()
{
	array<Byte>^ data = gcnew array<Byte>(0);

	data = addData(data,reportId->encode());
	data = addData(data,reportResult->encode());

	len = data->Length;

	return data;
}

String^ Report::getShortDesc()
{
	TreeString^ desc = gcnew TreeString();

	desc->add("reportId:" + reportId->getShortDesc());
	desc->add("reportResult:" + resultId((int)reportResult->get()));

	return desc->string;
}

String^ Report::getFullDesc()
{
	return getShortDesc();
}
