#include <string>
#include <assert.h>

#include "mWDT.h"

mWDT::mWDT()
    {
    this->aIWdt.stopWatchDog();
    }

mWDT::~mWDT()
    {

    }

void mWDT::mOpen()
    {
    return;
    }

void mWDT::mSetup()
    {
    return;
    }

void mWDT::mClose()
    {
    return;
    }

void mWDT::startWatchDog()
    {
    this->aIWdt.startWatchDog();
    }

void mWDT::stopWatchDog()
    {
    this->aIWdt.stopWatchDog();
    }

void mWDT::resetWatchDog()
    {
    this->aIWdt.resetWatchDog();
    }
