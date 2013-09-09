/*
 * gError.h
 *
 *  Created on: 6 sept. 2013
 *      Author: cyrille.savy
 */

#ifndef GERROR_H_
#define GERROR_H_

#include "Gestionnaire.h"
#include "mGSM.h"
#include "mTempSensor.h"
#include "mEEPROM.h"
#include "mDelay.h"

#define kGErrorNbErrors	5

typedef enum
    {
    kGErrorGSM = 0,
    kGErrorEEPROM = 1,
    kGErrorTempSensor = 2,
    kGErrorCompteur = 3,
    kGErrorAlim = 4
    } gErrorEnum;

class gError: public Gestionnaire
    {
public:
    bool gErrorList[kGErrorNbErrors];
//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entrees
//----------------------------------------------------------------
    gError(mGSM* theGSM, mTempSensor* theTempSensor, mEEPROM* theEEPROM);

    void setup();

    void execute();

    ~gError();

private:
    mGSM* theGSM;

    mTempSensor* theTempSensor;

    mEEPROM* theEEPROM;

    mDelay aDelay;
    };

#endif /* GERROR_H_ */
