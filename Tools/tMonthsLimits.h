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
    UInt16 limits[12];
    tMonthsLimits(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    ~tMonthsLimits();

    };
#endif
