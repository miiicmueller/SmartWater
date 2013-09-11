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
#include "tCompteur.h"
#include "gError.h"

typedef struct
    {
    //SMS
    tCommandsEnum* aAction;
    char* theParameters[12];
    UInt8* theParametersNumber;
    tCommandsUserNbEnum* aUserNb;
    char aReplyNb[15];

    //la date d'execution
    tDate* date;

    //capteurs de temperature
    Float32 temperature;

    //credit
    UInt16 theCredit;

    //pour la simulation
    bool isSimulation;
    UInt32 indexOverrunSimulation; // index qu'il faut pour simuler un depassement de consommation
    bool simulateCompteur;
    } gInputMailBox;

class gInput: public Gestionnaire
    {
private:
    mTempSensor* theTempSensor;

    mCompteur* theCompteurs[3];

    mRTC* theRTC;

    mGSM* theGSM;

    mUSB* theUSB;

    gError* theGError;

    tToolsCluster* theTools;

    tCommandsAnalyzer theAnalyzer;

public:
    gInputMailBox theInputMailBox;

    //----------------------------------------------------------------
    //constructeur
    //----------------------------------------------------------------
    gInput(mGSM* theGSM, mCompteur* theCompteurs[3], mRTC* theRTC,
	    mTempSensor* theTempSensor, tToolsCluster* theTools, mUSB* theUSB,
	    gError* theGError);

    ~gInput();

    void setup();

    void execute();

    };
#endif
