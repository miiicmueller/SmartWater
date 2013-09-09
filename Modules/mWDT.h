#ifndef M_WDT_H
#define M_WDT_H

#include <string>
#include <assert.h>
#include <msp430f5519.h>
#include "Interfaces/iWDT.h"
#include "Module.h"

class mWDT: public Module
    {
private :
    iWDT aIWdt;
public:
    mWDT();
    ~mWDT();

    void mOpen();
    void mSetup();
    void mClose();

    void stopWatchDog();
    void startWatchDog();
    void resetWatchDog();

    };
#endif
