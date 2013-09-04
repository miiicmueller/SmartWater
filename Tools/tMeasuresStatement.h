#ifndef T_MEASURES_STATEMENT_H
#define T_MEASURES_STATEMENT_H

#include <string>
#include <assert.h>
#include "Def/def.h"
#include "tParameters.h"
#include "Modules/mEEPROM.h"

class tMeasuresStatement: public tParameters
    {

public:
    UInt16 MonthlyConsumption[12];
    UInt16 CurrentMonthConsumption[31];

    tMeasuresStatement(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();
    ~tMeasuresStatement();
    };
#endif
