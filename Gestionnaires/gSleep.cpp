#include <string>
#include <assert.h>

#include "gSleep.h"
#include "Modules/mCpu.h"
#include "Modules/mRTC.h"
#include "Modules/mGSM.h"
#include "Modules/mCompteur.h"
#include "Modules/mTempSensor.h"

gSleep::gSleep(tToolsCluster* aToolCluster, mRTC* amRTC, mGSM* aGsm,
	mCompteur* aCompteur, mTempSensor* amTempSensor)
    {

    char aHour = 0, aMinutes = 0, aSec = 0, aRes = 0;

    this->atAvailability = aToolCluster->theAvailability;
    this->amRTC = amRTC;
    this->aGsm = aGsm;
    this->aCompteur = aCompteur;
    this->amTempSensor = amTempSensor;

    //On initialise les ancienne valeur
    this->aHourOld = 0;
    this->aMinOld = 0;
    this->aSecOld = 0;

    //Récupération de l'heure
    amRTC->readTime(&aHour, &aMinutes, &aSec);

    //On calcul on on se retrouve dans les portion horaire
    aRes = (aMinutes + aHour * 60) / this->atAvailability->aIntervalMn; // si on désire toute les 10 min, et que aMinutes = 15 => aRes = 1 . On est dans la deuxième tranche, la première étant 0
    this->aMinOld = aRes * this->atAvailability->aIntervalMn;
    }

void gSleep::setup()
    {

    }

void gSleep::execute()
    {
    char aHour = 0, aMinutes = 0, aSec = 0;
    int aMinutesCalc = 0;

    //Récupération de l'heure
    amRTC->readTime(&aHour, &aMinutes, &aSec);
    aMinutesCalc = (aHour * 60) + aMinutes;

    //Comparaison avec les ancienne valeure

    //Ici on dort
    if (aMinutesCalc >= this->aMinOld + this->atAvailability->aTimeMn) // Suivant l'exemple si aMinutes = 15 et aMinold = 10 et aTime = 5 , on passe
	{
	//Setter l'alarme
	this->amRTC->setAlarm(
		((this->aMinOld + this->atAvailability->aIntervalMn) / 60),
		(this->aMinOld + this->atAvailability->aIntervalMn % 60));
	this->aMinOld += this->atAvailability->aIntervalMn;

	//Arret de tout les autres composants
	this->aGsm->mClose();
	this->aCompteur->mClose();
	this->amTempSensor->mClose();

	//On endort le porcesseur
	mCpu::setPowerMode(kLPM3);

	//Lors du réveil on sera là
	this->aGsm->mOpen();
	this->aCompteur->mOpen();
	this->amTempSensor->mOpen();

	}
    //Sinon on continue
    else
	{

	}

    }
