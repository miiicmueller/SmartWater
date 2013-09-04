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
    UInt8 aDataTab[4] =
	{
	0
	};

    //Serialisation
    aDataTab[0] = (UInt8) this->aIntervalMn;
    aDataTab[1] = (UInt8) (this->aIntervalMn >> 8);
    aDataTab[2] = (UInt8) this->aTimeMn;
    aDataTab[3] = (UInt8) (this->aTimeMn >> 8);

    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, aDataTab);

    }
void tAvailability::load()
    {
    UInt8 aDataTab[4] =
	{
	0
	};

    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, aDataTab);

    //Deserialisation
    this->aIntervalMn = (UInt8) aDataTab[0];
    this->aIntervalMn |= (UInt8) aDataTab[1];
    this->aTimeMn = (UInt8) aDataTab[2];
    this->aTimeMn |= (UInt8) aDataTab[3];

    }

