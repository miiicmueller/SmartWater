//*****************************************************************************
//Nom du fichier : iRTI.cpp
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : mettre en place un mécanisme de delay
//*****************************************************************************

#include "iRTI.h"

iRTI::iRTI()
    {
    int i;

    for (i = 0; (i < kNbOfDelays) && (this->delayTab[i].isFree == false); i++)
	;

    if (i == kNbOfDelays)
	{
	i = -1;
	}
    else
	{
	this->delayTab[i].isFree = false;
	}
    }

iRTI::~iRTI()
    {
    }

#pragma vector=TIMER0_B0_VECTOR
__interrupt void INT_TIMER_B_0(void)
    {
    }

//initialisation des attributs statiques
static const int nbOfDelays = kNbOfDelays;
static const tDelay delayTab[kNbOfDelays];
