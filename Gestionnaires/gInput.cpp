#include <string>
#include <assert.h>

#include "gInput.h"


int gInput::getCounterValue(char counterNb)
{
	return 0;
}

int gInput::getBatteryValue()
{
	return 0;
}

int gInput::getTempSensValue(char tempSensNb)
{
	return 0;
}

std::string gInput::getSms(int nSms)
{
	return "";
}

int gInput::getSmsNb()
{
	return 0;
}

tDate* gInput::getCurrentTime()
{
	return new tDate();
}
