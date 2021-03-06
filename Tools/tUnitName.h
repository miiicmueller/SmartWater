#ifndef T_UNIT_NAME_H
#define T_UNIT_NAME_H

#include <string>
#include <assert.h>

#include "tParameters.h"

class tUnitName: public tParameters
    {
public:
    char aName[20];

    tUnitName(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    ~tUnitName();
    };
#endif
