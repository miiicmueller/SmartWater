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

    this->isPresent = false;
    this->isUnlocked = false;
    this->isActivate = false;
    }

bool mGSM::activateModule()
    {
    this->unlockSIM();

    return 0;
    }

bool mGSM::desactivateModule()
    {
    return false;
    }

std::string mGSM::getSMS()
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

//méthodes privées
void mGSM::sendCommandAT(std::string command, std::string data)
    {
    }

bool mGSM::controlPassword()
    {
    return false;
    }

void mGSM::unlockSIM()
    {
    }
