#ifndef T_TEMPERATURE_OFFSET_H
#define T_TEMPERATURE_OFFSET_H

#include <string>
#include <assert.h>

#include "tParameters.h"
#include "def.h"

class tTemperatureOffset: public tParameters
    {
public:
    Float32 aOffset;

    tTemperatureOffset(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    ~tTemperatureOffset();

    };
#endif
