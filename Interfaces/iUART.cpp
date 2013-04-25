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

//TODO fixer cette valeur � la bonne fr�quence
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
 * aParity : Parit� de la communication
 * aDataCfg : format de donn�e sur 8 ou 7 bits
 * aBaudrate : vitesse de transmission
 *
 */
iUART::iUART(iUARTPortEnum aPort, iUARTSendModeEnum aSendMode,
	iUARTStopBitsEnum aStopBits, iUARTPartityEnum aParity,
	iUARTDataCfgEnum aDataCfg, UInt16 aBaudrate)
    {
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
    switch (this->serialPort)
	{
    case kUSCI_A0:
	// On doit tester si le pointeur n'est pas utilis�
	// par un autre objet
	if (this->USCI_0 == NULL)
	    {
	    USCI_0 = this;

	    }
	else
	    {
	    // Impossible de cr�er l'objet voulu
	    }
	break;
    case kUSCI_A1:
	// On doit tester si le pointeur n'est pas utilis�
	// par un autre objet
	if (this->USCI_1 == NULL)
	    {
	    USCI_1 = this;
	    }
	else
	    {
	    // Impossible de cr�er l'objet voulu
	    }
	break;
    default:
	;
	}

    }

/**
 * Destructeur de la classe iUart
 */
