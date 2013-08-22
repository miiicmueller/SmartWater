#include <string>
#include <assert.h>

#include "mEEPROM.h"
#include "mDelay.h"
#include "Interfaces/iI2C.h"

// Adresse de base de la table
#define kTABLE_BASE_ADR 0
//Taille de la table
#define kTABLE_SIZE		1024

// Adresse des données
#define kDATA_BASE_ADR kTABLE_BASE_ADR + kTABLE_SIZE

//Position de la structure de la table
#define kIdLowPos  0
#define kIdHighPos  1
#define kAdrLowPos  2
#define kAdrHighPos 3
#define kSizeLowPos  4
#define kSizeHighPos  5

#define kRecordSize 6

/**
 * Création d'une EEPROM
 * moduleAddress : Adresse de l'EEPROM
 * i2cBus : Noeud i2c sur lequel il est connecté.
 */
mEEPROM::mEEPROM(UInt16 moduleAddress, iI2C *i2cBus)
    {
    this->moduleAddress = moduleAddress;
    this->availableData = (UInt16) 0xFFFF - (UInt16) kDATA_BASE_ADR;
    this->usedBytes = 0;
    this->i2c_1 = i2cBus;
    this->aStatus = 0;

    }

mEEPROM::~mEEPROM()
    {

    }

/**
 * Activation du port I2C + Va lire la table d'adresse et compter combien son encore disponibles
 */
void mEEPROM::mOpen()
    {
    UInt8 aByteTemp = 0;
    UInt16 aSize = 0;
    UInt16 i = 0;
    bool aHasNext = false;

    this->i2c_1->enable();
    this->usedBytes = 0;

    //On attend que l'EEPROM soit prete
    if (!this->ackPolling())
	{
	//mOpen error
	this->aStatus = 1;
	return;
	}

    //Si le premier byte est un zero alors on a rien Ou si on as pas pu lire
    aByteTemp = this->read(kTABLE_BASE_ADR);

    if (aByteTemp != 0)
	{
	aHasNext = true;
	for (i = kTABLE_BASE_ADR + kSizeLowPos; i < kTABLE_SIZE && aHasNext;
		i += kSizeLowPos)
	    {
	    //lecture des tailles
	    aSize = this->read(i);
	    aSize |= (this->read(i + 1) << 8);

	    //Enregistrement de la taille deja allouee
	    this->usedBytes += aSize;

	    //Test si on arrive a la fin
	    if (this->read(i + 2) == 0)
		{
		aHasNext = false;
		}
	    //On se met sur le prochain enregistrement
	    i += 2;
	    }
	}
    }

/**
 * Surtout pas de bus i2c->disable !!
 * Plusieurs autres composant peuvent être sur le bus !
 */
void mEEPROM::mClose()
    {
    }

/**
 * rien
 */
void mEEPROM::mSetup()
    {

    }

/**
 * Permet de tester l'état du module
 * retour : valeur du status
 */
UInt8 mEEPROM::getStatus()
    {
    return this->aStatus;
    }

/*
 * Libère de la mémoire allouée.
 * UInt16 aId : Id unique d'un objet. Le byte de poids faible ne doit jamais valoir 0 !!!
 *
 * retour : true si la libération à réussie
 */
