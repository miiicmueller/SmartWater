#include <string>
#include <assert.h>

#include "mTempSensor.h"

mTempSensor::mTempSensor(char sensorAddress, iI2C *i2cBus) {
	this->sensorAddress = sensorAddress;
	this->i2c_1 = i2cBus;
}
mTempSensor::~mTempSensor() {

}

void mTempSensor::mOpen() {
	this->i2c_1->enable();
}
void mTempSensor::mClose() {

}
void mTempSensor::mSetup() {

}

int mTempSensor::readTemp() {

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
		return (int) tempLSB + ((int) tempMSB << 8);

	} else {
		this->i2c_1->stop();
		while (this->i2c_1->getStatusFlag(kSTP) == true)
			;
		return 0;
	}

}

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
	}
}
