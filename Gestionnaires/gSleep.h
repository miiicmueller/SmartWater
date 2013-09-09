#ifndef G_SLEEP_H
#define G_SLEEP_H

#include <string>
#include <assert.h>

#include "Gestionnaire.h"
#include "Tools/tToolsCluster.h"
#include "Modules/mRTC.h"
#include "Modules/mGSM.h"
#include "Modules/mCompteur.h"
#include "Modules/mTempSensor.h"
#include "Tools/tAvailability.h"
#include "gCompute.h"
#include "Modules/mWDT.h"

class gSleep: public Gestionnaire
    {
public:
    gSleep(tToolsCluster* aToolCluster, mRTC* amRTC, mGSM* aGsm,
	    mCompteur* aCompteur, mTempSensor* amTempSensor,
	    gCompute* aGCompute, mWDT* aWatchDog);
    void setup();
    void execute();

    ~gSleep();

private:
    mWDT* aWatchDog;
    tAvailability* atAvailability;
    mRTC* amRTC;
    mGSM* aGsm;
    mCompteur* aCompteur;
    mTempSensor* amTempSensor;
    gCompute* aGCompute;
    static iDIO wakeUp;
    static iDIO ledWakeUp;


    //Interruptions handlers
    friend void WakeUpBtn(void);

    char aHourOld;
    char aMinOld;
    char aSecOld;
    static bool aCanSleep ;
    static mDelay aCanSleepDelay ;

    };
#endif
