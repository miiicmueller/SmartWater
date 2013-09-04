#include <string>
#include <assert.h>

#include "tMdPUser.h"
#include "Modules/mEEPROM.h"

tMdPUser::tMdPUser(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    //Configuration de la sauvegarde
    this->aId = kMPUSER_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = 20;

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);
    }

void tMdPUser::save()
    {
    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, (UInt8*) this->mdPUser);
    }

void tMdPUser::load()
    {
    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, (UInt8*) this->mdPUser);
    }

tMdPUser::~tMdPUser()
    {
    }
