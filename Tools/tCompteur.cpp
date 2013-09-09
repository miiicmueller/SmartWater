#include <string>
#include <assert.h>

#include "tCompteur.h"
#include "Modules/mEEPROM.h"

tCompteur::tCompteur(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    this->isConnected = false;
    this->aData.aDataStruct.aIndex = 0;

    //Configuration de la sauvegarde
    this->aId = kCOMPTEUR_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = kSizeSerializerCompteur;

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

    }

void tCompteur::save()
    {
    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, this->aData.aDataTab);

    }
void tCompteur::load()
    {
    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, this->aData.aDataTab);
    }

tCompteur::~tCompteur()
    {
    }
