#include <string>
#include <assert.h>
#include <msp430f5519.h>
#include "Def/def.h"
#include "iWDT.h"

iWDT::iWDT()
    {
    this->stopWatchDog();
    }

iWDT::~iWDT()
    {

    }

void iWDT::startWatchDog()
    {
    // Watchdog mode -> reset after expired time; WDT is clocked by ACLK
    WDTCTL = WDT_ARST_4M_16S;
    }

void iWDT::stopWatchDog()
    {
    // turn watchdog off
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    }

void iWDT::resetWatchDog()
    {
    this->startWatchDog();
    }

UInt8 iWDT::read()
    {
    return 0;
    }

bool iWDT::write(UInt8 aData)
    {
    return false;
    }