bool mEEPROM::free(UInt16 aId)
    {

    UInt16 i = 0;
    UInt16 aId_ee = 0;
    bool aHasNext = true;
    bool aIdFound = false;

    UInt16 aLastSize = 0;

    // L'Open de l'EEPROM a eu une erreur
    if (this->aStatus != 0)
	{
	return false;
	}
    //L'EEPROM est vide
    else if (this->usedBytes == 0)
	{
	return false;
	}
    //On parcours la table
    else
	{
	//On parcours tout l'enregistrement et on vérifie aussi si l'enregistrement exite deja
	for (i = kTABLE_BASE_ADR; i < kTABLE_SIZE && aHasNext && !aIdFound; i +=
		kRecordSize)
	    {
	    //lecture des IDs
	    aId_ee = this->read(i + kIdLowPos);
	    aId_ee |= (this->read(i + kIdHighPos) << 8);

	    //Lecture de la taille
	    aLastSize = this->read(i + kSizeLowPos);
	    aLastSize |= (this->read(i + kSizeHighPos) << 8);

	    //Verification si l'adresse existe déja
	    if (aId_ee == aId)
		{
		aIdFound = true;
		}

	    //Test si on arrive a la fin
	    if (this->read(i + kRecordSize) == 0)
		{
		aHasNext = false;
		}
	    }

	//Si on a trouvé l'ID
	if (aIdFound)
	    {
	    i = i - kRecordSize;
	    //On écrit l'entete ID libre
	    //On enregistre la partie basse de l'Id
	    this->write(i + kIdLowPos, (UInt8) kFREE_BASE_ID);

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie haute de l'Id
	    this->write(i + kIdHighPos, (UInt8) (kFREE_BASE_ID >> 8));

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}

	    // On retire les bytes utilisés
	    this->usedBytes -= aLastSize;

	    return true;
	    }
	//Si on est arrivé à la fin de la liste
	else
	    {
	    return false;
	    }

	}
    }

/*
 * Alloue de la mémoire en fonction de la capacité restante de l'EEPROM. On peut le faire une fois seulement !!
 * UInt16 aId : Id unique d'un objet. Le byte de poids faible ne doit jamais valoir 0 !!!
 * UInt16 size : nombre de bytes à allouer
 *
 * retour : true si l'allocation à réussie
 */
