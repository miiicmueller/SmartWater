#ifndef I_CPU_H
#define I_CPU_H

#include <string>
#include <assert.h>

#include "Interface.h"

#define XT2_FREQ 4000000 // Frequence premier quartz
#define XT1_FREQ 32768 // Frequence low quartz
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
