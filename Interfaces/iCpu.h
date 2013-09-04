#ifndef I_CPU_H
#define I_CPU_H

#include <string>
#include <assert.h>
#include <msp430f5519.h>

typedef enum
    {
    kActiveMode,
    kLPM0,
    kLPM1,
    kLPM2,
    kLPM3,
    kLPM4
    } powerModeEnum;

class iCpu
    {
private:
    static void SetVcoreUp(unsigned int level);

public:
    static void setPowerMode(powerModeEnum aMode);
    static void configFrequency(void);

    };
#endif
