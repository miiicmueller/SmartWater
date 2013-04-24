//*****************************************************************************
//Nom du fichier : Module.cpp
//Auteur et Date : SAVY Cyrille 24.04.2013
//But : classe abstraite de la couche Module
//*****************************************************************************

#ifndef __MGSM__
#define __MGSM__

#include <string>

#include "Module.h"
#include "../Interfaces/iUART.h"
#include "../Interfaces/iDIO.h"
#include "../Tools/tCommandesAT.h"

using namespace std;

class mGSM: public Module
    {
private:
    //input
    iDIO* outputGSM;
    iUART* uartGSM;
    tCommandesAT* commandesATGSM;

    //tools
    bool isPresent;
    bool isUnlocked;
    bool isActivate;

    //output
    std::string SMSReceived;

public:
    //constructeur
    mGSM(iDIO* aOutputGSM, iUART* aUartGSM, tCommandesAT* aCommandesATGSM);

    bool activateModule();

    bool desactivateModule();

    string getSMS();

    void sendSMS(std::string data);

    //destructeur
    ~mGSM();

private:
    void sendCommandAT(std::string command, std::string data);

    bool controlPassword();

    void unlockSIM();

    };
#endif
