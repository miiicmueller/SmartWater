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

class gSleep: public Gestionnaire
    {
public:
    gSleep(tToolsCluster* aToolCluster, mRTC* amRTC, mGSM* aGsm,
	    mCompteur* aCompteur, mTempSensor* amTempSensor,
	    gCompute* aGCompute);
    void setup();
    void execute();

    ~gSleep();

private:
    tAvailability* atAvailability;
    mRTC* amRTC;
    mGSM* aGsm;
    mCompteur* aCompteur;
    mTempSensor* amTempSensor;
    gCompute* aGCompute;

    char aHourOld;
    char aMinOld;
    char aSecOld;

    };
#endif
