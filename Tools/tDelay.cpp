//*****************************************************************************
//Nom du fichier : tDelay.cpp
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : structure d'un delay utilisé dans mDelays et iRTI
//*****************************************************************************

#include "tDelay.h"

tDelay::tDelay()
    {
    this->counter = 0;
    this->isFree = true;
    this->isDone = true;
    }

tDelay::~tDelay()
    {
    }

