//*****************************************************************************
//Nom du fichier : mDelay.h
//Auteurs et Date : SAVY Cyrille 01.05.2013
//But : utiliser les RTI (classe iRTI) pour mettre des temporisations à disposition
//*****************************************************************************

#ifndef __MDELAY__
#define __MDELAY__

#include "../Interfaces/iRTI.h"

class mDelay
    {
public:
    //tools
    bool disponibility;

    //constructeur
    mDelay();

    //méthodes héritées
    static void mOpen();
    static void mClose();
    static void mSetup();

    //méthodes
    void startDelayMS(UInt32 aTimeMs);
    void startDelay100US(UInt32 aTime100Us);
    bool isDone();

    //destructeur
    ~mDelay();

private:
    iRTI theDelayRTI;
    };

#endif
