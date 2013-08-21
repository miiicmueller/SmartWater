//*****************************************************************************
//Nom du fichier : mDelay.cpp
//Auteurs et Date : SAVY Cyrille 01.05.2013
//But : utiliser les RTI (classe iRTI) pour mettre des temporisations à disposition
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

//méthodes héritées
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

//méthodes
void mDelay::startDelayMS(int aTimeMs)
    {
    if (this->disponibility == true)
	{
	this->theDelayRTI.startDelayUS(aTimeMs * 1000);
	}
    }

//méthodes
void mDelay::startDelayUS(int aTimeUs)
    {
    if (this->disponibility == true)
	{
	this->theDelayRTI.startDelayUS(aTimeUs);
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

