#include <string>
#include <assert.h>
#include <msp430.h>

#include "iUART.h"
#include "../Def/enum_types.h"
#include "../Def/def.h"

#define F_BRCLK 15000

iUART::iUART(UARTPortEnum aPort, UARTSendModeEnum aSendMode,
		UARTStopBitsEnum aStopBits, UARTPartityEnum aParity,
		UARTDataCfgEnum aDataCfg, int aBaudrate) {
	//Assignation du port de communcation
	this->serialPort = aPort;
	//Configuration du port USCI
	this->config(aSendMode, aStopBits, aParity, aDataCfg, aBaudrate);

}

void iUART::config(UARTSendModeEnum aSendMode, UARTStopBitsEnum aStopBits,
		UARTPartityEnum aParity, UARTDataCfgEnum aDataCfg, int aBaudrate) {

	//Calcul de la division
	int aBaudDiv = (int) (F_BRCLK / aBaudrate);

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

		// Configuration en mode UART => sans bit d'adresse
		UCA0CTL0 &= ~(UCMODE0 | UCMODE1);

		//Configuration de transmission asynchrone
		UCA0CTL0 &= ~(UCSYNC);

		// Configuration de la longeur de donées à tranmettre
		if (k7bits == aDataCfg) {
			UCA0CTL0 |= UC7BIT;
		} else {
			UCA0CTL0 &= ~UC7BIT;
		}

		//Configuration du baudrate
		UCA0BR0 = (char) aBaudDiv;
		UCA0BR1 = (char) (aBaudDiv >> 8);
		//FIXME penser à ajouter le reste quand on connaîtra la fréquence CPU

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
	if (isEnabled) {
		return 0;
	} else {
		return 0;
	}
}

bool iUART::write(char aData) {
	//test si l'interface est activé
	if (isEnabled) {
		//Selection du port
		switch (this->serialPort) {
		case kUSCI_A0: // Sur le port 0
			UCA0TXBUF = aData;
			return true;
			break;
		case kUSCI_A1: // Sur le port 1
			UCA1TXBUF = aData;
			return true;
			break;
		default:
			;
		}
	} else {
		return false;
	}
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
	this->isEnabled = true;
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
	this->isEnabled = false;
}

