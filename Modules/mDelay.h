//*****************************************************************************
//Nom du fichier : mDelay.h
//Auteurs et Date : SAVY Cyrille 01.05.2013
//But : utiliser les RTI (classe iRTI) pour mettre des temporisations � disposition
//*****************************************************************************

#ifndef __MDELAY__
#define __MDELAY__

#include "Module.h"
#include "../Interfaces/iRTI.h"

class mDelay
    {
public:
    //tools
    bool disponibility;

    //constructeur
    mDelay();

    //m�thodes h�rit�es
    static void mOpen();
    static void mClose();
    static void mSetup();

    //m�thodes
    void startDelay(int aTimeMs);
    bool isDone();

    //destructeur
    ~mDelay();

private:
    iRTI theDelayRTI;
    };

#endif
