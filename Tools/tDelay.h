//*****************************************************************************
//Nom du fichier : tDelay.h
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : structure d'un delay utilisé dans mDelays et iRTI
//*****************************************************************************

#ifndef __TDELAY__
#define __TDELAY__

class tDelay
    {
public:
    //input
    int counter;

    //output
    bool isFree;
    bool isDone;

    tDelay();
    ~tDelay();
    };

#endif
