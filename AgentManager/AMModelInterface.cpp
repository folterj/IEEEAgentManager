#include "StdAfx.h"
#include "AMModelInterface.h"

void AMModelInterface::registerObserver(AMObserver^ observer)
{
	amObservers.Add(observer);
}

void AMModelInterface::unregisterObserver(AMObserver^ observer)
{
	amObservers.Remove(observer);
}
