#include <assert.h>

#include "mCpu.h"
#include "../Interfaces/iCpu.h"

void mCpu::setPowerMode(powerModeEnum aMode)
    {
    iCpu::setPowerMode(aMode);
    }

void mCpu::configFrequency()
    {
    iCpu::configFrequency();
    }
