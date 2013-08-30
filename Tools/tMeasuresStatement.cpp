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
    UInt8 i = 0;
    UInt8 j = 0;
    UInt8 aDataTab[86];

    // Serialisation des consommations
    for (i = 0, j = 0; i < 12; i++, j += 2)
	{
	aDataTab[j] = (UInt8) (this->MonthlyConsumption[i]);
	aDataTab[j + 1] = (UInt8) (this->MonthlyConsumption[i] >> 8);
	}
    for (i = 0, j = 12; i < 31; i++, j += 2)
	{
	aDataTab[j] = (UInt8) (this->CurrentMonthConsumption[i]);
	aDataTab[j + 1] = (UInt8) (this->CurrentMonthConsumption[i] >> 8);
	}

    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, aDataTab);
    }

void tMeasuresStatement::load()
    {
    UInt8 i = 0;
    UInt8 j = 0;
    UInt8 aDataTab[86];

    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, aDataTab);

    // Deserialisation des consommations
    for (i = 0, j = 0; i < 12; i++, j += 2)
	{
	this->MonthlyConsumption[i] = aDataTab[j];
	this->MonthlyConsumption[i] |= aDataTab[j + 1];
	}
    for (i = 0, j = 12; i < 31; i++, j += 2)
	{
	this->CurrentMonthConsumption[i] = (UInt16) aDataTab[j];
	this->CurrentMonthConsumption[i] |= (UInt16) aDataTab[j + 1];
	}
    }
