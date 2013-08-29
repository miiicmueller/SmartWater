/*
 ------------------------------------------------------------
 Copyright 2003-200x Haute Ecole ARC Ing�nierie,
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

// fixer cette valeur a la bonne frequence
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

	this->dataReceived = false;

	//intialiser les adresse poiteur d'instance iUart pour les interruptions
	switch (this->serialPort) {
	case kUSCI_A0:
		// On doit tester si le pointeur n'est pas utilis�
		// par un autre objet
		if (this->USCI_0 == NULL) {
			USCI_0 = this;

		} else {
			// Impossible de creer l'objet voulu
		}
		break;
	case kUSCI_A1:
		// On doit tester si le pointeur n'est pas utilis�
		// par un autre objet
		if (this->USCI_1 == NULL) {
			USCI_1 = this;
		} else {
			// Impossible de creer l'objet voulu
		}
		break;
	default:
		;
	}

	this->clearReceptionBuffer();
	this->clearInternalSerialBuffer();
}

/**
 * Destructeur de la classe iUart
 */
iUART::~iUART()
    {
    //Liberation de la pile d'interruption
    switch (this->serialPort)
	{
    case kUSCI_A0:
	if (this->USCI_0 == this)
	    {
	    USCI_0 = NULL;
	    }
	break;
    case kUSCI_A1:
	if (this->USCI_1 == this)
	    {
	    USCI_1 = NULL;
	    }
	break;
    default:
	;
	}
    }

/**
 * Fonction de configuration du port assigne dans le constructeur
 * On peut tout modifier sauf le port
 *
 * aSendMode : LSB ou MSB en premier
 * aStopBits : nbr de stop bits
 * aParity : Parite de la communication
 * aDataCfg : format de donnee sur 8 ou 7 bits
 * aBaudrate : vitesse de transmission
 *
 */
