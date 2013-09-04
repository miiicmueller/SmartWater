/*
 * tSIMCard.cpp
 *
 *  Created on: 30 août 2013
 *      Author: cyrille.savy
 */

#include "tSIMCard.h"

tSIMCard::tSIMCard(mEEPROM *mEeprom, UInt16 aModeNum)
    {
    this->mPeriphSauv = mEeprom;

    //Configuration de la sauvegarde
    this->aId = kSIMCARD_BASE_ID + aModeNum; //Id unique
    this->aNbBytes = 20; // 15 + 5

    //Allocation de la memoire
    this->mPeriphSauv->malloc(this->aId, this->aNbBytes);
    }

void tSIMCard::save()
    {
    UInt8 aDataTab[24];

    // Serialisation des limites
    for (int i = 0; i < 15; i++)
	{
	aDataTab[i] = (UInt8) (this->theOwnNumber[i]);
	}
    for (int i = 0; i < 5; i++)
	{
	aDataTab[i + 15] = (UInt8) (this->thePINCode[i]);
	}

    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, aDataTab);
    }

void tSIMCard::load()
    {
    UInt8 aDataTab[24];

    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, aDataTab);

    // Deserialisation des limites
    for (int i = 0; i < 15; i++)
	{
	this->theOwnNumber[i] = (char) aDataTab[i];
	}
    for (int i = 0; i < 5; i++)
	{
	this->thePINCode[i] = (char) aDataTab[i + 15];
	}
    }

tSIMCard::~tSIMCard()
    {
    }