bool mEEPROM::malloc(UInt16 aId, UInt16 aSize)
    {

    UInt16 aNewAdress = 0;
    UInt16 i = 0;

    // L'Open de l'EEPROM a eu une erreur
    if (this->aStatus != 0)
	{
	return false;
	}
    //L'EEPROM est vide
    else if (this->usedBytes == 0)
	{
	//Calcul de la nouvelle addresse en fonction des bytes utilisés
	aNewAdress = kDATA_BASE_ADR + this->usedBytes;
	this->usedBytes += aSize;

	//On enregistre la partie basse de l'Id
	this->write(i + kIdLowPos, (UInt8) aId);

	//On attend que l'EEPROM soit prete
	if (!this->ackPolling())
	    {
	    return false;
	    }
	//On enregistre la partie haute de l'Id
	this->write(i + kIdHighPos, (UInt8) (aId >> 8));

	//On attend que l'EEPROM soit prete
	if (!this->ackPolling())
	    {
	    return false;
	    }
	//On enregistre la partie basse de l'adresse
	this->write(i + kAdrLowPos, (UInt8) aNewAdress);

	//On attend que l'EEPROM soit prete
	if (!this->ackPolling())
	    {
	    return false;
	    }
	//On enregistre la partie haute de l'adresse
	this->write(i + kAdrHighPos, (UInt8) (aNewAdress >> 8));

	//On attend que l'EEPROM soit prete
	if (!this->ackPolling())
	    {
	    return false;
	    }
	//On enregistre la partie basse de la taille
	this->write(i + kSizeLowPos, (UInt8) aSize);

	//On attend que l'EEPROM soit prete
	if (!this->ackPolling())
	    {
	    return false;
	    }
	//On enregistre la partie haute de la taille
	this->write(i + kSizeHighPos, (UInt8) (aSize >> 8));

	//On attend que l'EEPROM soit prete
	if (!this->ackPolling())
	    {
	    return false;
	    }
	//On enregistre la fin des enregistrement
	this->write(i + kRecordSize, 0x00);

	return true;
	}
    //Si la taille exigée est trop grande
    else if (this->availableData >= aSize)
	{

	UInt16 aId_ee = 0;
	bool aHasNext = false;
	bool aIdFound = false;
	bool aIdFreeFound = false;

	UInt16 aLastAdr = 0;
	UInt16 aLastSize = 0;

	//Calcul de la nouvelle addresse en fonction des bytes utilisés
	aNewAdress = kDATA_BASE_ADR + this->usedBytes;
	this->usedBytes += aSize;

	//Enregistrement dans la table

	//Lecture de la table pour vérifier si l'ID existe. Sinon on ne fait rien

	//On attend que l'EEPROM soit prete
	if (!this->ackPolling())
	    {
	    return false;
	    }

	aHasNext = true;
	aIdFound = false;
	aIdFreeFound = false;

	//On parcours tout l'enregistrement et on vérifie aussi si l'enregistrement exite deja
	for (i = kTABLE_BASE_ADR;
		i < kTABLE_SIZE && aHasNext && !aIdFound && !aIdFreeFound; i +=
			kRecordSize)
	    {
	    //lecture des tailles
	    aId_ee = this->read(i + kIdLowPos);
	    aId_ee |= (this->read(i + kIdHighPos) << 8);

	    //Lecture de l'addresse
	    aLastAdr = this->read(i + kAdrLowPos);
	    aLastAdr |= (this->read(i + kAdrHighPos) << 8);

	    //Lecture de la taille
	    aLastSize = this->read(i + kSizeLowPos);
	    aLastSize |= (this->read(i + kSizeHighPos) << 8);

	    //Verification si l'adresse existe déja
	    if (aId_ee == aId)
		{
		aIdFound = true;
		}

	    else if (aId_ee == (UInt16) kFREE_BASE_ID && aLastSize >= aSize)
		{
		aIdFreeFound = true;
		}

	    //Test si on arrive a la fin
	    else if (this->read(i + kRecordSize) == 0)
		{
		aHasNext = false;
		}
	    }

	//Si on a trouvé l'id existant on arrete tout
	if (aIdFound)
	    {
	    this->usedBytes -= aSize;
	    return false;
	    }
	else if (aIdFreeFound)
	    {
	    i -= kRecordSize;
	    //On enregistre la partie basse de l'Id
	    this->write(i + kIdLowPos, (UInt8) aId);

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie haute de l'Id
	    this->write(i + kIdHighPos, (UInt8) (aId >> 8));

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie basse de la taille
	    this->write(i + kSizeLowPos, (UInt8) aSize);

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie haute de la taille
	    this->write(i + kSizeHighPos, (UInt8) (aSize >> 8));

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}

	    return true;
	    }
	// Sinon on a atteint la fin des enregistrement
	else if (!aHasNext)
	    {

	    //On enregistre la partie basse de l'Id
	    this->write(i + kIdLowPos, (UInt8) aId);

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie haute de l'Id
	    this->write(i + kIdHighPos, (UInt8) (aId >> 8));

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie basse de l'adresse
	    this->write(i + kAdrLowPos, (UInt8) aNewAdress);

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie haute de l'adresse
	    this->write(i + kAdrHighPos, (UInt8) (aNewAdress >> 8));

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie basse de la taille
	    this->write(i + kSizeLowPos, (UInt8) aSize);

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la partie haute de la taille
	    this->write(i + kSizeHighPos, (UInt8) (aSize >> 8));

	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    //On enregistre la fin des enregistrement
	    this->write(i + kRecordSize, 0x00);

	    return true;
	    }
	//Table corompue !!
	else
	    {
	    return false;
	    }

	}
    else
	{
	return false;
	}
    }

/*
 * Charge les valeurs du objet reconnu par son ID
 * UInt16 aId : Id unique d'un objet.
 * UInt8 aDataTab[] : tableau pour récupérer les données
 *
 * retour : true si on a bien lu ! false si l'id n'existe pas
 */
