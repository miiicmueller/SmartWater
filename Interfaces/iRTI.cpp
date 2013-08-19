//*****************************************************************************
//Nom du fichier : iRTI.cpp
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : mettre en place un m�canisme de delay
//*****************************************************************************

#include "iRTI.h"

#define kNbOfDelays	10
#define kTA0_Period	25000 // clk � 25 000 000 Hz, divis� par 25 000, cela fait 1000Hz, soit 1ms
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

//m�thodes publiques
void iRTI::startDelay(int aTimeMs)
    {
    this->delaysTab[this->delayNumber].counter = aTimeMs;
    this->delaysTab[this->delayNumber].isDone = false;
    }

bool iRTI::isDone()
    {
    return this->delaysTab[this->delayNumber].isDone;
    }

//m�thodes statiques, qui agissent sur toutes les instances de la classe
void iRTI::config()
    {
    TA0CTL |= (TASSEL__SMCLK); //s�lection de la source d'horloge du compteur (divis� par 1 par d�faut)
    TA0CCR0 = kTA0_Period; //nombre de pas � compter pour avoir une p�riode de 1ms
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

