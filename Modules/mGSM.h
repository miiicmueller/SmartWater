//*****************************************************************************
//Nom du fichier : mGSM.h
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
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
    iDIO* enableGSM;
    iDIO* resetGSM;
    iUART* uartGSM;
    static iUART uartGSMStat;
    tCommandesAT* commandesATGSM;

    //tools
    bool isUnlocked;
    int indexSMS;

    void _delay_us(long aDelay);

public:

    char* phoneNumber;
    char* codePIN;

    //constructeur
    mGSM();

    bool getSMS(char* aSMS);
    bool sendSMS(char* aSMS, char* aPhoneNumber);
    tDate getHour();
    int getCredit();
    void mSetup();
    void mOpen();
    void mClose();

    //destructeur
    ~mGSM();

    };
#endif