bool mEEPROM::load(UInt16 aId, UInt8 aDataTab[])
    {

    UInt16 aId_ee = 0;
    UInt16 i = 0;
    bool aHasNext = false;
    bool aIdFound = false;

    UInt16 aLastAdr = 0;
    UInt16 aLastSize = 0;

    //Lecture de la table pour vérifier si l'ID existe. Sinon on ne fait rien
    // L'Open de l'EEPROM a eu une erreur
    if (this->aStatus != 0)
	{
	return false;
	}
    //On attend que l'EEPROM soit prete
    else if (!this->ackPolling())
	{
	return false;
	}

    aHasNext = true;
    aIdFound = false;

    //On parcours tout l'enregistrement et on vérifie aussi si l'enregistrement exite deja
    for (i = kTABLE_BASE_ADR; i < kTABLE_SIZE && aHasNext && !aIdFound; i +=
	    kRecordSize)
	{
	//lecture des tailles
	aId_ee = this->read(i + kIdLowPos);
	aId_ee |= (this->read(i + kIdHighPos) << 8);

	//Lecture de l'addresse
	aLastAdr = this->read(i + kAdrLowPos);
	aLastAdr |= (this->read(i + kAdrHighPos) << 8);

	//Lecture de la taille
	aLastSize = this->read(i + kSizeLowPos);
	aLastSize |= (this->read(i + kSizeHighPos) << 8);

	//Verification si l'adresse existe déja
	if (aId_ee == aId)
	    {
	    aIdFound = true;
	    }

	//Test si on arrive a la fin
	if (this->read(i + kRecordSize) == 0)
	    {
	    aHasNext = false;
	    }
	}

    //On a trouvé l'enregistrement avec l'adresse dans aLastAdr et la taille dans aLastSize
    if (aIdFound == true)
	{
	for (i = 0; i < aLastSize; i++)
	    {
	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    aDataTab[i] = this->read(aLastAdr + i);
	    }
	return true;
	}
    else
	{
	return false;
	}

    }

/*
 * Sauvegarde les valeurs du objet reconnu par son ID
 * UInt16 aId : Id unique d'un objet.
 * UInt8 aDataTab[] : tableau pour enregistrer les données
 *
 * retour : true si on a bien écrit ! false si l'id n'existe pas
 */
bool mEEPROM::store(UInt16 aId, UInt8 aDataTab[])
    {

    UInt16 aId_ee = 0;
    UInt16 i = 0;
    bool aHasNext = false;
    bool aIdFound = false;

    UInt16 aLastAdr = 0;
    UInt16 aLastSize = 0;

    // L'Open de l'EEPROM a eu une erreur
    if (this->aStatus != 0)
	{
	return false;
	}
    //Lecture de la table pour vérifier si l'ID existe. Sinon on ne fait rien

    //On attend que l'EEPROM soit prete
    else if (!this->ackPolling())
	{
	return false;
	}

    aHasNext = true;
    aIdFound = false;

    //On parcours tout l'enregistrement et on vérifie aussi si l'enregistrement exite deja
    for (i = kTABLE_BASE_ADR; i < kTABLE_SIZE && aHasNext && !aIdFound; i +=
	    kRecordSize)
	{
	//lecture des tailles
	aId_ee = this->read(i + kIdLowPos);
	aId_ee |= (this->read(i + kIdHighPos) << 8);

	//Lecture de l'addresse
	aLastAdr = this->read(i + kAdrLowPos);
	aLastAdr |= (this->read(i + kAdrHighPos) << 8);

	//Lecture de la taille
	aLastSize = this->read(i + kSizeLowPos);
	aLastSize |= (this->read(i + kSizeHighPos) << 8);

	//Verification si l'adresse existe déja
	if (aId_ee == aId)
	    {
	    aIdFound = true;
	    }

	//Test si on arrive a la fin
	if (this->read(i + kRecordSize) == 0)
	    {
	    aHasNext = false;
	    }
	}

    //On a trouvé l'enregistrement avec l'adresse dans aLastAdr et la taille dans aLastSize
    if (aIdFound == true)
	{
	for (i = 0; i < aLastSize; i++)
	    {
	    //On attend que l'EEPROM soit prete
	    if (!this->ackPolling())
		{
		return false;
		}
	    this->write(aLastAdr + i, aDataTab[i]);
	    }
	return true;
	}
    else
	{
	return false;
	}

    }

