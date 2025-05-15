#pragma once

using namespace System;
using namespace Net;

public ref class TCPInfo
{
public:
	static int defServerPort = 8080;
	static int defClientPort = 8081;

	IPEndPoint^ targetIpInfo;
	int listenPort;

	TCPInfo();
	bool parse(String^ ips,String^ ports,String^ listenPorts);
};
