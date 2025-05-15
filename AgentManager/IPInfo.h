#pragma once

using namespace System;

public ref class IPInfo
{
public:
	String^ target;
	int port;

	IPInfo();
	bool isValidIP();
	bool isValidIP(String^ ip);
	String^ targetString();
	String^ selfString();
};
