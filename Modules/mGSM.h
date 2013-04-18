#ifndef M_G_S_M_H
#define M_G_S_M_H

#include <string>
#include <assert.h>

#include "Module.h"

using namespace std ;

class mGSM : public Module
{
private:
	bool isPresent;

	bool isUnlocked;

	std::string SMSReceived;

	bool isActivate;


private:
	void sendCommandAT(std::string command, std::string data);

	bool controlPassword();

	void unlockSIM();

public:
	string getSMS();

	void sendSMS(std::string data);

	bool activateModule();

	bool desactivateModule();

};
#endif
