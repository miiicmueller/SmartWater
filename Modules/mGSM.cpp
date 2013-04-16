#include <string>
#include <assert.h>

#include "mGSM.h"


std::string mGSM::getSMS()
{
	return "";
}

void mGSM::sendSMS(std::string data)
{
}

bool mGSM::activateModule()
{
	return 0;
}

bool mGSM::desactivateModule()
{
	return false;
}

void mGSM::sendCommandAT(std::string command, std::string data)
{
}

bool mGSM::controlPassword()
{
	return false;
}

void mGSM::unlockSIM()
{
}
