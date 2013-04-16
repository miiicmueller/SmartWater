#include <string>
#include <assert.h>
#include <msp430.h>

#include "iUART.h"

iUART::iUART(UARTPortEnum aPort)
{
	this->serialPort = aPort ;
}

void iUART::config(int kPort)
{
}
