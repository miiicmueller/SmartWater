#ifndef T_ALARM_NUMBER_H
#define T_ALARM_NUMBER_H

#include <string>
#include <assert.h>

#include "tParameters.h"

class tAlarmNumber: public tParameters
    {
public:
    char aTelNumber[15];

    tAlarmNumber(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    ~tAlarmNumber();

    };
#endif
