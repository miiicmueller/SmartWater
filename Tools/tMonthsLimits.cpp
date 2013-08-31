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
    UInt8 i = 0;
    UInt8 j = 0;
    UInt8 aDataTab[24];

    // Serialisation des limites
    for (i = 0, j = 0; i < 24; i += 2, j++)
	{
	aDataTab[i] = (UInt8) (this->limits[j]);
	aDataTab[i + 1] = (UInt8) (this->limits[j] >> 8);
	}

    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, aDataTab);
    }

void tMonthsLimits::load()
    {
    UInt8 i = 0;
    UInt8 j = 0;
    UInt8 aDataTab[24];

    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, aDataTab);

    // Deserialisation des limites
    for (i = 0, j = 0; i < 12; i++, j += 2)
	{
	this->limits[i] = (UInt16) (aDataTab[j]);
	this->limits[i] |= (UInt16) (aDataTab[j + 1]);
	}
    }

