//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteur et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#include "mGSM.h"

//méthodes publiques
//constructeur
mGSM::mGSM(iDIO* aOutputGSM, iUART* aUartGSM, tCommandesAT* aCommandesATGSM)
    {
    this->commandesATGSM = aCommandesATGSM;
    this->outputGSM = aOutputGSM;
    this->uartGSM = aUartGSM;

    this->isUnlocked = false;
    this->indexSMS = 0;
    }

std::string mGSM::getSMS(char* aSMS)
    {
    return "";
    }

void mGSM::sendSMS(std::string aSMS, std::string aPhoneNumber)
    {
    char aReceivedChar;
    std::string theAnswer();
    std::string theSMS(
	    this->commandesATGSM->aCommand + "=\"+" + aPhoneNumber + "\"\r"
		    + aSMS + "\r\n");

    this->uartGSM->sendString(theSMS);

    while (false == this->uartGSM->isBufferEmpty())
	{
	aReceivedChar = this->uartGSM->read();

	}

    }

//destructeur
mGSM::~mGSM()
    {
    }