void iUART::config(iUARTSendModeEnum aSendMode, iUARTStopBitsEnum aStopBits,
	iUARTPartityEnum aParity, iUARTDataCfgEnum aDataCfg,
	iUARTBaudrateEnum aBaudrate)
    {

    //Initialisation du port USCI
    switch (this->serialPort)
	{

    case kUSCI_A0:
	//Obligation de mettre le bit UCSWRST ï¿½ 1
	// pour permettre de configurer
	UCA0CTL1 |= UCSWRST;

	//Test du mode | LSB ou MSB first
	if (kMSBFirst == aSendMode)
	    {
	    UCA0CTL0 |= UCMSB;
	    }
	else
	    {
	    UCA0CTL0 &= ~UCMSB;
	    }

	// Configuration des bits de stop
	if (k1StBits == aStopBits)
	    {
	    UCA0CTL0 &= UCSPB;
	    }
	else
	    {
	    UCA0CTL0 |= UCSPB;
	    }

	//Configuration de la paritï¿½e
	switch (aParity)
	    {
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
	if (k7bits == aDataCfg)
	    {
	    UCA0CTL0 |= UC7BIT;
	    }
	else
	    {
	    UCA0CTL0 &= ~UC7BIT;
	    }

	//Configuration du baudrate avec over sampling

	//Configuration du clock
	UCA0CTL1 |= UCSSEL__SMCLK;

	switch (aBaudrate)
	    {
	case k300:
	    //Modulation
	    UCA0MCTL = 0x00;
	    UCA0MCTL |= UCOS16;
	    UCA0MCTL |= UCBRS_0 + UCBRF_1;
	    //Configuration du baudrate
	    UCA0BRW = 832;
	    break;
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
	    UCA0MCTL &= ~UCOS16;
	    UCA0MCTL |= UCBRS_6 + UCBRF_0;
	    //Configuration du baudrate
	    UCA0BRW = 34;
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
	if (kMSBFirst == aSendMode)
	    {
	    UCA1CTL0 |= UCMSB;
	    }
	else
	    {
	    UCA1CTL0 &= ~UCMSB;
	    }

	// Configuration des bits de stop
	if (k1StBits == aStopBits)
	    {
	    UCA1CTL0 &= UCSPB;
	    }
	else
	    {
	    UCA1CTL0 |= UCSPB;
	    }

	//Configuration de la paritï¿½e
	switch (aParity)
	    {
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
	UCA1CTL1 &= ~(UCMODE0 | UCMODE1);

	//Configuration de transmission asynchrone
	UCA1CTL1 &= ~(UCSYNC);

	// Configuration de la longeur de donï¿½es ï¿½ tranmettre
	if (k7bits == aDataCfg)
	    {
	    UCA1CTL0 |= UC7BIT;
	    }
	else
	    {
	    UCA1CTL0 &= ~UC7BIT;
	    }

	//Configuration du clock
	UCA1CTL1 |= UCSSEL__SMCLK;

	switch (aBaudrate)
	    {
	case k300:
	    //Modulation
	    UCA1MCTL = 0x00;
	    UCA1MCTL |= UCOS16;
	    UCA1MCTL |= ((0xB6) << 8);      // Modulation UCBRSx=6, UCBRFx=0
	    UCA1MCTL &= ~(UCBRF0 | UCBRF1 | UCBRF2 | UCBRF3);
	    //Configuration du baudrate
	    UCA1BRW = 832;
	    break;
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
	    UCA1MCTL &= ~UCOS16;
	    UCA1MCTL |= UCBRS_6 + UCBRF_0;
	    //Configuration du baudrate
	    UCA1BRW = 34;
	    break;
	    }

	//Configuration des port I/O
	P4SEL |= (BIT4 + BIT5);	// Selection de RX et TX

	break;
    default:
	;

	}

    for (int i = 0; i < kSciRecBufReceptionSize ; i++) // initialise le buffer uart
	{
	this->uartBuffer[i] = 0;
	}
    }

/**
 * Fonction pour lire "1" byte recus dans le buffer tourant
 *
 */
UInt8 iUART::read()
    {
    if (isEnabled)
	{
	UInt8 aByteToRead = 0;

	aByteToRead =
		this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.OutIndex];

	// On incrï¿½mente seulement aprï¿½s avoir lu .
	this->USCIRingBuffer.OutIndex++;

	// Si on a atteint la derniï¿½re case on revient ï¿½ 0
	if (kSciRecBufSize <= this->USCIRingBuffer.OutIndex)
	    {
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
bool iUART::write(UInt8 aData)
    {
    //test si l'interface est activï¿½
    if (isEnabled)
	{
	//Selection du port
	switch (this->serialPort)
	    {

	case kUSCI_A0: // Sur le port 0
	    while (!((UCA0IFG & UCTXIFG)== UCTXIFG))
		;
	    UCA0TXBUF = aData;
	    break;

	case kUSCI_A1: // Sur le port 1
	    while (!((UCA0IFG & UCTXIFG)== UCTXIFG))
		;
	    UCA1TXBUF = aData;
	    break;

	default:
	    ;
	    }
	return true;
	}
    else
	{
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
bool iUART::getStatusFlag(iUARTStatusFlagEnum aFlag)
    {
    switch (this->serialPort)
	{
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
void iUART::enable()
    {
    switch (this->serialPort)
	{

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
void iUART::disable()
    {
    switch (this->serialPort)
	{

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
bool iUART::isBufferEmpty()
    {
    return (this->USCIRingBuffer.ByteCount > 0);
    }

/**
 * Handler d'interruption propre ï¿½ chaque objets
 *
 */
void iUART::interruptHandler()
    {

    UInt8 aReceivedChar = 0;

    this->dataReceived = true;

    if (this->serialPort == kUSCI_A0)
	{
	//Lecture du byte recu et ceci clear l'interruption
	aReceivedChar = UCA0RXBUF;

	// Test que le buffer ne soit pas plein
	if (false == this->USCIRingBuffer.BufferIsFull)
	    {
	    //Alors on ï¿½crit le byte recus dans le buffer
	    this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.InIndex] =
		    aReceivedChar;

	    //On incrï¿½ment l'index et le nombre de byte recus
	    this->USCIRingBuffer.InIndex++;

	    // Si on a atteint la derni�re case on revient � 0
			if (kSciRecBufSize <= this->USCIRingBuffer.InIndex) {
				this->USCIRingBuffer.InIndex = 0;
			}

			this->USCIRingBuffer.ByteCount++;
		}

	//Test si on a rempli le buffer Si on a recu n char
	if (kSciRecBufSize <= this->USCIRingBuffer.ByteCount)
	    {
	    this->USCIRingBuffer.BufferIsFull = true;
	    }
	else
	    {
	    this->USCIRingBuffer.BufferIsFull = false;
	    }

	}
    else if (this->serialPort == kUSCI_A1)
	{
	//Lecture du byte recu et ceci clear l'interruption
	aReceivedChar = UCA1RXBUF;

	// Test que le buffer ne soit pas plein
	if (false == this->USCIRingBuffer.BufferIsFull)
	    {
	    //Alors on ï¿½crit le byte recus dans le buffer
	    this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.InIndex] =
		    aReceivedChar;

	    //On incrï¿½ment l'index et le nombre de byte recus
	    this->USCIRingBuffer.InIndex++;

	    // Si on a atteint la derniï¿½re case on revient ï¿½ 0
	    if (kSciRecBufSize <= this->USCIRingBuffer.InIndex)
		{
		this->USCIRingBuffer.InIndex = 0;
		}

	    this->USCIRingBuffer.ByteCount++;
	    }

	//Test si on a rempli le buffer Si on a recu n char
	if (kSciRecBufSize <= this->USCIRingBuffer.ByteCount)
	    {
	    this->USCIRingBuffer.BufferIsFull = true;
	    }
	else
	    {
	    this->USCIRingBuffer.BufferIsFull = false;
	    }
	}
    }

/**
 * Fonction qui permet d'obtenir l'ensemble des bytes recus
 * en mï¿½moire sï¿½parï¿½ d'un CR+LF
 *
 * aBuffer : Buffer d'entrï¿½e qui contiendra la ligne lue. Taille minimum de ce que l'on a recu
 * retour  : -1 si on a rien trouvï¿½ sinon la taille de la chaï¿½ne
 */
bool iUART::readFrame(UInt8* string) {
	UInt8 i = 0;
	UInt8 nDataReceived = 0;

    nDataReceived = this->USCIRingBuffer.ByteCount;

	//Tester si l'on a recu qqch
	if ((this->dataReceived == true) || (nDataReceived != 0)) {
		UInt8 pieceOfString[kSciRecBufSize ] = ""; //Holds the new addition to the string

	//Recuperation des bytes recus
	for (i = 0; i < nDataReceived; i++)
	    {
	    pieceOfString[i] = this->read();
	    }

	strcat((char*)this->uartBuffer,(char*) pieceOfString);

	// Test \r
	if (retInString(this->uartBuffer))
	    {
	    strcpy((char*)string, (char*)this->uartBuffer);
	    this->clearInternalSerialBuffer();
	    this->dataReceived = false;
	    return true;
	    }
	else
	    {
	    this->dataReceived = false;
	    return false;
	    }

	}
    else
	{
	return false;
	}
    }

/**
 * Fonction permettant d'obtenir les bytes reçus jusqu'au \r\n
 *
 * aString : chaine resortant la prochaine chaîne de byte reçus en mémoire, jusqu'à un CRLF
 * retour : true si une nouvelle chaine a ete trouvee
 */
bool iUART::readFrameToCRLF(char* aString)
    {
    UInt16 aNDataReceived = 0;
    bool aEndString = false;
    bool aIsOk;
    UInt16 i = 0;
    char pieceOfString[kSciRecBufSize ] = ""; //contient les nouveaux bytes

    aNDataReceived = this->USCIRingBuffer.ByteCount;

    if ((true == this->dataReceived) || (aNDataReceived != 0)) // teste si on a recu de nouveaux bytes
	{
	//Recuperation des bytes recus
	for (i = 0; (i < aNDataReceived) && (i < kSciRecBufSize) && (false == aEndString); i++)
	    {
	    pieceOfString[i] = this->read(); //prend les nouveaux bytes

	    if ('\r' == pieceOfString[i] || '\n' == pieceOfString[i]) // trouve LF ou CR
		{
		pieceOfString[i] = 0;
		aEndString = true;
		}
	    }

	if (0 == i) // ne prend pas en compte si la chaine etait vide //TODO changer en 1
	    {
	    aIsOk = false;
	    }
	else
	    {
	    strcat((char*)this->uartBuffer, (char*)pieceOfString); // ajoute les nouveaux bytes

	    if (aEndString) // on a la fin d'une ligne
		{
		strcpy((char*)aString, (char*)this->uartBuffer);
		this->clearInternalSerialBuffer();
		aIsOk = true;
		}
	    else
		{
		aIsOk = false;
		}

	    }
	}
    else
	{
	aIsOk = false;
	}

    return aIsOk;
    }

/**
 * Fonction qui permet d'obtenir l'ensemble des bytes recus
 * en memoire dans le buffer
 *
 * stringReceived : pointeur sur le tableau de recuperation du buffer
 *
 * retour  : true si il y a au moins un caractere dans le buffer
 */
bool iUART::readFullFrame(UInt8* stringReceived) {
	UInt8 i = 0;
	UInt8 nDataReceived = this->USCIRingBuffer.ByteCount;

	//Tester si l'on a recu qqch
	if (!((this->dataReceived == true) || (nDataReceived != 0)))
		{
		return false; // buf empty
		}

	//Recuperation des bytes recus
	for (i = 0; i < nDataReceived; i++)
		{
		stringReceived[i] = this->read();
		}
	return true;
}

// TODO - Tester les performances des fonctions send string

/**
 * Fonction qui permet d'obtenir le nombre de caractÃ¨re contenu
 * dans le buffer
 *
 * retour  : nombre de caractÃ¨re contenu dans le buffer
 */
UInt16 iUART::availableCharToRead()
    {
    return this->USCIRingBuffer.ByteCount;
    }

///**
// * Fonction qui permet d'obtenir l'ensemble des bytes recus
// * en mï¿½moire sï¿½parï¿½ d'un CR+LF
// *
// * aBuffer : Buffer d'entrï¿½e qui contiendra la ligne lue. Taille minimum de ce que l'on a recu
// * retour  : -1 si on a rien trouvï¿½ sinon la taille de la chaï¿½ne
// */
//int iUART::readLine(char* aBuffer) {
//	int i = 0;
//	int aByteCount = this->USCIRingBuffer.ByteCount;
//
//	//On enlï¿½ve les premier \r\n
//	this->read();
//	this->read();
//
//	//Detection du CR+LF
//	for (i = 0; (i < (aByteCount - 2)) && (aBuffer[i - 1] != 0x0D); i++) {
//		aBuffer[i] = this->read();
//	}
//	if (i < (aByteCount - 2)) //CR detectï¿½
//			{
//		//lecture du LF
//		aBuffer[i] = this->read();
//		//Effacement de CR+LF
//		aBuffer[i] = '\0';
//		aBuffer[i - 1] = '\0';
//		return i;
//	} else {
//		return -1;
//	}
//}

/**
 * Fonction pour envoyer une chaÃ®ne de caractÃ¨re de type char*
 *
 * aString : ChaÃ®ne Ã  envoyeriUart
 * retour  : 1 si la chaÃ®ne Ã  bien Ã©tÃ© transmise
 */
bool iUART::sendString(UInt8* aString) {
	UInt16 i = 0;
	bool result = false;

	//Test si la chaîne est vide
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

	//clear contenu buffer
	for(UInt16 i=0; i<kSciRecBufSize; i++)
		{
		this->USCIRingBuffer.UsciRecBuf[i]=0;
		}
}

void iUART::clearInternalSerialBuffer() {
	UInt8 i = 0;
	for (i = 0; i < kSciRecBufSize ; i++) {
		this->uartBuffer[i] = 0x00;
	}
    }


//This function returns TRUE if there's an 0x0D character in the string; and if so,
//it trims the 0x0D and anything that had followed it.
bool iUART::retInString(UInt8* string) {
	UInt8 retPos = 0, i, len;
	char tempStr[kSciRecBufSize ] = "";

	strncpy(tempStr, (char*)string, strlen((char*)string));        //Make a copy of the string
	len = strlen(tempStr);
	while ((tempStr[retPos] != 0x0A) && (tempStr[retPos] != 0x0D)
			&& (retPos++ < len))
		;        //Find 0x0D; if not found, retPos ends up at len

	if ((retPos < len) && (tempStr[retPos] == 0x0D)) { //If 0x0D was actually found...
		for (i = 0; i < kSciRecBufSize ; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy((char*)string, tempStr, retPos); //...trim the input string to just before 0x0D
		return true; //...and tell the calling function that we did so
	} else if ((retPos < len) && (tempStr[retPos] == 0x0A)) { //If 0x0D was actually found...
		for (i = 0; i < kSciRecBufSize ; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy((char*)string, tempStr, retPos); //...trim the input string to just before 0x0D
		return true; //...and tell the calling function that we did so
	} else if (tempStr[retPos] == 0x0D) {
		for (i = 0; i < kSciRecBufSize ; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy((char*)string, tempStr, retPos); //...trim the input string to just before 0x0D
		return true; //...and tell the calling function that we did so
	} else if (retPos < len) {
		for (i = 0; i < kSciRecBufSize ; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy((char*)string, tempStr, retPos); //...trim the input string to just before 0x0D
		return true; //...and tell the calling function that we did so
	}

    return false;                                 //Otherwise, it wasn't found
    }

//-------------- INTERRUPT HANDLER | FRIEND OF iUart ------------

// USCIA0 Interrupt handler
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0(void)
    {
//Vï¿½rifiation que c'est bien un interruption en reception
    if ((UCA0IFG & UCRXIFG)== UCRXIFG)
	{
	// On teste si le pointeur iUART_0 a ï¿½tï¿½  affectï¿½
	if (iUART::USCI_0 != NULL)
	    {
	    iUART::USCI_0->interruptHandler();
	    }
	}

    }

// USCIA1 Interrupt handler
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1(void)
    {
//Vï¿½rifiation que c'est bien un interruption en reception
    if ((UCA1IFG & UCRXIFG)== UCRXIFG)
	{
	// On teste si le pointeur iUART_1 a ï¿½tï¿½  affectï¿½
	if (iUART::USCI_1 != NULL)
	    {
	    iUART::USCI_1->interruptHandler();
	    }
	}
    }

