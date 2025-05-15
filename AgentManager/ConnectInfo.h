#pragma once

#include "DevSpec.h"

using namespace System;

public ref class ConnectInfo
{
public:
	UInt64 eui;
	SpecType specType;
	bool init;

	ConnectInfo();
	ConnectInfo(UInt64 eui0,SpecType specType0);
};
