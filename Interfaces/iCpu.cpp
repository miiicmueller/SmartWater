#include <string>
#include <assert.h>
#include <msp430.h>

#include "iCpu.h"

iCpu::iCpu()
    {
    // Configuration des IOs
    P5SEL |= (0x04 | 0x08); // Selection du mode XT2

    }

void iCpu::setPowerMode(char aMode)
    {
    }

void iCpu::setFrequency(int aDivider)
    {
    }

kStatusEnum iCpu::getStatus()
    {

    }
