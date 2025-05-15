#include "StdAfx.h"
#include "IPInfo.h"

IPInfo::IPInfo()
{
	target = "http://localhost";
	port = 8080;
}

bool IPInfo::isValidIP()
{
	return (isValidIP(targetString()) && isValidIP(selfString()));
}

bool IPInfo::isValidIP(String^ ip)
{
	Uri^ uri;
	if (!String::IsNullOrEmpty(ip) && Uri::IsWellFormedUriString(ip,UriKind::RelativeOrAbsolute)) {
		if (Uri::TryCreate(ip,UriKind::RelativeOrAbsolute,uri)) {
			return true;
		}
	}
	return false;
}

String^ IPInfo::targetString()
{
	return String::Format("{0}:{1}/",target,port);
}

String^ IPInfo::selfString()
{
	return String::Format("http://localhost:{0}/",port);
}
