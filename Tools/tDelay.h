//*****************************************************************************
//Nom du fichier : tDelay.h
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : structure d'un delay utilis� dans mDelays et iRTI
//*****************************************************************************

#ifndef __TDELAY__
#define __TDELAY__

#include "Def/def.h"

class tDelay
    {
public:
    //input
    UInt32 counter;

    //output
    bool isFree;
    bool isDone;

    tDelay();
    ~tDelay();
    };

#endif
