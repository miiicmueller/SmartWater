#include <string>
#include <assert.h>

#include "mEEPROM.h"
#include "Interfaces/iI2C.h"

/**
 * Création d'une EEPROM
 * moduleAddress : Adresse de l'EEPROM
 * i2cBus : Noeud i2c sur lequel il est connecté.
 */
mEEPROM::mEEPROM(char moduleAddress, iI2C *i2cBus) {
	this->moduleAddress = moduleAddress;
	this->i2c_1 = i2cBus;

}

mEEPROM::~mEEPROM() {

}

/**
 * Activation du port I2C
 */
void mEEPROM::mOpen() {
	this->i2c_1->enable();
}

/**
 * Surtout pas de bus i2c->disable !!
 * Plusieurs autres composant peuvent être sur le bus !
 */
void mEEPROM::mClose() {
}

/**
 * Inutilisée
 */
void mEEPROM::mSetup() {
//Noting to do pour l'instant
}

/**
 * Ecriture d'un byte dans l'EEPROM
 * address : Adresse mémoire sur 16 bits (64k)
 * value : Valeur à affecter sur 8 bits
 */
bool mEEPROM::write(int address, char value) {

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
	if (this->i2c_1->getStatusFlag(kNACK) == false) {
		//On attent que l'on transmette le byte suivant
		while (this->i2c_1->getStatusFlag(kTXIFG) == false)
			;

		//On prépare le nouveau
		this->i2c_1->write(aAdr_lo);

		//On attent que la fin
		while (this->i2c_1->getStatusFlag(kTXIFG) == true)
			;

		//Check si l'on a recu un ACK
		if (this->i2c_1->getStatusFlag(kNACK) == false) {
			//On attent que l'on transmette le byte suivant
			while (this->i2c_1->getStatusFlag(kTXIFG) == false)
				;
			//On prépare le nouveau
			this->i2c_1->write(value);

			//On attent que la fin
			while (this->i2c_1->getStatusFlag(kTXIFG) == true)
				;

			//Check si l'on a recu un ACK
			if (this->i2c_1->getStatusFlag(kNACK) == false) {
				//On attent que l'on transmette le byte suivant
				while (this->i2c_1->getStatusFlag(kTXIFG) == false)
					;

				UCB1IFG &= ~UCTXIFG;
				this->i2c_1->stop();

				//Check si l'on a recu un ACK
				if (this->i2c_1->getStatusFlag(kNACK) == false) {
					while (this->i2c_1->getStatusFlag(kSTP) == true)
						;
					return true;
				} else {
					this->i2c_1->stop();
					while (this->i2c_1->getStatusFlag(kSTP) == true)
						;
					return false;
				}

			} else {
				this->i2c_1->stop();
				while (this->i2c_1->getStatusFlag(kSTP) == true)
					;
				return false;
			}
		} else {
			this->i2c_1->stop();
			while (this->i2c_1->getStatusFlag(kSTP) == true)
				;
			return false;
		}
	} else {
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
char mEEPROM::read(int address) {

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
	if (this->i2c_1->getStatusFlag(kNACK) == false) {
		//On attent que l'on transmette le byte suivant
		while (this->i2c_1->getStatusFlag(kTXIFG) == false)
			;

		//On prépare le nouveau
		this->i2c_1->write(aAdr_lo);

		//On attent que la fin
		while (this->i2c_1->getStatusFlag(kTXIFG) == true)
			;

		//Check si l'on a recu un ACK
		if (this->i2c_1->getStatusFlag(kNACK) == false) {
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

		} else {
			this->i2c_1->stop();
			while (this->i2c_1->getStatusFlag(kSTP) == true)
				;
			return 0;
		}
	} else {
		this->i2c_1->stop();
		while (this->i2c_1->getStatusFlag(kSTP) == true)
			;
		return 0;
	}
}

/**
 * Vérification que le cycle d'écriture est bien terminé.
 * Sinon l'EEPROM ne répond pas
 */
void mEEPROM::ackPolling() {
	while (this->i2c_1->getStatusFlag(kBUSY) == true)
		;
	do {
		UCB1STAT = 0x00;                        // clear I2C interrupt flags
		this->i2c_1->setWriteMode();  // I2CTRX=1 => Transmit Mode (R/W bit = 0)
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
		__delay_cycles(500);                    // Software delay
	} while (this->i2c_1->getStatusFlag(kNACK) == true);
}

