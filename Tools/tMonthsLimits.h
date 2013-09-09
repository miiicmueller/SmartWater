#ifndef T_MONTHS_LIMITS_H
#define T_MONTHS_LIMITS_H

#include <string>
#include <assert.h>
#include "Def/def.h"
#include "tParameters.h"
#include "Modules/mEEPROM.h"

class tMonthsLimits: public tParameters
    {
public:
    union
	{
	UInt8 aDataTab[24];
	struct
	    {
	    UInt16 limits[12];
	    } aDataStruct;
	} aData;
    tMonthsLimits(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    ~tMonthsLimits();

    };
#endif
