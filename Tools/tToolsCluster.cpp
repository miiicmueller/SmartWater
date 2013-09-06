/*
 * tToolsCluster.cpp
 *
 *  Created on: 30 août 2013
 *      Author: cyrille.savy
 */

#include "tToolsCluster.h"
#include "stdio.h"
#include "string.h"

using namespace std;

// contructeur
tToolsCluster::tToolsCluster(mEEPROM* aEEPROM)
    {
    //parametres utilisateur
    for (int i = 0; i < 2; i++)
	{
	this->theAlarmNumber[i] = new tAlarmNumber(aEEPROM, i);

	this->theMdPUser[i] = new tMdPUser(aEEPROM, i);

	this->theMeasuresStatement[i] = new tMeasuresStatement(aEEPROM, i);

	this->theMonthsLimits[i] = new tMonthsLimits(aEEPROM, i);

	this->theCompteur[i] = new tCompteur(aEEPROM, i);
	}

    //le compteur de simulation
    this->theCompteur[2] = new tCompteur(aEEPROM, 2);

    //parametres administrateur
    this->theAvailability = new tAvailability(aEEPROM, 1);

    this->theMdPAdmin = new tMdPAdmin(aEEPROM, 1);

    this->theMode = new tMode(aEEPROM, 1);

    this->theTemperatureOffset = new tTemperatureOffset(aEEPROM, 1);

    this->theUnitName = new tUnitName(aEEPROM, 1);

    this->theSIMCard = new tSIMCard(aEEPROM, 1);
    }

//methodes
void tToolsCluster::reset()
    {
    //parametres utilisateur
    for (int i = 0; i < 2; i++)
	{
	sprintf(this->theAlarmNumber[i]->aTelNumber, "");

	sprintf(this->theMdPUser[i]->mdPUser, "PassUser%d", (i + 1));

	for (int j = 0; j < 12; j++)
	    {
	    this->theMeasuresStatement[i]->MonthlyConsumption[j] = 0;
	    }
	for (int j = 0; j < 31; j++)
	    {
	    this->theMeasuresStatement[i]->CurrentMonthConsumption[j] = 0;
	    }

	for (int j = 0; j < 12; j++)
	    {
	    this->theMonthsLimits[i]->limits[j] = 999;
	    }

	this->theCompteur[i]->aFabDate[0] = '\0';
	this->theCompteur[i]->aFluide[0] = '\0';
	this->theCompteur[i]->aManufacturer[0] = '\0';
	this->theCompteur[i]->aNominalSize[0] = '\0';
	this->theCompteur[i]->aSerialNum[0] = '\0';
	this->theCompteur[i]->aVersNum[0] = '\0';
	this->theCompteur[i]->aIndex = 0;
	this->theCompteur[i]->isConnected = false;
	}

    //le compteur de simulation
    this->theCompteur[2]->aFabDate[0] = '\0';
    this->theCompteur[2]->aFluide[0] = '\0';
    this->theCompteur[2]->aManufacturer[0] = '\0';
    this->theCompteur[2]->aNominalSize[0] = '\0';
    this->theCompteur[2]->aSerialNum[0] = '\0';
    this->theCompteur[2]->aVersNum[0] = '\0';
    this->theCompteur[2]->aIndex = 0;
    this->theCompteur[2]->isConnected = false;

    //parametres administrateur
    this->theAvailability->aIntervalMn = 60;
    this->theAvailability->aTimeMn = 15;

    sprintf(this->theMdPAdmin->mdPAdmin, "PassAdmin");

    this->theMode->mode = 'S';

    this->theTemperatureOffset->aOffset.aFloatVal = 0;

    sprintf(this->theUnitName->aName, "Unit1");

    sprintf(this->theSIMCard->theOwnNumber, "+41000000000");
    sprintf(this->theSIMCard->thePINCode, "0000");
    }

void tToolsCluster::saveAll()
    {
    //parametres utilisateur
    for (int i = 0; i < 2; i++)
	{
	this->theAlarmNumber[i]->save();

	this->theMdPUser[i]->save();

	this->theMeasuresStatement[i]->save();

	this->theMonthsLimits[i]->save();

	this->theCompteur[i]->save();
	}

    //le compteur de simulation
    this->theCompteur[2]->save();

    //parametres administrateur
    this->theAvailability->save();

    this->theMdPAdmin->save();

    this->theMode->save();

    this->theTemperatureOffset->save();

    this->theUnitName->save();

    this->theSIMCard->save();
    }

