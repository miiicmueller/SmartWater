#include <string>
#include <assert.h>

#include "gInput.h"

gInput::gInput(mGSM* theGSM)
    {
    this->smsTab = NULL;
    this->theGSM = theGSM;
    }

void gInput::setup()
    {
    }

void gInput::execute()
    {
    }

int gInput::getCounterValue(char counterNb)
    {
    //return this->counterValues;
    }

int gInput::getBatteryValue()
    {
    //return this->tempSensValues;
    }

int gInput::getTempSensValue(char tempSensNb)
    {
    //return this->tempSensValues;
    }

char* gInput::getSms(int nSms)
    {
    return this->smsTab;
    }

int gInput::getSmsNb()
    {
    return this->smsNb;
    }

tDate gInput::getCurrentTime()
    {
    return this->currentTime;
    }

