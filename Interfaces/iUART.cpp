#include <string>
#include <assert.h>
#include <msp430.h>

#include "iUART.h"
#include "../Def/enum_types.h"
#include "../Def/def.h"

iUART::iUART(UARTPortEnum aPort) {
	this->serialPort = aPort;

	this->config();

}

void iUART::config() {

	//Initialisation du port USCI
	switch (this->serialPort) {

	case kUSCI_A0:
		//Obligation de mettre le bit UCSWRST à 1
		// pour permettre de configurer
		UCA0CTL1 |= UCSWRST;

		break;
	case kUSCI_A1:
		//Obligation de mettre le bit UCSWRST à 1
		// pour permettre de configurer
		UCA1CTL1 |= UCSWRST;

		break;
	default:
		;

	}
}

char iUART::read() {

}

bool iUART::write(char aData) {

}

bool iUART::getStatusFlag(UARTStatusFlag aFlag) {

}

void iUART::enable() {
	switch (this->serialPort) {

	case kUSCI_A0:
		UCA0CTL1 &= ~(UCSWRST);
		break;
	case kUSCI_A1:
		UCA1CTL1 &= ~(UCSWRST);
		break;
	default:
		;

	}
}

void iUART::disable() {
	switch (this->serialPort) {

	case kUSCI_A0:
		UCA0CTL1 |= UCSWRST;
		break;
	case kUSCI_A1:
		UCA1CTL1 |= UCSWRST;
		break;
	default:
		;

	}
}