void tToolsCluster::loadAll()
    {
    //parametres utilisateur
    for (int i = 0; i < 2; i++)
	{
	this->theAlarmNumber[i]->load();

	this->theMdPUser[i]->load();

	this->theMeasuresStatement[i]->load();

	this->theMonthsLimits[i]->load();

	this->theCompteur[i]->load();
	}

    //le compteur de simulation
    this->theCompteur[2]->load();

    //parametres administrateur
    this->theAvailability->load();

    this->theMdPAdmin->load();

    this->theMode->load();

    this->theTemperatureOffset->load();

    this->theUnitName->load();

    this->theSIMCard->load();
    }

//setters
bool tToolsCluster::setAvailability(char* aPeriode, char* aDuree)
    {
    UInt16 aHourPeriod, aMinPeriod, aHourDuty, aMinDuty;
    bool isSuccessful = false;

    if ((sscanf(aPeriode, "%d:%d", &aHourPeriod, &aMinPeriod) == 2)
	    && (sscanf(aDuree, "%d:%d", &aHourDuty, &aMinDuty) == 2))
	{
	aMinPeriod += (60 * aHourPeriod);
	aMinDuty += (60 * aHourDuty);

	if ((aMinPeriod >= MinPeriode) && (aMinPeriod <= MaxPeriode)
		&& (aMinDuty >= MinDuree) && (aMinDuty <= MaxDuree))
	    {
	    isSuccessful = true;
	    this->theAvailability->aIntervalMn = aMinPeriod;
	    this->theAvailability->aTimeMn = aMinDuty;
	    this->theAvailability->save();
	    }
	}
    return isSuccessful;
    }

bool tToolsCluster::setMdPAdmin(char* aMdP1, char* aMdP2)
    {
    bool isSuccessful = false;

    if (strcmp(aMdP1, aMdP2) == 0)
	{
	isSuccessful = true;
	strcpy(this->theMdPAdmin->mdPAdmin, aMdP1);
	this->theMdPAdmin->save();
	}
    return isSuccessful;
    }

bool tToolsCluster::setMode(char* aMode)
    {
    bool isSuccessful = false;

    if ((strcmp(aMode, "E") == 0) || (strcmp(aMode, "S") == 0))
	{
	isSuccessful = true;
	this->theMode->mode = aMode[0];
	this->theMode->save();
	}
    return isSuccessful;
    }

bool tToolsCluster::setTemperatureOffset(char* aTemperatureOffset)
    {
    UInt8 aOffsetUnit;
    UInt8 aOffsetDecimal;
    bool isSuccessful = false;

    if (sscanf(aTemperatureOffset, "%d.%d", &aOffsetUnit, &aOffsetDecimal) == 2)
	{
	isSuccessful = true;
	this->theTemperatureOffset->aOffset.aFloatVal = aOffsetUnit
		+ (0.1 * aOffsetDecimal);
	this->theTemperatureOffset->save();
	}
    return isSuccessful;
    }

bool tToolsCluster::setUnitName(char* aUnitName)
    {
    strcpy(this->theUnitName->aName, aUnitName);
    this->theUnitName->save();

    return true;
    }

bool tToolsCluster::setPINCode(char* aPINCode)
    {
    bool isSuccessful = false;

    if (strlen(aPINCode) == 4)
	{
	isSuccessful = true;
	strcpy(this->theSIMCard->thePINCode, aPINCode);
	this->theSIMCard->save();
	}
    return isSuccessful;
    }

bool tToolsCluster::setOwnNumber(char* aOwnNumber)
    {
    bool isSuccessful = false;

    if (aOwnNumber[0] == '+')
	{
	isSuccessful = true;
	for (int i = 1; (isSuccessful == true) && (aOwnNumber[i] != '\0'); i++)
	    {
	    if ((i > 11) || (aOwnNumber[i] < 30) || (aOwnNumber[i] < 39))
		{
		isSuccessful = false;
		}
	    }

	if (isSuccessful == true)
	    {
	    strcpy(this->theSIMCard->theOwnNumber, aOwnNumber);
	    this->theSIMCard->save();
	    }
	}
    return isSuccessful;
    }

