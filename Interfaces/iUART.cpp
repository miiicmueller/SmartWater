/*
 ------------------------------------------------------------
 Copyright 2003-200x Haute Ecole ARC Ingï¿½nierie,
 Switzerland. All rights reserved
 ------------------------------------------------------------
 Nom du fichier : iUART.cpp
 Auteur et Date : Michael Mueller

 Description dans le fichier iUART.h
 ------------------------------------------------------------
 */
#include <cassert>
#include <msp430.h>

#include "iUART.h"
#include "../Def/def.h"

//TODO fixer cette valeur à la bonne frï¿½quence
#define F_BRCLK 4000000

//Initalisation des attributs UART_x statiques
iUART* iUART::USCI_0 = NULL;
iUART* iUART::USCI_1 = NULL;

/**
 * Constructeur principal de la classe iUart du MSP430
 *
 * aPort : Port de communication
 * aSendMode : LSB ou MSB en premier
 * aStopBits : nbr de stop bits
 * aParity : Paritï¿½ de la communication
 * aDataCfg : format de donnï¿½e sur 8 ou 7 bits
 * aBaudrate : vitesse de transmission
 *
 */
iUART::iUART(iUARTPortEnum aPort, iUARTSendModeEnum aSendMode,
		iUARTStopBitsEnum aStopBits, iUARTPartityEnum aParity,
		iUARTDataCfgEnum aDataCfg, iUARTBaudrateEnum aBaudrate) {
	//Assignation du port de communcation
	this->serialPort = aPort;
	//Configuration du port USCI
	this->config(aSendMode, aStopBits, aParity, aDataCfg, aBaudrate);

	//initialiser le buffer tournant
	this->USCIRingBuffer.BufferIsFull = false;
	this->USCIRingBuffer.ByteCount = 0;
	this->USCIRingBuffer.InIndex = 0;
	this->USCIRingBuffer.OutIndex = 0;

	//intialiser les adresse poiteur d'instance iUart pour les interruptions
	switch (this->serialPort) {
	case kUSCI_A0:
		// On doit tester si le pointeur n'est pas utilisï¿½
		// par un autre objet
		if (this->USCI_0 == NULL) {
			USCI_0 = this;

		} else {
			// Impossible de crï¿½er l'objet voulu
		}
		break;
	case kUSCI_A1:
		// On doit tester si le pointeur n'est pas utilisï¿½
		// par un autre objet
		if (this->USCI_1 == NULL) {
			USCI_1 = this;
		} else {
			// Impossible de crï¿½er l'objet voulu
		}
		break;
	default:
		;
	}

}

/**
 * Destructeur de la classe iUart
 */
iUART::~iUART() {
	//Libï¿½ration de la pile d'interruption
	switch (this->serialPort) {
	case kUSCI_A0:
		if (this->USCI_0 == this) {
			USCI_0 = NULL;
		}
		break;
	case kUSCI_A1:
		if (this->USCI_1 == this) {
			USCI_1 = NULL;
		}
		break;
	default:
		;
	}
}

/**
 * Fonction de configuration du port assignï¿½ dans le constructeur
 * On peut tout modifier sauf le port
 *
 * aSendMode : LSB ou MSB en premier
 * aStopBits : nbr de stop bits
 * aParity : Paritï¿½ de la communication
 * aDataCfg : format de donnï¿½e sur 8 ou 7 bits
 * aBaudrate : vitesse de transmission
 *
 */
