#ifndef I_WDT_H
#define I_WDT_H

#include <string>
#include <assert.h>
#include <msp430f5519.h>
#include "Interface.h"

class iWDT: public Interface
    {
public:
    iWDT();
    ~iWDT();

    UInt8 read();
    bool write(UInt8 aData);

    void stopWatchDog();
    void startWatchDog();
    void resetWatchDog();

    };
#endif
