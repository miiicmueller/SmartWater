#ifndef M_CPU_H
#define M_CPU_H

#include <assert.h>
#include "iCpu.h"

class mCpu
    {
public:
    static void setPowerMode(powerModeEnum aMode);
    static void configFrequency();
    };
#endif
