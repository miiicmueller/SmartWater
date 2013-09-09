/*
 * tSIMCard.cpp
 *
 *  Created on: 30 ao�t 2013
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
    //Enregistrement dans l'EEPROM
    this->mPeriphSauv->store(this->aId, this->aData.aDataTab);
    }

void tSIMCard::load()
    {
    //Recuperation des donnees
    this->mPeriphSauv->load(this->aId, this->aData.aDataTab);

    }

tSIMCard::~tSIMCard()
    {
    }

