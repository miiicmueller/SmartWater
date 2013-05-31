#ifndef I_CPU_H
#define I_CPU_H

#include <string>
#include <assert.h>

#include "Interface.h"

typedef enum
    {
    kSMCLK,
    kMCLK,
    kACLK
    } lineFreqEnum;

class iCpu: public Interface
    {
private:
    long smclk_freq;
    long mclk_freq;
    long aclk_freq;

public:
    iCpu();

    void setPowerMode(char aMode);
    void setFrequency(int aDivider);
    long getFrequency(lineFreqEnum aLineFreq);
    kStatusEnum getStatus();

    };
#endif