void iUART::config(iUARTSendModeEnum aSendMode, iUARTStopBitsEnum aStopBits,
		iUARTPartityEnum aParity, iUARTDataCfgEnum aDataCfg,
		iUARTBaudrateEnum aBaudrate) {

	//Initialisation du port USCI
	switch (this->serialPort) {

	case kUSCI_A0:
		//Obligation de mettre le bit UCSWRST ï¿½ 1
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

		//Configuration de la paritï¿½e
		switch (aParity) {
		case kNone: //Pas de paritï¿½e
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

		// Configuration de la longeur de donï¿½es ï¿½ tranmettre
		if (k7bits == aDataCfg) {
			UCA0CTL0 |= UC7BIT;
		} else {
			UCA0CTL0 &= ~UC7BIT;
		}

		//Configuration du baudrate avec over sampling

		//Configuration du clock
		UCA0CTL1 |= UCSSEL__SMCLK;

		switch (aBaudrate) {
		case k4800:
			break;
		case k9600:
			//Modulation
			UCA0MCTL = 0x00;
			UCA0MCTL |= UCOS16;
			UCA0MCTL |= ((0xB6) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA0MCTL &= ~(UCBRF0 | UCBRF1 | UCBRF2 | UCBRF3);
			//Configuration du baudrate
			UCA0BRW = 26;
			break;
		case k19200:
			//Modulation
			UCA0MCTL = 0x00;
			UCA0MCTL |= UCOS16;
			UCA0MCTL |= ((0x84) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA0MCTL &= ~(UCBRF0 | UCBRF1 | UCBRF2 | UCBRF3);
			//Configuration du baudrate
			UCA0BRW = 13;
			break;
		case k57600:
			//Modulation
			UCA0MCTL = 0x00;
			UCA0MCTL |= UCOS16;
			UCA0MCTL |= ((0x55) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA0MCTL |= (UCBRF0 | UCBRF2);
			//Configuration du baudrate
			UCA0BRW = 4;
			break;
		case k115200:
			//Modulation
			UCA0MCTL = 0x00;
			UCA0MCTL |= UCOS16;
			UCA0MCTL |= ((0xBB) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA0MCTL |= (UCBRF1);
			//Configuration du baudrate
			UCA0BRW = 2;
			break;
		}

		//Configuration des port I/O
		P3SEL |= 0x18;	// Selection de RX et TX

		break;

	case kUSCI_A1:
		//Obligation de mettre le bit UCSWRST ï¿½ 1
		// pour permettre de configurer
		UCA1CTL1 |= UCSWRST;

		//Test du mode | LSB ou MSB first
		if (kMSBFirst == aSendMode) {
			UCA1CTL0 |= UCMSB;
		} else {
			UCA1CTL0 &= ~UCMSB;
		}

		// Configuration des bits de stop
		if (k1StBits == aStopBits) {
			UCA1CTL0 &= UCSPB;
		} else {
			UCA1CTL0 |= UCSPB;
		}

		//Configuration de la paritï¿½e
		switch (aParity) {
		case kNone: //Pas de paritï¿½e
			UCA1CTL0 &= ~UCPEN;
			break;
		case kOdd: // Parity impair
			UCA1CTL0 |= UCPEN;
			UCA1CTL0 &= ~UCPAR;
			break;
		case kEven: // parity paire
			UCA1CTL0 |= UCPEN;
			UCA1CTL0 |= UCPAR;
			break;
		default:
			;
		}

		// Configuration en mode UART => sans bit d'adresse
		UCA0CTL1 &= ~(UCMODE0 | UCMODE1);

		//Configuration de transmission asynchrone
		UCA0CTL1 &= ~(UCSYNC);

		// Configuration de la longeur de donï¿½es ï¿½ tranmettre
		if (k7bits == aDataCfg) {
			UCA1CTL0 |= UC7BIT;
		} else {
			UCA1CTL0 &= ~UC7BIT;
		}

		//Configuration du clock
		UCA1CTL1 |= UCSSEL__SMCLK;

		switch (aBaudrate) {
		case k4800:
					break;
		case k9600:
			//Modulation
			UCA1MCTL = 0x00;
			UCA1MCTL |= UCOS16;
			UCA1MCTL |= ((0xB6) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA1MCTL &= ~(UCBRF0 | UCBRF1 | UCBRF2 | UCBRF3);
			//Configuration du baudrate
			UCA1BRW = 26;
			break;
		case k19200:
			//Modulation
			UCA1MCTL = 0x00;
			UCA1MCTL |= UCOS16;
			UCA1MCTL |= ((0x84) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA1MCTL &= ~(UCBRF0 | UCBRF1 | UCBRF2 | UCBRF3);
			//Configuration du baudrate
			UCA1BRW = 13;
			break;
		case k57600:
			//Modulation
			UCA1MCTL = 0x00;
			UCA1MCTL |= UCOS16;
			UCA1MCTL |= ((0x55) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA1MCTL |= (UCBRF0 | UCBRF2);
			//Configuration du baudrate
			UCA1BRW = 4;
			break;
		case k115200:
			//Modulation
			UCA1MCTL = 0x00;
			UCA1MCTL |= UCOS16;
			UCA1MCTL |= ((0xBB) << 8);      // Modulation UCBRSx=6, UCBRFx=0
			UCA1MCTL |= (UCBRF1);
			//Configuration du baudrate
			UCA1BRW = 2;
			break;
		}
		break;
	default:
		;

	}
}

/**
 * Fonction pour lire "1" byte recus dans le buffer tourant
 *
 */
char iUART::read() {
	if (isEnabled) {
		UInt8 aByteToRead = 0;

		aByteToRead =
				this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.OutIndex];

		// On incrï¿½mente seulement aprï¿½s avoir lu .
		this->USCIRingBuffer.OutIndex++;

		// Si on a atteint la derniï¿½re case on revient ï¿½ 0
		if (kSciRecBufSize <= this->USCIRingBuffer.OutIndex) {
			this->USCIRingBuffer.OutIndex = 0;
		}

		this->USCIRingBuffer.ByteCount--;

		return aByteToRead;

	} else {
		return 0;
	}
}

/**
 * Fonction pour transmettre "1" byte sur la ligne
 * !! La mï¿½thode enable doit avoir ï¿½tï¿½ prï¿½alablement appelï¿½e
 *
 */
bool iUART::write(char aData) {
	//test si l'interface est activï¿½
	if (isEnabled) {
		//Selection du port
		switch (this->serialPort) {

		case kUSCI_A0: // Sur le port 0
			while (!(UCA0IFG & UCTXIFG))
				;
			UCA0TXBUF = aData;
			break;

		case kUSCI_A1: // Sur le port 1
			while (!(UCA1IFG & UCTXIFG))
				;
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

/**
 * Fonction qui permet de lire 1 flag de status du port
 * !! La mï¿½thode enable doit avoir ï¿½tï¿½ prï¿½alablement appelï¿½e
 *
 * aFlag : nom du flag ï¿½ lire
 *
 */
bool iUART::getStatusFlag(iUARTStatusFlagEnum aFlag) {
	switch (this->serialPort) {
	case kUSCI_A0:
		return ((UCA0STAT & aFlag) == aFlag) ? true : false;

	case kUSCI_A1:
		return ((UCA1STAT & aFlag) == aFlag) ? true : false;
	default:
		return false;
	}
}

/**
 * Fonction qui permet d'activer la communcation serielle
 *
 */
void iUART::enable() {
	switch (this->serialPort) {

	case kUSCI_A0:
		UCA0CTL1 &= ~(UCSWRST);

		//Configuration de l'interruption ï¿½ la reception
		UCA0IE |= UCRXIE;
		break;
	case kUSCI_A1:
		UCA1CTL1 &= ~(UCSWRST);

		//Configuration de l'interruption ï¿½ la reception
		UCA1IE |= UCRXIE;
		break;
	default:
		;

	}
	this->isEnabled = true;
}

/**
 * Fonction qui permet desactiver la communcation serielle
 *
 */
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

/**
 * Fonction qui permet de tester si le buffer tourant est vide
 *
 */
bool iUART::isBufferEmpty() {
	return (this->USCIRingBuffer.ByteCount > 0);
}

/**
 * Handler d'interruption propre ï¿½ chaque objets
 *
 */
void iUART::interruptHandler() {
	UInt8 aReceivedChar = 0;
	if (this->serialPort == kUSCI_A0) {
		//Lecture du byte recu et ceci clear l'interruption
		aReceivedChar = UCA0RXBUF;

		// Test que le buffer ne soit pas plein
		if (false == this->USCIRingBuffer.BufferIsFull) {
			//Alors on ï¿½crit le byte recus dans le buffer
			this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.InIndex] =
					aReceivedChar;

			//On incrï¿½ment l'index et le nombre de byte recus
			this->USCIRingBuffer.InIndex++;

			// Si on a atteint la derniï¿½re case on revient ï¿½ 0
			if (kSciRecBufSize <= this->USCIRingBuffer.InIndex) {
				this->USCIRingBuffer.InIndex = 0;
			}

			this->USCIRingBuffer.ByteCount++;
		}

		//Test si on a rempli le buffer Si on a recu n char
		if (kSciRecBufSize <= this->USCIRingBuffer.ByteCount) {
			this->USCIRingBuffer.BufferIsFull = true;
		} else {
			this->USCIRingBuffer.BufferIsFull = false;
		}
	} else if (this->serialPort == kUSCI_A1) {
		//Lecture du byte recu et ceci clear l'interruption
		aReceivedChar = UCA1RXBUF;

		// Test que le buffer ne soit pas plein
		if (false == this->USCIRingBuffer.BufferIsFull) {
			//Alors on ï¿½crit le byte recus dans le buffer
			this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.InIndex] =
					aReceivedChar;

			//On incrï¿½ment l'index et le nombre de byte recus
			this->USCIRingBuffer.InIndex++;

			// Si on a atteint la derniï¿½re case on revient ï¿½ 0
			if (kSciRecBufSize <= this->USCIRingBuffer.InIndex) {
				this->USCIRingBuffer.InIndex = 0;
			}

			this->USCIRingBuffer.ByteCount++;
		}

		//Test si on a rempli le buffer Si on a recu n char
		if (kSciRecBufSize <= this->USCIRingBuffer.ByteCount) {
			this->USCIRingBuffer.BufferIsFull = true;
		} else {
			this->USCIRingBuffer.BufferIsFull = false;
		}
	}
}

// TODO - Tester les performances des fonctions send string

/**
 * Fonction qui permet d'obtenir le nombre de caractÃ¨re contenu
 * dans le buffer
 *
 * retour  : nombre de caractÃ¨re contenu dans le buffer
 */
int iUART::availableCharToRead() {
	return this->USCIRingBuffer.ByteCount;
}

/**
 * Fonction qui permet d'obtenir l'ensemble des bytes recus
 * en mémoire séparé d'un CR+LF
 *
 * aBuffer : Buffer d'entrée qui contiendra la ligne lue. Taille minimum de ce que l'on a recu
 * retour  : -1 si on a rien trouvé sinon la taille de la chaîne
 */
int iUART::readLine(char* aBuffer) {
	int i = 0;

	//Detection du CR+LF
	for (i = 0; i < this->USCIRingBuffer.ByteCount || aBuffer[i] == '\r'; i++) {
		aBuffer[i] = this->read();
	}
	if (i < this->USCIRingBuffer.ByteCount) //CR detecté
			{
		//lecture du LF
		aBuffer[i] = this->read();
		aBuffer[i + 1] = this->read();
		//Effacement de CR+LF
		aBuffer[i] = '\0';
		aBuffer[i - 1] = '\0';
		return i;
	} else {
		return -1;
	}
}

/**
 * Fonction pour envoyer une chaÃ®ne de caractÃ¨re de type char*
 *
 * aString : ChaÃ®ne Ã  envoyeriUart
 * retour  : 1 si la chaÃ®ne Ã  bien Ã©tÃ© transmise
 */
bool iUART::sendString(const char* aString) {
	int i = 0;
	unsigned int j = 0;
	bool result = false;

	//Test si la chaÃ®ne est vide
	if (aString != NULL) {
		for (i = 0; aString[i] != '\0'; i++) {
			result = this->write(aString[i]);
		}
		return result;
	} else {
		return false;
	}
}

void iUART::clearReceptionBuffer() {
	//initialiser le buffer tournant
	this->USCIRingBuffer.BufferIsFull = false;
	this->USCIRingBuffer.ByteCount = 0;
	this->USCIRingBuffer.InIndex = 0;
	this->USCIRingBuffer.OutIndex = 0;
}

//-------------- INTERRUPT HANDLER | FRIEND OF iUart ------------

// USCIA0 Interrupt handler
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0(void) {
//Vï¿½rifiation que c'est bien un interruption en reception
	if ((UCA0IFG & UCRXIFG)== UCRXIFG) {
		// On teste si le pointeur iUART_0 a ï¿½tï¿½  affectï¿½
		if (iUART::USCI_0 != NULL) {
			iUART::USCI_0->interruptHandler();
		}
	}

}

// USCIA1 Interrupt handler
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1(void) {
//Vï¿½rifiation que c'est bien un interruption en reception
	if ((UCA1IFG & UCRXIFG)== UCRXIFG) {
		// On teste si le pointeur iUART_1 a ï¿½tï¿½  affectï¿½
		if (iUART::USCI_1 != NULL) {
			iUART::USCI_1->interruptHandler();
		}
	}
}

