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

    }


bool mGSM::getSMS(char* aSMS)
    {
    return "";
    }

void mGSM::sendSMS(std::string data)
    {
    }

//destructeur
mGSM::~mGSM()
    {
    }
