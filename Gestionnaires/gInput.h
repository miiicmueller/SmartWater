#ifndef G_INPUT_H
#define G_INPUT_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"

class gInput : public Gestionnaire
{
private:
	int counterValues;

	int batteryValue;

	int tempSensValues;

	std::string smsTab;

	int smsNb;

	tDate* currentTime;


public:
	int getCounterValue(char counterNb);

	int getBatteryValue();

	int getTempSensValue(char tempSensNb);

	std::string getSms(int nSms);

	int getSmsNb();

	tDate* getCurrentTime();

};
#endif
