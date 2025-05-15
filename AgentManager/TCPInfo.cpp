#include "StdAfx.h"
#include "TCPInfo.h"

TCPInfo::TCPInfo()
{
	int targetPort;

#ifdef MANAGER
	targetPort = defClientPort;
	listenPort = defServerPort;
#endif
#ifdef AGENT
	targetPort = defServerPort;
	listenPort = defClientPort;
#endif

	targetIpInfo = gcnew IPEndPoint(gcnew IPAddress(gcnew array<Byte>{127,0,0,1}),targetPort);
}

bool TCPInfo::parse(String^ ips,String^ ports,String^ listenPorts)
{
	IPAddress^ ip;
	int port;

	if (IPAddress::TryParse(ips,ip)) {
		targetIpInfo->Address = ip;
		if (int::TryParse(ports,port)) {
			targetIpInfo->Port = port;
			if (int::TryParse(listenPorts,port)) {
				listenPort = port;
				return true;
			}
		}
	}
	return false;
}
