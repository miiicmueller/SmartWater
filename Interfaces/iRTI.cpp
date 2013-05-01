//*****************************************************************************
//Nom du fichier : iRTI.cpp
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : mettre en place un mécanisme de delay
//*****************************************************************************

#include "iRTI.h"

#define kNbOfDelays	10
#define kRTIper		1024
//TODO : fixer la valeur de kTA0_Period
#define kTA0_Period	500

//initialisation des attributs statiques
int iRTI::freeDelays = kNbOfDelays;
tDelay iRTI::delaysTab[kNbOfDelays];

//constructeur
iRTI::iRTI()
    {
    int i = 0;

    while ((i < kNbOfDelays) && (this->delaysTab[i].isFree == false))
	{
	i++;
	}

    if (i < kNbOfDelays)
	{
	this->delayNumber = i;
	this->freeDelays--;
	this->delaysTab[i].isFree = false;
	}
    else
	{
	this->delayNumber = -1;
	}
    }

//destructeur
iRTI::~iRTI()
    {
    this->delaysTab[this->delayNumber].isFree = true;
    this->freeDelays++;
    }

//méthodes publiques
void iRTI::startDelay(int aTimeMs)
    {
    this->delaysTab[this->delayNumber].counter = aTimeMs;
    this->delaysTab[this->delayNumber].isDone = false;
    }

bool iRTI::isDone()
    {
    return this->delaysTab[this->delayNumber].isDone;
    }

//méthodes statiques, qui agissent sur toutes les instances de la classe
void iRTI::config()
    {
    //TODO : sélectionner la source d'horloge pour le timer (cf. p. 476 user's guide) et le diviseur
    TA0CTL |= (TAIE); //up mode,

    TA0CCR0 = kTA0_Period; //nombre de pas à compter pour avoir une période de 1ms
    }

void iRTI::enable()
    {
    TA0CTL |= (MC_0); //stop mode,
    }

void iRTI::disable()
    {
    TA0CTL |= (MC_1); //up mode,
    }

//interrupt handler
#pragma vector=TIMER0_A0_VECTOR
__interrupt void INT_TIMER_A_0(void)
    {
    int i = 0;

    while (i < kNbOfDelays)
	{
	if (iRTI::delaysTab[i].isDone == false)
	    {
	    iRTI::delaysTab[i].counter--;

	    if (iRTI::delaysTab[i].counter == 0)
		{
		iRTI::delaysTab[i].isDone = false;
		}
	    }
	}
    }

