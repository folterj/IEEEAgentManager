#include "StdAfx.h"
#include "InvokeHandler.h"


InvokeHandler::InvokeHandler(AMState minimumState0,bool confirmed0)
{
	minimumState = minimumState0;
	confirmed = confirmed0;
	invokeId = -1;
	state = SendState::New;
}
