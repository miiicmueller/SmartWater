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

	//initialiser le buffer tournant
	this->USCIRingBuffer.BufferIsFull = false;
	this->USCIRingBuffer.ByteCount = 0;
	this->USCIRingBuffer.InIndex = 0;
	this->USCIRingBuffer.OutIndex = 0;

}

void iUART::config(UARTSendModeEnum aSendMode, UARTStopBitsEnum aStopBits,
		UARTPartityEnum aParity, UARTDataCfgEnum aDataCfg, int aBaudrate) {

	//Calcul de la division
	int aBaudDiv = (int) (F_BRCLK / aBaudrate);

	//Initialisation du port USCI
	switch (this->serialPort) {

	case kUSCI_A0:
		//Obligation de mettre le bit UCSWRST � 1
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

		//Configuration de la parit�e
		switch (aParity) {
		case kNone: //Pas de parit�e
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

		// Configuration de la longeur de don�es � tranmettre
		if (k7bits == aDataCfg) {
			UCA0CTL0 |= UC7BIT;
		} else {
			UCA0CTL0 &= ~UC7BIT;
		}

		//Configuration du baudrate
		UCA0BR0 = (char) aBaudDiv;
		UCA0BR1 = (char) (aBaudDiv >> 8);
		//FIXME penser � ajouter le reste quand on conna�tra la fr�quence CPU

		//Configuration de l'interruption � la reception
		UCA0IE |= UCRXIE;

		break;

	case kUSCI_A1:
		//Obligation de mettre le bit UCSWRST � 1
		// pour permettre de configurer
		UCA1CTL1 |= UCSWRST;

		break;
	default:
		;

	}
}

char iUART::read() {
	if (isEnabled) {
		char aByteToRead = 0;

		aByteToRead =
				this->USCIRingBuffer.SciRecBuf[this->USCIRingBuffer.OutIndex];

		// On incr�mente seulement apr�s avoir lu .
		this->USCIRingBuffer.OutIndex++;

		// Si on a atteint la derni�re case on revient � 0
		if (kSciRecBufSize <= this->USCIRingBuffer.OutIndex) {
			this->USCIRingBuffer.OutIndex = 0;
		}

		this->USCIRingBuffer.ByteCount--;

		return aByteToRead;

	} else {
		return 0;
	}
}

bool iUART::write(char aData) {
	//test si l'interface est activ�
	if (isEnabled) {
		//Selection du port
		switch (this->serialPort) {

		case kUSCI_A0: // Sur le port 0
			UCA0TXBUF = aData;
			break;

		case kUSCI_A1: // Sur le port 1
			UCA1TXBUF = aData;
			break;

		default:
			;
		}
		return true;
	} else {
		return false;
	}
}

bool iUART::getStatusFlag(UARTStatusFlag aFlag) {
	switch (this->serialPort) {
	case kUSCI_A0:
		//Pas besoin de break car onfait un return directement
		switch (aFlag) {
		case kUCBUSY:
			return ((UCA0STAT & aFlag) == aFlag) ? true : false;

		case kUCRXERR:
			return ((UCA0STAT & aFlag) == aFlag) ? true : false;

		case kUCPE:
			return ((UCA0STAT & aFlag) == aFlag) ? true : false;

		case kUCOE:
			return ((UCA0STAT & aFlag) == aFlag) ? true : false;

		case kUCFE:
			return ((UCA0STAT & aFlag) == aFlag) ? true : false;

		case kUCLISTEN:
			return ((UCA0STAT & aFlag) == aFlag) ? true : false;

		default:
			return false;
			;
		}

	case kUSCI_A1:
		switch (aFlag) {
		case kUCBUSY:
			return ((UCA1STAT & aFlag) == aFlag) ? true : false;

		case kUCRXERR:
			return ((UCA1STAT & aFlag) == aFlag) ? true : false;

		case kUCPE:
			return ((UCA1STAT & aFlag) == aFlag) ? true : false;

		case kUCOE:
			return ((UCA1STAT & aFlag) == aFlag) ? true : false;

		case kUCFE:
			return ((UCA1STAT & aFlag) == aFlag) ? true : false;

		case kUCLISTEN:
			return ((UCA1STAT & aFlag) == aFlag) ? true : false;

		default:
			return false;
			;
		}
	default:
		return false;
	}
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

bool iUART::isBufferEmpty() {
	return (this->USCIRingBuffer.ByteCount > 0);
}

//-------------- INTERRUPT HANDLER ------------

// USCIA0 Interrupt handler
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0(void) {
	//V�rifiation que c'est bien un interruption en reception
	if ((UCA0IF & GUCRXIFG) == GUCRXIFG) {
		char aReceivedChar = 0;
		//Lecture du byte recu et ceci clear l'interruption
		aReceivedChar = UCA0RXBUF;

		// Test que le buffer ne soit pas plein
		if (kFalse == this->USCIRingBuffer.BufferIsFull) {
			//Alors on �crit le byte recus dans le buffer
			this->USCIRingBuffer.SciRecBuf[this->USCIRingBuffer.InIndex] =
					aReceivedChar;

			//On incr�ment l'index et le nombre de byte recus
			this->USCIRingBuffer.InIndex++;

			// Si on a atteint la derni�re case on revient � 0
			if (kSciRecBufSize <= this->USCIRingBuffer.InIndex) {
				this->USCIRingBuffer.InIndex = 0;
			}

			this->USCIRingBuffer.ByteCount++;
		}

		//Test si on a rempli le buffer Si on a recu n char
		if (kSciRecBufSize <= this->USCIRingBuffer.ByteCount) {
			this->USCIRingBuffer.BufferIsFull = kTrue;
		} else {
			this->USCIRingBuffer.BufferIsFull = kFalse;
		}
	}

}

// USCIA1 Interrupt handler
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1(void) {
	//V�rifiation que c'est bien un interruption en reception
	if ((UCA1IF & GUCRXIFG) == GUCRXIFG) {
		char aReceivedChar = 0;
		//Lecture du byte recu et ceci clear l'interruption
		aReceivedChar = UCA1RXBUF;

		// Test que le buffer ne soit pas plein
		if (kFalse == this->USCIRingBuffer.BufferIsFull) {
			//Alors on �crit le byte recus dans le buffer
			this->USCIRingBuffer.SciRecBuf[this->USCIRingBuffer.InIndex] =
					aReceivedChar;

			//On incr�ment l'index et le nombre de byte recus
			this->USCIRingBuffer.InIndex++;

			// Si on a atteint la derni�re case on revient � 0
			if (kSciRecBufSize <= this->USCIRingBuffer.InIndex) {
				this->USCIRingBuffer.InIndex = 0;
			}

			this->USCIRingBuffer.ByteCount++;
		}

		//Test si on a rempli le buffer Si on a recu n char
		if (kSciRecBufSize <= this->USCIRingBuffer.ByteCount) {
			this->USCIRingBuffer.BufferIsFull = kTrue;
		} else {
			this->USCIRingBuffer.BufferIsFull = kFalse;
		}
	}
}

