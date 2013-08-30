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

class tToolsCluster
    {
public:
    //parametres utlisiteur
    tAlarmNumber* theAlarmNumber[2];
    tMdPUser* theMdPUser[2];
    tMeasuresStatement* theMeasuresStatement[2];
    tMonthsLimits* theMonthsLimits[2];
    tCompteur* theCompteur[2];

    //parametres administrateur
    tAvailability* theAvailability;
    tMdPAdmin* theMdPAdmin;
    tMode* theMode;
    tTemperatureOffset* theTemperatureOffset;
    tUnitName* theUnitName;
    tSIMCard* theSIMCard;

    tToolsCluster(mEEPROM* aEEPROM);
    virtual ~tToolsCluster();
    };

#endif /* TTOOLSCLUSTER_H_ */