bool tToolsCluster::setAlarmNumber(char* aAlarmNumber, UInt8 aUserNb)
    {
    bool isSuccessful = false;

    if (aAlarmNumber[0] == '+')
	{
	isSuccessful = true;
	for (int i = 1; (isSuccessful == true) && (aAlarmNumber[i] != '\0');
		i++)
	    {
	    if ((i > 11) || (aAlarmNumber[i] < 30) || (aAlarmNumber[i] < 39))
		{
		isSuccessful = false;
		}
	    }

	if (isSuccessful == true)
	    {
	    strcpy(this->theAlarmNumber[aUserNb - 1]->aTelNumber, aAlarmNumber);
	    this->theAlarmNumber[aUserNb - 1]->save();
	    }
	}
    return isSuccessful;
    }

bool tToolsCluster::setMdPUser(char* aMdP1, char* aMdP2, UInt8 aUserNb)
    {
    bool isSuccessful = false;

    if (strcmp(aMdP1, aMdP2) == 0)
	{
	isSuccessful = true;
	strcpy(this->theMdPUser[aUserNb - 1]->mdPUser, aMdP1);
	this->theMdPUser[aUserNb - 1]->save();
	}
    return isSuccessful;
    }

bool tToolsCluster::setMonthsLimits(char** aMonthLimits, UInt8 aNbOfLimits,
	UInt8 aUserNb)
    {
    UInt16 theMonths[12], theLimits[12];
    bool isSuccessful = true;

    for (int i = 0; i < aNbOfLimits; i++)
	{
	if (sscanf(aMonthLimits[i], "%d:%d", &theMonths[i], &theLimits[i]) != 2)
	    {
	    isSuccessful = false;
	    }
	if ((theMonths[i] > 12) || (theLimits[i] > 999) || (theMonths[i] < 1))
	    {
	    isSuccessful = false;
	    }
	}

    if (isSuccessful == true)
	{
	for (int i = 0; i < aNbOfLimits; i++)
	    {
	    this->theMonthsLimits[aUserNb - 1]->limits[theMonths[i] - 1] =
		    theLimits[i];
	    }

	this->theMonthsLimits[aUserNb - 1]->save();
	}

    return isSuccessful;
    }

//getters
void tToolsCluster::getMonthsLimits(char* aMessage, UInt8 aUserNb)
    {
    char aTemp[8];
    unsigned int aLimit;

    sprintf(aMessage, "_");

    for (int i = 1; i <= 12; i++)
	{
	aLimit =
		(unsigned int) this->theMonthsLimits[aUserNb - 1]->limits[i - 1];
	sprintf(aTemp, "%d:%d_", i, aLimit);
	strcat(aMessage, aTemp);
	}
    }

void tToolsCluster::getMonthlyConsumption(char* aMessage, UInt8 aUserNb)
    {
    char aTemp[8];
    unsigned int aLimit;

    sprintf(aMessage, "_");

    for (int i = 1; i <= 12; i++)
	{
	aLimit =
		(unsigned int) this->theMeasuresStatement[aUserNb - 1]->MonthlyConsumption[i
			- 1];
	sprintf(aTemp, "%d:%d_", i, aLimit);
	strcat(aMessage, aTemp);
	}
    }

void tToolsCluster::getDailyConsumption(char* aMessage, UInt8 aUserNb)
    {
    char aTemp[8];
    unsigned int aLimit;

    sprintf(aMessage, "_");

    for (int i = 1; i <= 31; i++)
	{
	aLimit =
		(unsigned int) this->theMeasuresStatement[aUserNb - 1]->CurrentMonthConsumption[i
			- 1];
	sprintf(aTemp, "%d:%d_", i, aLimit);
	strcat(aMessage, aTemp);
	}
    }

void tToolsCluster::getEtat(char* aMessage, UInt8 aUserNb)
    {
    char aTemp[8];
    unsigned int aLimit;

    sprintf(aMessage, this->theUnitName->aName);
    //TODO : la suite du message
    }

// destructeur
tToolsCluster::~tToolsCluster()
    {
    }

