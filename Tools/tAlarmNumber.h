#ifndef T_ALARM_NUMBER_H
#define T_ALARM_NUMBER_H

#include <string>
#include <assert.h>

#include "tParameters.h"

class tAlarmNumber : public tParameters
{
public:
	UInt8 aTelNumber[15];

	tAlarmNumber(mEEPROM *mEeprom,UInt16 aModeNum);
	void save();
	void load();

};
#endif