iUART::~iUART()
    {
    //Lib�ration de la pile d'interruption
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
 * Fonction de configuration du port assign� dans le constructeur
 * On peut tout modifier sauf le port
 *
 * aSendMode : LSB ou MSB en premier
 * aStopBits : nbr de stop bits
 * aParity : Parit� de la communication
 * aDataCfg : format de donn�e sur 8 ou 7 bits
 * aBaudrate : vitesse de transmission
 *
 */
void iUART::config(iUARTSendModeEnum aSendMode, iUARTStopBitsEnum aStopBits,
	iUARTPartityEnum aParity, iUARTDataCfgEnum aDataCfg, UInt16 aBaudrate)
    {

    //Calcul de la division
    UInt16 aBaudDiv = (UInt16) (F_BRCLK / (UInt32) aBaudrate);

    //Initialisation du port USCI
    switch (this->serialPort)
	{

    case kUSCI_A0:
	//Obligation de mettre le bit UCSWRST � 1
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

	//Configuration de la parit�e
	switch (aParity)
	    {
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
	if (k7bits == aDataCfg)
	    {
	    UCA0CTL0 |= UC7BIT;
	    }
	else
	    {
	    UCA0CTL0 &= ~UC7BIT;
	    }

	//Configuration du baudrate avec over sampling

	//Configuration modulation
	UCA0MCTL = 0x00;
	UCA0MCTL |= (UCBRF0 | UCOS16);

	aBaudDiv >>= 4; // Division par 16
	UCA0BR0 = (char) aBaudDiv;
	UCA0BR1 = (char) (aBaudDiv >> 8);

	//round([(N/16) � INT(N/16)] � 16)
	//Configuration de l'interruption � la reception
	UCA0IE |= UCRXIE;

	//Configuration du clock
	UCA0CTL1 |= UCSSEL__SMCLK;

	//Configuration des port I/O
	P3SEL |= 0x18;	// Selection de RX et TX

	break;

    case kUSCI_A1:
	//Obligation de mettre le bit UCSWRST � 1
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

	//Configuration de la parit�e
	switch (aParity)
	    {
	case kNone: //Pas de parit�e
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

	// Configuration de la longeur de don�es � tranmettre
	if (k7bits == aDataCfg)
	    {
	    UCA1CTL0 |= UC7BIT;
	    }
	else
	    {
	    UCA1CTL0 &= ~UC7BIT;
	    }

	//Configuration du baudrate
	UCA1BR0 = (char) aBaudDiv;
	UCA1BR1 = (char) (aBaudDiv >> 8);
	//TODO penser � ajouter le reste quand on conna�tra la fr�quence CPU

	//Configuration de l'interruption � la reception
	UCA1IE |= UCRXIE;

	//Configuration du clock
	UCA1CTL1 |= UCSSEL__SMCLK;

	break;
    default:
	;

	}
    }

/**
 * Fonction pour lire "1" byte recus dans le buffer tourant
 *
 */
char iUART::read()
    {
    if (isEnabled)
	{
	UInt8 aByteToRead = 0;

	aByteToRead =
		this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.OutIndex];

	// On incr�mente seulement apr�s avoir lu .
	this->USCIRingBuffer.OutIndex++;

	// Si on a atteint la derni�re case on revient � 0
	if (kSciRecBufSize <= this->USCIRingBuffer.OutIndex)
	    {
	    this->USCIRingBuffer.OutIndex = 0;
	    }

	this->USCIRingBuffer.ByteCount--;

	return aByteToRead;

	}
    else
	{
	return 0;
	}
    }

/**
 * Fonction pour transmettre "1" byte sur la ligne
 * !! La m�thode enable doit avoir �t� pr�alablement appel�e
 *
 */
bool iUART::write(char aData)
    {
    //test si l'interface est activ�
    if (isEnabled)
	{
	//Selection du port
	switch (this->serialPort)
	    {

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
	}
    else
	{
	return false;
	}
    }

/**
 * Fonction qui permet de lire 1 flag de status du port
 * !! La m�thode enable doit avoir �t� pr�alablement appel�e
 *
 * aFlag : nom du flag � lire
 *
 */
bool iUART::getStatusFlag(iUARTStatusFlag aFlag)
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
	break;
    case kUSCI_A1:
	UCA1CTL1 &= ~(UCSWRST);
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
 * Handler d'interruption propre � chaque objets
 *
 */
void iUART::interruptHandler()
    {
    UInt8 aReceivedChar = 0;
    if (this->serialPort == kUSCI_A0)
	{
	//Lecture du byte recu et ceci clear l'interruption
	aReceivedChar = UCA0RXBUF;

	// Test que le buffer ne soit pas plein
	if (false == this->USCIRingBuffer.BufferIsFull)
	    {
	    //Alors on �crit le byte recus dans le buffer
	    this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.InIndex] =
		    aReceivedChar;

	    //On incr�ment l'index et le nombre de byte recus
	    this->USCIRingBuffer.InIndex++;

	    // Si on a atteint la derni�re case on revient � 0
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
    else if (this->serialPort == kUSCI_A1)
	{
	//Lecture du byte recu et ceci clear l'interruption
	aReceivedChar = UCA1RXBUF;

	// Test que le buffer ne soit pas plein
	if (false == this->USCIRingBuffer.BufferIsFull)
	    {
	    //Alors on �crit le byte recus dans le buffer
	    this->USCIRingBuffer.UsciRecBuf[this->USCIRingBuffer.InIndex] =
		    aReceivedChar;

	    //On incr�ment l'index et le nombre de byte recus
	    this->USCIRingBuffer.InIndex++;

	    // Si on a atteint la derni�re case on revient � 0
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

// TODO - Tester les performances des fonctions send string

/**
 * Fonction pour envoyer une chaîne de caractère de type string
 *
 * aString : Chaîne à envoyer
 * retour  : "true" si la chaîne à bien été transmise
 */
bool iUART::sendString(string aString)
    {
    int i = 0;
    bool result = false;

    //Test si la chaîne est vide
    if (aString.empty() == false)
	{
	for (i = 0; i < aString.size(); i++)
	    {
	    result = this->write(aString.at(i));
	    }
	return result;
	}
    else
	{
	return false;
	}
    }

/**
 * Fonction qui permet d'obtenir le nombre de caractère contenu
 * dans le buffer
 *
 * retour  : nombre de caractère contenu dans le buffer
 */
int iUART::availableCharToRead()
    {
    return this->USCIRingBuffer.ByteCount;
    }

/**
 * Fonction qui permet d'obtenir l'ensemble des bytes recus
 * en mémoire
 *
 * retour  : chaîne de caractère
 */
void iUART::readFullBuffer(char* aBuffer)
    {
    int aCharNum = this->availableCharToRead();
    int i = 0;

    for (i = aCharNum; i > 0; i--)
	{
	aBuffer[i] = this->read();
	}
    }

/**
 * Fonction pour envoyer une chaîne de caractère de type char*
 *
 * aString : Chaîne à envoyeriUart
 * retour  : 1 si la chaîne à bien été transmise
 */
bool iUART::sendString(char* aString)
    {
    return sendString(string(aString));
    }

//-------------- INTERRUPT HANDLER | FRIEND OF iUart ------------

// USCIA0 Interrupt handler
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0(void)
    {
//V�rifiation que c'est bien un interruption en reception
    if ((UCA0IFG & UCRXIFG)== UCRXIFG)
	{
	// On teste si le pointeur iUART_0 a �t�  affect�
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
//V�rifiation que c'est bien un interruption en reception
    if ((UCA1IFG & UCRXIFG)== UCRXIFG)
	{
	// On teste si le pointeur iUART_1 a �t�  affect�
	if (iUART::USCI_1 != NULL)
	    {
	    iUART::USCI_1->interruptHandler();
	    }
	}
    }

