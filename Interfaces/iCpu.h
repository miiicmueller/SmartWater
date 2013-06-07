#ifndef I_CPU_H
#define I_CPU_H

#include <string>
#include <assert.h>

typedef enum
    {
    kSMCLK,
    kMCLK,
    kACLK
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
