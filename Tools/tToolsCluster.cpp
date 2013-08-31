/*
 * tToolsCluster.cpp
 *
 *  Created on: 30 août 2013
 *      Author: cyrille.savy
 */

#include "tToolsCluster.h"
#include "stdio.h"

using namespace std;

tToolsCluster::tToolsCluster(mEEPROM* aEEPROM)
    {
    //parametres utilisateur
    for (int i = 0; i < 2; i++)
	{
	this->theAlarmNumber[i] = new tAlarmNumber(aEEPROM, i);
	sprintf(this->theAlarmNumber[i]->aTelNumber, "");
	this->theAlarmNumber[i]->save();

	this->theMdPUser[i] = new tMdPUser(aEEPROM, i);
	sprintf(this->theMdPUser[i]->mdPUser, "PassUser%d", (i + 1));
	this->theMdPUser[i]->save();

	this->theMeasuresStatement[i] = new tMeasuresStatement(aEEPROM, i);
	for (int j = 0; j < 12; j++)
	    {
	    this->theMeasuresStatement[i]->MonthlyConsumption[j] = 0;
	    }
	for (int j = 0; j < 31; j++)
	    {
	    this->theMeasuresStatement[i]->CurrentMonthConsumption[j] = 0;
	    }
	this->theMeasuresStatement[i]->save();

	this->theMonthsLimits[i] = new tMonthsLimits(aEEPROM, i);
	for (int j = 0; j < 12; j++)
	    {
	    this->theMonthsLimits[i]->limits[j] = 999;
	    }
	this->theMonthsLimits[i]->save();

	this->theCompteur[i] = new tCompteur(aEEPROM, i);
	this->theCompteur[i]->aFabDate[0] = '\0';
	this->theCompteur[i]->aFluide[0] = '\0';
	this->theCompteur[i]->aManufacturer[0] = '\0';
	this->theCompteur[i]->aNominalSize[0] = '\0';
	this->theCompteur[i]->aSerialNum[0] = '\0';
	this->theCompteur[i]->aVersNum[0] = '\0';
	this->theCompteur[i]->save();
	}

    //parametres administrateur
    this->theAvailability = new tAvailability(aEEPROM, 1);
    this->theAvailability->aIntervalMn = 60;
    this->theAvailability->aTimeMn = 15;
    this->theAvailability->save();

    this->theMdPAdmin = new tMdPAdmin(aEEPROM, 1);
    sprintf(this->theMdPAdmin->mdPAdmin, "PassAdmin");
    this->theMdPAdmin->save();

    this->theMode = new tMode(aEEPROM, 1);
    this->theMode->mode = 'S';
    this->theMode->save();

    this->theTemperatureOffset = new tTemperatureOffset(aEEPROM, 1);
    this->theTemperatureOffset->aOffset.aFloatVal = 0;
    this->theTemperatureOffset->save();

    this->theUnitName = new tUnitName(aEEPROM, 1);
    sprintf(this->theUnitName->aName, "Unit1");
    this->theUnitName->save();

    this->theSIMCard = new tSIMCard(aEEPROM, 1);
    sprintf(this->theSIMCard->theOwnNumber, "+41000000000");
    sprintf(this->theSIMCard->thePINCode, "0000");
    this->theSIMCard->save();
    }

tToolsCluster::~tToolsCluster()
    {
    }

