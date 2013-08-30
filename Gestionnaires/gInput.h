#ifndef G_INPUT_H
#define G_INPUT_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "mGSM.h"

class gInput: public Gestionnaire
    {
private:
    int counterValues;

    int batteryValue;

    int tempSensValues;

    char* smsTab;

    int smsNb;

    tDate currentTime;

    mGSM* theGSM;

public:
    //----------------------------------------------------------------
    //constructeur
    //----------------------------------------------------------------
    gInput(mGSM* theGSM);

    ~gInput();

    int getCounterValue(char counterNb);

    int getBatteryValue();

    int getTempSensValue(char tempSensNb);

    char* getSms(int nSms);

    int getSmsNb();

    tDate getCurrentTime();

    void setup();

    void execute();

    };
#endif
