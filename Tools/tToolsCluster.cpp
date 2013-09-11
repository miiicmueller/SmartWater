/*
 * tToolsCluster.cpp
 *
 *  Created on: 30 ao�t 2013
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
	    this->theMeasuresStatement[i]->aData.aDataStruct.MonthlyConsumption[j] =
		    0;
	    }
	for (int j = 0; j < 31; j++)
	    {
	    this->theMeasuresStatement[i]->aData.aDataStruct.CurrentMonthConsumption[j] =
		    0;
	    }

	for (int j = 0; j < 12; j++)
	    {
	    this->theMonthsLimits[i]->aData.aDataStruct.limits[j] = 999;
	    }

	this->theCompteur[i]->aData.aDataStruct.aFabDate[0] = '\0';
	this->theCompteur[i]->aData.aDataStruct.aFluide[0] = '\0';
	this->theCompteur[i]->aData.aDataStruct.aManufacturer[0] = '\0';
	this->theCompteur[i]->aData.aDataStruct.aNominalSize[0] = '\0';
	this->theCompteur[i]->aData.aDataStruct.aSerialNum[0] = '\0';
	this->theCompteur[i]->aData.aDataStruct.aVersNum[0] = '\0';
	this->theCompteur[i]->aData.aDataStruct.aIndex = 0;
	this->theCompteur[i]->isConnected = false;
	}

    //le compteur de simulation
    this->theCompteur[2]->aData.aDataStruct.aFabDate[0] = '\0';
    this->theCompteur[2]->aData.aDataStruct.aFluide[0] = '\0';
    this->theCompteur[2]->aData.aDataStruct.aManufacturer[0] = '\0';
    this->theCompteur[2]->aData.aDataStruct.aNominalSize[0] = '\0';
    this->theCompteur[2]->aData.aDataStruct.aSerialNum[0] = '\0';
    this->theCompteur[2]->aData.aDataStruct.aVersNum[0] = '\0';
    this->theCompteur[2]->aData.aDataStruct.aIndex = 0;
    this->theCompteur[2]->isConnected = false;

    //parametres administrateur
    this->theAvailability->aData.aDataStruct.aIntervalMn = 60;
    this->theAvailability->aData.aDataStruct.aTimeMn = 15;

    sprintf(this->theMdPAdmin->mdPAdmin, "PassAdmin");

    this->theMode->mode = 'S';

    this->theTemperatureOffset->aOffset.aFakeFloat.integer = 0;
    this->theTemperatureOffset->aOffset.aFakeFloat.decimal = 0;

    sprintf(this->theUnitName->aName, "Unit1");

    sprintf(this->theSIMCard->aData.aDataStruct.theOwnNumber, "+41000000000");
    sprintf(this->theSIMCard->aData.aDataStruct.thePINCode, "0000");
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
	    this->theAvailability->aData.aDataStruct.aIntervalMn = aMinPeriod;
	    this->theAvailability->aData.aDataStruct.aTimeMn = aMinDuty;
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
    bool isSuccessful = false;

    if (sscanf(aTemperatureOffset, "%d.%d",
	    &this->theTemperatureOffset->aOffset.aFakeFloat.integer,
	    &this->theTemperatureOffset->aOffset.aFakeFloat.decimal) == 2)
	{
	isSuccessful = true;
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
	strcpy(this->theSIMCard->aData.aDataStruct.thePINCode, aPINCode);
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
	    strcpy(this->theSIMCard->aData.aDataStruct.theOwnNumber,
		    aOwnNumber);
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
	    this->theMonthsLimits[aUserNb - 1]->aData.aDataStruct.limits[theMonths[i]
		    - 1] = theLimits[i];
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
		(unsigned int) this->theMonthsLimits[aUserNb - 1]->aData.aDataStruct.limits[i
			- 1];
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
		(unsigned int) this->theMeasuresStatement[aUserNb - 1]->aData.aDataStruct.MonthlyConsumption[i
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
		(unsigned int) this->theMeasuresStatement[aUserNb - 1]->aData.aDataStruct.CurrentMonthConsumption[i
			- 1];
	sprintf(aTemp, "%d:%d_", i, aLimit);
	strcat(aMessage, aTemp);
	}
    }

void tToolsCluster::getEtat(char* aMessage, UInt8 aUserNb, tDate* theDate,
	UInt16 theCredit, Float32 theTemp)
    {
    char aTemp[20];

    aMessage[0] = '\0';
    strcat(aMessage, this->theUnitName->aName);
    strcat(aMessage, "\r\n");

    sprintf(aTemp, "%d/%d/%d %d:%d:%d", theDate->day, theDate->month,
	    theDate->year, theDate->hour, theDate->minute, theDate->second);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Disponibilite ");
    sprintf(aTemp, "%d:%d/%d:%d",
	    (this->theAvailability->aData.aDataStruct.aIntervalMn) / 60,
	    (this->theAvailability->aData.aDataStruct.aIntervalMn) % 60,
	    (this->theAvailability->aData.aDataStruct.aTimeMn) / 60,
	    (this->theAvailability->aData.aDataStruct.aTimeMn) % 60);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Mode ");
    aTemp[0] = this->theMode->mode;
    aTemp[1] = 0;
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Index ");
    sprintf(aTemp, "%d",
	    this->theCompteur[aUserNb - 1]->aData.aDataStruct.aIndex);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Debit jour ");
    sprintf(aTemp, "%d",
	    this->theMeasuresStatement[aUserNb - 1]->aData.aDataStruct.CurrentMonthConsumption[theDate->day
		    - 1]);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Debit mens ");
    sprintf(aTemp, "%d",
	    this->theMeasuresStatement[aUserNb - 1]->aData.aDataStruct.MonthlyConsumption[theDate->month
		    - 1]);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Limite jour ");
    sprintf(aTemp, "%d",
	    this->theMonthsLimits[aUserNb - 1]->aData.aDataStruct.limits[theDate->month
		    - 1]);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Temp ");
    sprintf(aTemp, "%d.%d", theTemp.aFakeFloat.integer,
	    theTemp.aFakeFloat.decimal / 10);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Off Temp ");
    sprintf(aTemp, "%d.%d",
	    this->theTemperatureOffset->aOffset.aFakeFloat.integer,
	    this->theTemperatureOffset->aOffset.aFakeFloat.decimal / 10);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Credit ");
    sprintf(aTemp, "%dcts", theCredit);
    strcat(aMessage, aTemp);
    strcat(aMessage, "\r\n");

    strcat(aMessage, "Alarme ");
    strcat(aMessage, this->theAlarmNumber[aUserNb]->aTelNumber);
    strcat(aMessage, "\r\n");
    }

// destructeur
tToolsCluster::~tToolsCluster()
    {
    }

