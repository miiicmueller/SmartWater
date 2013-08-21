#ifndef T_AVAILABILITY_H
#define T_AVAILABILITY_H

#include <string>
#include <assert.h>

#include "tParameters.h"

class tAvailability : public tParameters
{
public:
	UInt16 aInterval;
	UInt16 aTime;

	tAvailability(mEEPROM *mEeprom,UInt16 aModeNum);
	void save();
	void load();


};
#endif
