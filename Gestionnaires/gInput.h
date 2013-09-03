#ifndef G_INPUT_H
#define G_INPUT_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "mGSM.h"

//Structure de valeur des compteurs
typedef struct
    {
    UInt32 value;
    tDate date;
    } gInputMeterValueStruct;

class gInput: public Gestionnaire
    {
private:
    gInputMeterValueStruct valueMeters[2];

    char* smsTab;

    UInt8 smsNb;

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
