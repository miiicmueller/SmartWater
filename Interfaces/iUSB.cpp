#include <string>
#include <assert.h>

#include "iUSB.h"


bool iUSB::getFullFrame(char* FrameBuffer)
{
	return false;
}

void iUSB::sendFullFrame(char* FrameBuffer)
{
}

kStatusEnum iUSB::getStatus()
{
	return kActive ;
}

void iUSB::initUSB()
{
}

char iUSB::getConnectionState()
{
	return 0;
}
