//*****************************************************************************
//Nom du fichier : iRTI.cpp
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : mettre en place un mécanisme de delay
//*****************************************************************************

#include "iRTI.h"

#define kNbOfDelays	5
#define kTA0_Period	400 // clk à 4 000 000 Hz, divisé par 400, cela fait 10 000Hz, soit 100us
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
void iRTI::startDelay100US(UInt32 aTime100Us)
    {
    this->delaysTab[this->delayNumber].counter = aTime100Us;
    this->delaysTab[this->delayNumber].isDone = false;
    }

bool iRTI::isDone()
    {
    return this->delaysTab[this->delayNumber].isDone;
    }

//méthodes statiques, qui agissent sur toutes les instances de la classe
void iRTI::config()
    {
    TA0CTL |= (TASSEL__SMCLK); //sélection de la source d'horloge du compteur (divisé par 1 par défaut)
    TA0CCR0 = kTA0_Period; //nombre de pas à compter pour avoir une période de 1us
    }

void iRTI::enable()
    {
    TA0CTL |= (TAIE); //timer A interrupt enable,
    TA0CTL |= (MC_1); //up mode,
    }

void iRTI::disable()
    {
    TA0CTL &= ~(TAIE); //timer A interrupt disable,
    TA0CTL |= (MC_0); //stop mode,
    }

//interrupt handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void INT_TIMER_A_1(void)
    {
    int i = 0;

    while (i < kNbOfDelays)
	{
	if (iRTI::delaysTab[i].isDone == false)
	    {
	    iRTI::delaysTab[i].counter--;

	    if (iRTI::delaysTab[i].counter == 0)
		{
		iRTI::delaysTab[i].isDone = true;
		}
	    }
	i++;
	}

    i = (TA0IV); //reset du flag d'interruption en lisant TA0IV
    }

