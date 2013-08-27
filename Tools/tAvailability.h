#ifndef T_AVAILABILITY_H
#define T_AVAILABILITY_H

#include <string>
#include <assert.h>

#include "tParameters.h"

class tAvailability : public tParameters
{
public:
	UInt16 aIntervalMn;
	UInt16 aTimeMn;

	tAvailability(mEEPROM *mEeprom,UInt16 aModeNum);
	void save();
	void load();


};
#endif
