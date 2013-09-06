/*
 * tToolsCluster.h
 *
 *  Created on: 30 août 2013
 *      Author: cyrille.savy
 */

#ifndef TTOOLSCLUSTER_H_
#define TTOOLSCLUSTER_H_

#include "tAlarmNumber.h"
#include "tAvailability.h"
#include "tMdPAdmin.h"
#include "tMdPUser.h"
#include "tMeasuresStatement.h"
#include "tMode.h"
#include "tMonthsLimits.h"
#include "tTemperatureOffset.h"
#include "tUnitName.h"
#include "tSIMCard.h"
#include "tCompteur.h"

#define MaxPeriode 1440
#define MinPeriode 30
#define MaxDuree 30
#define MinDuree 0

class tToolsCluster
    {
public:
    //parametres utlisiteur
    tAlarmNumber* theAlarmNumber[2];
    tMdPUser* theMdPUser[2];
    tMeasuresStatement* theMeasuresStatement[2];
    tMonthsLimits* theMonthsLimits[2];
    tCompteur* theCompteur[3];

    //parametres administrateur
    tAvailability* theAvailability;
    tMdPAdmin* theMdPAdmin;
    tMode* theMode;
    tTemperatureOffset* theTemperatureOffset;
    tUnitName* theUnitName;
    tSIMCard* theSIMCard;

    //methodes
    void reset();

    void loadAll();

    void saveAll();

    //setters
    bool setAvailability(char* aPeriode, char* aDuree);

    bool setMdPAdmin(char* aMdP1, char* aMdP2);

    bool setMode(char* aMode);

    bool setTemperatureOffset(char* aTemperatureOffset);

    bool setUnitName(char* aUnitName);

    bool setPINCode(char* aPINCode);

    bool setOwnNumber(char* aOwnNumber);

    bool setAlarmNumber(char* aAlarmNumber, UInt8 aUserNb);

    bool setMdPUser(char* aMdP1, char* aMdP2, UInt8 aUserNb);

    bool setMonthsLimits(char** aMonthLimits, UInt8 aNbOfLimits, UInt8 aUserNb);

    //getters
    void getMonthsLimits(char* aMessage, UInt8 aUserNb);

    void getMonthlyConsumption(char* aMessage, UInt8 aUserNb);

    void getDailyConsumption(char* aMessage, UInt8 aUserNb);

    void getEtat(char* aMessage, UInt8 aUserNb);

    tToolsCluster(mEEPROM* aEEPROM);
    virtual ~tToolsCluster();
    };

#endif /* TTOOLSCLUSTER_H_ */
