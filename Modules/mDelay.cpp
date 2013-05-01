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
	this->disponibility = false;
	}
    else
	{
	this->disponibility = true;
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
void mDelay::startDelay(int aTimeMs)
    {
    if (this->disponibility == true)
	{
	this->theDelayRTI.startDelay(aTimeMs);
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

