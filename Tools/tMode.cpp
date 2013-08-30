#include <string>
#include <assert.h>

#include "tMode.h"
#include "Modules/mEEPROM.h"

tMode::tMode(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;
    this->mode = 0;

    //Configuration de la sauvegarde
    this->aId = kMODE_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = 1;

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);
    }

void tMode::save()
    {
    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, (UInt8*) &(this->mode));
    }

void tMode::load()
    {
    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, (UInt8*) &(this->mode));
    }