/**
 * Initialise la table d'adresses avec le premier byte a zero
 */
void mEEPROM::initIdTable()
    {
    this->i2c_1->enable();
    if (!this->ackPolling())
	{
	//Pas d'initialisation possible
	this->aStatus = 2;
	return;
	}
    this->write(kTABLE_BASE_ADR, 0x00);
    }

/**
 * Ecriture d'un byte dans l'EEPROM
 * address : Adresse mémoire sur 16 bits (64k)
 * value : Valeur à affecter sur 8 bits
 */
bool mEEPROM::write(UInt16 address, UInt8 value)
    {

    unsigned char aAdr_hi;
    unsigned char aAdr_lo;

    aAdr_hi = address >> 8;                    // calculate high byte
    aAdr_lo = address & 0xFF;                  // and low byte of address

//Config de l'adress du slave
    this->i2c_1->setSlaveAddr(this->moduleAddress);
    this->i2c_1->setWriteMode();

//Attente que le BUS soit libre
    while (this->i2c_1->getStatusFlag(kBUSY) == true)
	;

//Condition de start
    this->i2c_1->start();

//Attente de la fin de la condition de start
    while (this->i2c_1->getStatusFlag(kTXIFG) == false)
	;

//écriture du permier byte à transmettre
    this->i2c_1->write(aAdr_hi);

//Attente de l'ack de l'adresse slave
    while (this->i2c_1->getStatusFlag(kSTT) == true)
	;

//Check si l'on a recu un ACK
    if (this->i2c_1->getStatusFlag(kNACK) == false)
	{
	//On attent que l'on transmette le byte suivant
	while (this->i2c_1->getStatusFlag(kTXIFG) == false)
	    ;

	//On prépare le nouveau
	this->i2c_1->write(aAdr_lo);

	//On attent que la fin
	while (this->i2c_1->getStatusFlag(kTXIFG) == true)
	    ;

	//Check si l'on a recu un ACK
	if (this->i2c_1->getStatusFlag(kNACK) == false)
	    {
	    //On attent que l'on transmette le byte suivant
	    while (this->i2c_1->getStatusFlag(kTXIFG) == false)
		;
	    //On prépare le nouveau
	    this->i2c_1->write(value);

	    //On attent que la fin
	    while (this->i2c_1->getStatusFlag(kTXIFG) == true)
		;

	    //Check si l'on a recu un ACK
	    if (this->i2c_1->getStatusFlag(kNACK) == false)
		{
		//On attent que l'on transmette le byte suivant
		while (this->i2c_1->getStatusFlag(kTXIFG) == false)
		    ;

		UCB1IFG &= ~UCTXIFG;
		this->i2c_1->stop();

		//Check si l'on a recu un ACK
		if (this->i2c_1->getStatusFlag(kNACK) == false)
		    {
		    while (this->i2c_1->getStatusFlag(kSTP) == true)
			;
		    return true;
		    }
		else
		    {
		    this->i2c_1->stop();
		    while (this->i2c_1->getStatusFlag(kSTP) == true)
			;
		    return false;
		    }

		}
	    else
		{
		this->i2c_1->stop();
		while (this->i2c_1->getStatusFlag(kSTP) == true)
		    ;
		return false;
		}
	    }
	else
	    {
	    this->i2c_1->stop();
	    while (this->i2c_1->getStatusFlag(kSTP) == true)
		;
	    return false;
	    }
	}
    else
	{
	this->i2c_1->stop();
	while (this->i2c_1->getStatusFlag(kSTP) == true)
	    ;
	return false;
	}

    }

/**
 * Lecteur d'un byte dans l'EEPROM
 * address : Adresse mémoire sur 16 bits (64k)
 * retour : Valeur lue
 */
