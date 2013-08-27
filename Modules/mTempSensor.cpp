#include <string>
#include <assert.h>

#include "mTempSensor.h"

/**
 * Création d'un senseur de temperature
 * sensorAddress : Adresse du capteur
 * i2cBus : Noeud i2c sur lequel il est connecté.
 */
mTempSensor::mTempSensor(char sensorAddress, iI2C *i2cBus) {
	this->sensorAddress = sensorAddress;
	this->aStatus = 0;
	this->i2c_1 = i2cBus;
}
mTempSensor::~mTempSensor() {

}

/**
 * Activation du bus i2c
 */
void mTempSensor::mOpen() {
	this->i2c_1->enable();
}

/**
 * Surtout pas de bus i2c->disable !!
 * Plusieurs autres composant peuvent être sur le bus !
 */
void mTempSensor::mClose() {

}

/**
 * Inutilisée
 */
void mTempSensor::mSetup() {

}

/**
 * Permet de tester l'état du module
 * retour : valeur du status
 */
UInt8 mTempSensor::getStatus() {
	return this->aStatus;
}

/**
 * Aquisition de la température
 * Donne un entier sur 16 bits (12bits)
 * POur avoir la température en degrée : Temp = (retour >> 4 )*0.0625
 */
UInt16 mTempSensor::readTemp() {

	char tempLSB = 0;
	char tempMSB = 0;

//Config de l'adress du slave
	this->i2c_1->setSlaveAddr(this->sensorAddress);
	this->i2c_1->setWriteMode();

//Attente que le BUS soit libre
	while (this->i2c_1->getStatusFlag(kBUSY) == true) {
		this->i2c_1->stop();
	}

//Condition de start
	this->i2c_1->start();

//Attente de la fin de la condition de start
	while (this->i2c_1->getStatusFlag(kTXIFG) == false)
		;

//écriture du permier byte à transmettre "Pointer Register"
	this->i2c_1->write(kTemperature);

//Attente de l'ack de l'adresse slave
	while (this->i2c_1->getStatusFlag(kSTT) == true)
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

		//On attend la fin de la lecture
		while (this->i2c_1->getStatusFlag(kRXIFG) == false)
			;
		//Lecture du MSB
		tempMSB = this->i2c_1->read();

		this->i2c_1->stop();

		//On attend la fin de la lecture
		while (this->i2c_1->getStatusFlag(kRXIFG) == false)
			;
		//Lecture du MSB
		tempLSB = this->i2c_1->read();

		while (this->i2c_1->getStatusFlag(kSTP) == true)
			;
		// Comm error
		this->aStatus = 0;
		return (int) tempLSB + ((int) tempMSB << 8);

	} else {
		this->i2c_1->stop();
		while (this->i2c_1->getStatusFlag(kSTP) == true)
			;
		// Le capteur ne répond pas
		this->aStatus = 1;
		return 0;
	}

}

/**
 * Permet d'acceder à un registre du capteur pour sa configuration
 * aRegister : Registre à configurer
 * aValue : Valeur à écrire dans le registre
 */
bool mTempSensor::configSensor(mTempSensorRegEnum aRegister, char aValue) {
//Config de l'adress du slave
	this->i2c_1->setSlaveAddr(this->sensorAddress);
	this->i2c_1->setWriteMode();

//Attente que le BUS soit libre
	while (this->i2c_1->getStatusFlag(kBUSY) == true) {
		this->i2c_1->stop();
	}

//Condition de start
	this->i2c_1->start();

//Attente de la fin de la condition de start
	while (this->i2c_1->getStatusFlag(kTXIFG) == false)
		;

//écriture du permier byte à transmettre "Pointer Register"
	this->i2c_1->write(aRegister);

//Attente de l'ack de l'adresse slave
	while (this->i2c_1->getStatusFlag(kSTT) == true)
		;

//Check si l'on a recu un ACK
	if (this->i2c_1->getStatusFlag(kNACK) == false) {
		//On attent que l'on transmette le byte suivant
		while (this->i2c_1->getStatusFlag(kTXIFG) == false)
			;
		//écriture
		this->i2c_1->write(aValue);
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
				// Comm error
				this->aStatus = 0;
				return true;
			} else {
				this->i2c_1->stop();
				while (this->i2c_1->getStatusFlag(kSTP) == true)
					;
				// Comm error
				this->aStatus = 2;
				return false;
			}
		} else {
			this->i2c_1->stop();
			while (this->i2c_1->getStatusFlag(kSTP) == true)
				;
			// Comm error
			this->aStatus = 2;
			return false;
		}
	} else {
		// Le capteur ne répond pas
		this->aStatus = 1;
		return false;
	}
}
