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

void iUART::config(UARTSendModeEnum aSendMode, UARTStopBitsEnum aStopBits,
		UARTPartityEnum aParity) {

	//Initialisation du port USCI
	switch (this->serialPort) {

	case kUSCI_A0:
		//Obligation de mettre le bit UCSWRST à 1
		// pour permettre de configurer
		UCA0CTL1 |= UCSWRST;

		//Test du mode | LSB ou MSB first
		if (kMSBFirst == aSendMode) {
			UCA0CTL0 |= UCMSB;
		} else {
			UCA0CTL0 &= ~UCMSB;
		}

		// Configuration des bits de stop
		if (k1StBits == aStopBits) {
			UCA0CTL0 &= UCSPB;
		} else {
			UCA0CTL0 |= UCSPB;
		}

		//Configuration de la paritée
		switch (aParity) {
		case kNone: //Pas de paritée
			UCA0CTL0 &= ~UCPEN;
			break;
		case kOdd: // Parity impair
			UCA0CTL0 |= UCPEN;
			UCA0CTL0 &= ~UCPAR;
			break;
		case kEven: // parity paire
			UCA0CTL0 |= UCPEN;
			UCA0CTL0 |= UCPAR;
			break;
		default:
			;
		}


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