char mEEPROM::read(UInt16 address)
    {

    unsigned char aAdr_hi;
    unsigned char aAdr_lo;

    aAdr_hi = address >> 8;                    // calculate high byte
    aAdr_lo = address & 0xFF;                  // and low byte of address

//Config de l'adress du slave
    this->i2c_1->setSlaveAddr(this->moduleAddress);
    this->i2c_1->setWriteMode();

//Attente que le BUS soit libre
    while (this->i2c_1->getStatusFlag(kBUSY) == true)
	;

//Condition de start
    this->i2c_1->start();

//Attente de la fin de la condition de start
    while (this->i2c_1->getStatusFlag(kTXIFG) == false)
	;

//écriture du permier byte à transmettre
    this->i2c_1->write(aAdr_hi);

//Attente de l'ack de l'adresse slave
    while (this->i2c_1->getStatusFlag(kSTT) == true)
	;

//Check si l'on a recu un ACK
    if (this->i2c_1->getStatusFlag(kNACK) == false)
	{
	//On attent que l'on transmette le byte suivant
	while (this->i2c_1->getStatusFlag(kTXIFG) == false)
	    ;

	//On prépare le nouveau
	this->i2c_1->write(aAdr_lo);

	//On attent que la fin
	while (this->i2c_1->getStatusFlag(kTXIFG) == true)
	    ;

	//Check si l'on a recu un ACK
	if (this->i2c_1->getStatusFlag(kNACK) == false)
	    {
	    //On attent que l'on transmette le byte suivant
	    while (this->i2c_1->getStatusFlag(kTXIFG) == false)
		;

	    //On se met en mode lecture
	    this->i2c_1->setReadMode();
	    UCB1IFG &= ~UCTXIFG;
	    //REPEATED START
	    this->i2c_1->start();

	    //Attente de l'ack de l'adresse slave
	    while (this->i2c_1->getStatusFlag(kSTT) == true)
		;
	    this->i2c_1->stop();

	    //On attend la fin de la lecture
	    while (this->i2c_1->getStatusFlag(kRXIFG) == false)
		;

	    return this->i2c_1->read();

	    }
	else
	    {
	    this->i2c_1->stop();
	    while (this->i2c_1->getStatusFlag(kSTP) == true)
		;
	    return 255;
	    }
	}
    else
	{
	this->i2c_1->stop();
	while (this->i2c_1->getStatusFlag(kSTP) == true)
	    ;
	return 255;
	}
    }

/**
 * Vérification que le cycle d'écriture est bien terminé.
 * Sinon l'EEPROM ne répond pas
 */
bool mEEPROM::ackPolling()
    {
    mDelay delayTimeout;

    if (delayTimeout.disponibility == false)
	{
	return false;
	}

    while (this->i2c_1->getStatusFlag(kBUSY) == true)
	;

    //1s de timeout
    delayTimeout.startDelayMS(1000);

    do
	{
	UCB1STAT = 0x00;                        // clear I2C interrupt flags
	//Config de l'adress du slave
	this->i2c_1->setSlaveAddr(this->moduleAddress);
	this->i2c_1->setWriteMode();// I2CTRX=1 => Transmit Mode (R/W bit = 0)

	UCB1CTL1 &= ~UCTXSTT;
	this->i2c_1->start();                    // start condition is generated
	while (this->i2c_1->getStatusFlag(kSTT) == true) // wait till I2CSTT bit was cleared
	    {
	    if (this->i2c_1->getStatusFlag(kNACK) == false) // Break out if ACK received
		break;
	    }
	this->i2c_1->stop();                // stop condition is generated after
	while (this->i2c_1->getStatusFlag(kSTP) == true)
	    ; // wait till stop bit is reset
	// Software delay
	__delay_cycles(500);
	if (delayTimeout.isDone())
	    {
	    return false;
	    }
	}
    while (this->i2c_1->getStatusFlag(kNACK) == true);

    return true;
    }

