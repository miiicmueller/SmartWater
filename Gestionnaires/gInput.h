#ifndef G_INPUT_H
#define G_INPUT_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "mGSM.h"
#include "mTempSensor.h"
#include "mRTC.h"
#include "mCompteur.h"

//Structure de valeur des compteurs
typedef struct
    {
    UInt32 value;
    tDate date;
    } gInputMeterValueStruct;

typedef struct
    {
    //SMS
    bool hasSMS;
    char theSMS[200];

    //compteurs
    gInputMeterValueStruct valueMeters[2];

    //capteurs de temperature
    UInt16 temperature;
    } gInputMailBox;

class gInput: public Gestionnaire
    {
private:
    mTempSensor* theTempSensor;

    mCompteur* theCompteurs[2];

    mRTC* theRTC;

    mGSM* theGSM;

public:
    gInputMailBox theInputMailBox;

    //----------------------------------------------------------------
    //constructeur
    //----------------------------------------------------------------
    gInput(mGSM* theGSM, mCompteur* theCompteurs[2], mRTC* theRTC,
	    mTempSensor* theTempSensor);

    ~gInput();

    void setup();

    void execute();

    };
#endif
