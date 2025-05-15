#include "StdAfx.h"
#include "ConnectInfo.h"

ConnectInfo::ConnectInfo()
{
	eui = 0;
	specType = SpecType::None;
	init = false;
}

ConnectInfo::ConnectInfo(UInt64 eui0,SpecType specType0)
{
	eui = eui0;
	specType = specType0;
	init = false;
}
