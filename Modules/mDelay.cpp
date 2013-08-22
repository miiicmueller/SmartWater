//*****************************************************************************
//Nom du fichier : mDelay.cpp
//Auteurs et Date : SAVY Cyrille 01.05.2013
//But : utiliser les RTI (classe iRTI) pour mettre des temporisations � disposition
//*****************************************************************************

#include "mDelay.h"

//constructeur
mDelay::mDelay()
    {
    if (this->theDelayRTI.delayNumber != -1)
	{
	this->disponibility = true;
	}
    else
	{
	this->disponibility = false;
	}
    }

//m�thodes h�rit�es
void mDelay::mOpen()
    {
    iRTI::enable();
    }

void mDelay::mClose()
    {
    iRTI::disable();
    }

void mDelay::mSetup()
    {
    iRTI::config();
    }

//m�thodes
void mDelay::startDelayMS(UInt32 aTimeMs)
    {
    if (this->disponibility == true)
	{
	this->theDelayRTI.startDelay100US(aTimeMs * 10);
	}
    }

//m�thodes
void mDelay::startDelay100US(UInt32 aTime100Us)
    {
    if (this->disponibility == true)
	{
	this->theDelayRTI.startDelay100US(aTime100Us);
	}
    }

bool mDelay::isDone()
    {
    if (this->disponibility == true)
	{
	return this->theDelayRTI.isDone();
	}
    else
	{
	return true;
	}
    }

//destructeur
mDelay::~mDelay()
    {
    }

