//*****************************************************************************
//Nom du fichier : iRTI.h
//Auteurs et Date : SAVY Cyrille 29.04.2013
//But : mettre en place un mécanisme de delay
//*****************************************************************************

#ifndef __IRTI__
#define __IRTI__

#include "../Tools/tDelay.h"
#include <msp430f5519.h>

class iRTI {
public:
	//tools
	int delayNumber;

	iRTI();
	~iRTI();

	void startDelay(int aTimeMs);
	bool isDone();

	//méthodes statiques, qui agissent sur toutes les instances de la classe
	static void config();
	static void enable();
	static void disable();

	static int freeDelays;

private:
	static tDelay delaysTab[];

	//Interruptions handlers
	friend void INT_TIMER_A_0(void);
};

#endif
