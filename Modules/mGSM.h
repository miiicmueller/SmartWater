#ifndef M_G_S_M_H
#define M_G_S_M_H

#include <string>
#include <assert.h>

#include "Module.h"

class mGSM : public Module
{
private:
	boolean isPresent;

	boolean isUnlocked;

	string SMSReceived;

	boolean isActivate;


private:
	void sendCommandAT(string command[], string data);

	boolean controlPassword();

	void unlockSIM();

public:
	string getSMS();

	void sendSMS(string data);

	boolean activateModule();

	boolean desactivateModule();

};
#endif
