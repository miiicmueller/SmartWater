#include <string>
#include <assert.h>

#include "tCompteur.h"
#include "Modules/mEEPROM.h"

tCompteur::tCompteur(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    //Configuration de la sauvegarde
    this->aId = kCOMPTEUR_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = kSizeSerializerCompteur;

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);

    }

void tCompteur::save()
    {
    UInt8 aDataTab[kSizeSerializerCompteur];
    UInt8 i;
    UInt8 j;

    //Serialisation
    for (j = 0, i = 0; j < kSizeManufacturer; i++, j++)
	{
	aDataTab[i] = (UInt8) this->aManufacturer[j];
	}
    for (j = 0; j < kSizeFluide; i++, j++)
	{
	aDataTab[i] = (UInt8) this->aFluide[j];
	}
    for (j = 0; j < kSizeVersNum; i++, j++)
	{
	aDataTab[i] = (UInt8) this->aVersNum[j];
	}
    for (j = 0; j < kSizeFabDate; i++, j++)
	{
	aDataTab[i] = (UInt8) this->aFabDate[j];
	}
    for (j = 0; j < kSizeSerialNum; i++, j++)
	{
	aDataTab[i] = (UInt8) this->aSerialNum[j];
	}
    for (j = 0; j < kSizeNominalSize; i++, j++)
	{
	aDataTab[i] = (UInt8) this->aNominalSize[j];
	}

    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, aDataTab);

    }
void tCompteur::load()
    {
    UInt8 aDataTab[kSizeSerializerCompteur];
    UInt8 i;
    UInt8 j;

    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, aDataTab);

    //Deserialisation
    for (j = 0, i = 0; j < kSizeManufacturer; i++, j++)
	{
	this->aManufacturer[j] = (char) aDataTab[i];
	}
    for (j = 0; j < kSizeFluide; i++, j++)
	{
	this->aFluide[j] = (char) aDataTab[i];
	}
    for (j = 0; j < kSizeVersNum; i++, j++)
	{
	this->aVersNum[j] = (char) aDataTab[i];
	}
    for (j = 0; j < kSizeFabDate; i++, j++)
	{
	this->aFabDate[j] = (char) aDataTab[i];
	}
    for (j = 0; j < kSizeSerialNum; i++, j++)
	{
	this->aSerialNum[j] = (char) aDataTab[i];
	}
    for (j = 0; j < kSizeNominalSize; i++, j++)
	{
	this->aNominalSize[j] = (char) aDataTab[i];
	}
    }

tCompteur::~tCompteur()
    {
    }
