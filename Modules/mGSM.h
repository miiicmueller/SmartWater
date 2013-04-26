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
#include "../Tools/tDate.h"

using namespace std;

class mGSM: public Module
    {
private:
    //input
    iDIO* outputGSM;
    iUART* uartGSM;
    tCommandesAT* commandesATGSM;

    //tools
    bool isUnlocked;
    int indexSMS;

public:

    string phoneNumber;
    string codePIN;

    //constructeur
    mGSM(iDIO* aOutputGSM, iUART* aUartGSM, tCommandesAT* aCommandesATGSM);

    bool getSMS(char* aSMS);
    void sendSMS(std::string aSMS);
    tDate getHour();
    int getCredit();
    void mSetup();
    void mOpen();
    void mClose();

    //destructeur
    ~mGSM();

    };
#endif
