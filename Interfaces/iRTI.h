//*****************************************************************************
//Nom du fichier : iRTI.h
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : mettre en place un mécanisme de delay
//*****************************************************************************

#ifndef __IRTI__
#define __IRTI__

#include "../Tools/tDelay.h"
#include <msp430f5519.h>
#include "def.h"

class iRTI
    {
public:
    //tools
    int delayNumber;

    iRTI();
    ~iRTI();

    void startDelay100US(UInt32 aTime100Us);
    bool isDone();

    //méthodes statiques, qui agissent sur toutes les instances de la classe
    static void config();
    static void enable();
    static void disable();

    static int freeDelays;

private:
    static tDelay delaysTab[];

    //Interruptions handlers
    friend void INT_TIMER_A_1(void);
    };

#endif
