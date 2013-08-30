#include <string>
#include <assert.h>

#include "tCompteur.h"
#include "Modules/mEEPROM.h"

tCompteur::tCompteur(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    //Configuration de la sauvegarde
    this->aId = kCOMPTEUR_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = 46;

    //Allocation de la mémoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

    }

void tCompteur::save()
    {
    UInt8 aDataTab[46] =
	{
	0
	};
    UInt8 i = 0;

    //Serialisation
    for (i = 0; i < 4; i++)
	{
	aDataTab[i] = this->aManufacturer[i];
	}
    for (i = 4; i < 14; i++)
	{
	aDataTab[i] = this->aFluide[i];
	}
    for (i = 14; i < 19; i++)
	{
	aDataTab[i] = this->aVersNum[i];
	}
    for (i = 19; i < 28; i++)
	{
	aDataTab[i] = this->aFabDate[i];
	}
    for (i = 28; i < 36; i++)
	{
	aDataTab[i] = this->aSerialNum[i];
	}
    for (i = 36; i < 46; i++)
	{
	aDataTab[i] = this->aNominalSize[i];
	}

    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, aDataTab);

    }
void tCompteur::load()
    {
    UInt8 aDataTab[46] =
	{
	0
	};
    UInt8 i = 0;

    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, aDataTab);

    //Deserialisation
    for (i = 0; i < 4; i++)
	{
	this->aManufacturer[i] = aDataTab[i];
	}
    for (i = 4; i < 14; i++)
	{
	this->aFluide[i] = aDataTab[i];
	}
    for (i = 14; i < 19; i++)
	{
	this->aVersNum[i] = aDataTab[i];
	}
    for (i = 19; i < 28; i++)
	{
	this->aFabDate[i] = aDataTab[i];
	}
    for (i = 28; i < 36; i++)
	{
	this->aSerialNum[i] = aDataTab[i];
	}
    for (i = 36; i < 46; i++)
	{
	this->aNominalSize[i] = aDataTab[i];
	}
    }

