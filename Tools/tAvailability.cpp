#include <string>
#include <assert.h>

#include "tAvailability.h"
#include "Modules/mEEPROM.h"

tAvailability::tAvailability(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    //Configuration de la sauvegarde
    this->aId = kAVAIL_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = 4; // 2 * 2 = 4

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);
    }

void tAvailability::save()
    {
    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, this->aData.aDataTab);

    }
void tAvailability::load()
    {

    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, this->aData.aDataTab);
    }

tAvailability::~tAvailability()
    {
    }
