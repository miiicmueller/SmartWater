#include <string>
#include <assert.h>

#include "tMonthsLimits.h"
#include "Modules/mEEPROM.h"

tMonthsLimits::tMonthsLimits(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    //Configuration de la sauvegarde
    this->aId = kMONTHSLIM_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = 24; // 12 x 2 car on est sur 16 bits

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

    }

void tMonthsLimits::save()
    {
    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, this->aData.aDataTab);
    }

void tMonthsLimits::load()
    {
    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, this->aData.aDataTab);
    }

tMonthsLimits::~tMonthsLimits()
    {
    }
