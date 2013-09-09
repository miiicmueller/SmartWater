#include <string>
#include <assert.h>

#include "tMeasuresStatement.h"
#include "Def/def.h"
#include "Modules/mEEPROM.h"

tMeasuresStatement::tMeasuresStatement(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    //Configuration de la sauvegarde
    this->aId = kMEASSTAT_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = 86; // (12 *2) + (31*2) les deux tableaux

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);
    }

void tMeasuresStatement::save()
    {
    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, this->aData.aDataTab);
    }

void tMeasuresStatement::load()
    {
    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, this->aData.aDataTab);
    }

tMeasuresStatement::~tMeasuresStatement()
    {
    }
