#ifndef T_AVAILABILITY_H
#define T_AVAILABILITY_H

#include <string>
#include <assert.h>

#include "tParameters.h"
#include "def.h"

class tAvailability: public tParameters
    {
public:

    union
	{
	UInt8 aDataTab[4];
	struct
	    {
	    UInt16 aIntervalMn;
	    UInt16 aTimeMn;
	    } aDataStruct;
	} aData;

    tAvailability(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    ~tAvailability();

    };
#endif
