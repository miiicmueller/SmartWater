#ifndef G_INPUT_H
#define G_INPUT_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "../Tools/tDate.h"
#include "Modules/mCompteur.h"
#include "mGSM.h"
#include "mTempSensor.h"
#include "../Modules/mRTC.h"
#include "mCompteur.h"
#include "Tools/tToolsCluster.h"
#include "tCommandsAnalyzer.h"
#include "mUSB.h"
#include "def.h"

//Structure de valeur des compteurs
typedef struct
    {
    UInt32 value;
    tDate date;
    } gInputMeterValueStruct;

typedef struct
    {
    //SMS
    tCommandsEnum* aAction;
    char* theParameters[12];
    UInt8* theParametersNumber;
    tCommandsUserNbEnum* aUserNb;

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

    mUSB* theUSB;

    tToolsCluster* theTools;

    tCommandsAnalyzer theAnalyzer;

public:
    gInputMailBox theInputMailBox;

    //----------------------------------------------------------------
    //constructeur
    //----------------------------------------------------------------
    gInput(mGSM* theGSM, mCompteur* theCompteurs[2], mRTC* theRTC,
	    mTempSensor* theTempSensor, tToolsCluster* theTools, mUSB* theUSB);

    ~gInput();

    void setup();

    void execute();

    };
#endif
