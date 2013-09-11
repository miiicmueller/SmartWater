#include <string>
#include <assert.h>

#include "gSleep.h"
#include "Modules/mCpu.h"
#include "Modules/mRTC.h"
#include "Modules/mGSM.h"
#include "Modules/mCompteur.h"
#include "Modules/mTempSensor.h"
#include "Interfaces/iDIO.h"
#include "gCompute.h"
#include "Modules/mWDT.h"

iDIO gSleep::wakeUp((char*) kPort_2, BIT1);
iDIO gSleep::ledWakeUp((char*) kPort_2, BIT0);
volatile bool gSleep::aCanSleep = true;
mDelay *gSleep::aCanSleepDelay;

gSleep::gSleep(tToolsCluster* aToolCluster, mRTC* amRTC, mGSM* aGsm,
	mCompteur* aCompteur, mTempSensor* amTempSensor, gCompute* aGCompute,
	mWDT* aWatchDog)
    {

    char aHour = 0, aMinutes = 0, aSec = 0, aRes = 0;

    this->atAvailability = aToolCluster->theAvailability;
    this->atMode = aToolCluster->theMode;
    this->amRTC = amRTC;
    this->aGsm = aGsm;
    this->aCompteur = aCompteur;
    this->amTempSensor = amTempSensor;
    this->aGCompute = aGCompute;
    this->aWatchDog = aWatchDog;
    gSleep::aCanSleepDelay = new mDelay();

    //On initialise les ancienne valeur
    this->aHourOld = 0;
    this->aMinOld = 0;
    this->aSecOld = 0;

    //Recuperation de l'heure
    amRTC->readTime(&aHour, &aMinutes, &aSec);

    //On calcul on on se retrouve dans les portions horaire
    aRes = (aMinutes + aHour * 60)
	    / this->atAvailability->aData.aDataStruct.aIntervalMn; // si on desire toute les 10 min, et que aMinutes = 15 => aRes = 1 . On est dans la deuxieme tranche, la premiere etant 0
    this->aMinOld = aRes * this->atAvailability->aData.aDataStruct.aIntervalMn;
    }

void gSleep::setup()
    {
    //Configuration du bouton de réveil
    gSleep::wakeUp.SetPortDirection(kInput);
    gSleep::wakeUp.write(~BIT1);
    gSleep::wakeUp.SetPortResistorEnable(kResistorEnable);

    //Configuration de la led de sortie
    gSleep::ledWakeUp.SetPortDirection(kOutput);
    gSleep::ledWakeUp.SetPortDriveStrength(kFullStrength);
    gSleep::ledWakeUp.write(~BIT0);

    //Config de l'interruption
    P2IES &= ~BIT1;
    P2IE |= BIT1;

    }

void gSleep::execute()
    {
    char aHour = 0, aMinutes = 0, aSec = 0;
    int aMinutesCalc = 0, aRes = 0;

    //Recuperation de l'heure
    amRTC->readTime(&aHour, &aMinutes, &aSec);
    aMinutesCalc = (aHour * 60) + aMinutes;

    // Recalcul si la valeur aurait changée
    aRes = aMinutesCalc / this->atAvailability->aData.aDataStruct.aIntervalMn; // si on desire toute les 10 min, et que aMinutes = 15 => aRes = 1 . On est dans la deuxieme tranche, la premiere etant 0
    this->aMinOld = aRes * this->atAvailability->aData.aDataStruct.aIntervalMn;

    if ((gSleep::aCanSleepDelay->isDone()) && (!gSleep::aCanSleep))
	{
	gSleep::aCanSleep = true;
	//On éteint la led
	gSleep::ledWakeUp.write(~BIT0);
	}

    //Comparaison avec les ancienne valeurs
    //Ici on dort
    if ((aMinutesCalc
	    >= (this->aMinOld + this->atAvailability->aData.aDataStruct.aTimeMn))
	    && (this->aGCompute->theComputeMailBox.isWorkFinished)
	    && gSleep::aCanSleep && this->atMode->mode == 'S') // Suivant l'exemple si aMinutes = 15 et aMinold = 10 et aTime = 5 , on passe
	{
	//Setter l'alarme
	this->amRTC->setAlarm(
		((this->aMinOld
			+ this->atAvailability->aData.aDataStruct.aIntervalMn)
			/ 60),
		(this->aMinOld
			+ this->atAvailability->aData.aDataStruct.aIntervalMn
				% 60));
	this->aMinOld += this->atAvailability->aData.aDataStruct.aIntervalMn;

	//Arret de tout les autres composants
	this->aGsm->mClose();
	this->aCompteur->mClose();
	this->amTempSensor->mClose();

	//Arret du watchdog
	this->aWatchDog->stopWatchDog();

	//On endort le processeur
	mCpu::setPowerMode(kLPM3);

	//démmarage du watchdog
	this->aWatchDog->startWatchDog();

	//Lors du reveil on sera la�
	this->aGsm->mOpen();
	this->aCompteur->mOpen();
	this->amTempSensor->mOpen();

	}
    //Sinon on continue
    else
	{

	}
    }

gSleep::~gSleep()
    {
    }

// USCIA1 Interrupt handler
#pragma vector=PORT2_VECTOR
__interrupt void WakeUpBtn(void)
    {
//Verifiation que c'est bien un interruption en reception
    if ((P2IFG & BIT1)== BIT1)
	{
	//On réveil le processeur
	mCpu::setPowerMode(kActiveMode);

	gSleep::aCanSleep = false;
	//On ne permet pas de dormir pour 2 minutes
	gSleep::aCanSleepDelay->startDelayMS(120000);

	//On allume la led 1 seconde
	gSleep::ledWakeUp.write(BIT0);

	P2IFG &= ~BIT1;
	}
    }

