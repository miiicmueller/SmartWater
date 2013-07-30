#include <string.h>
#include <assert.h>

#include "Interfaces/iUSB.h"

#include "mUSB.h"

/**
 * Constructeur de base
 * *bCDCDataReceived_event : Variable globale changée dans usbEventHandling.c !!!!
 * A ne pas oublier !!
 */
mUSB::mUSB(volatile BYTE *bCDCDataReceived_event) {
	this->usbPort = new iUSB(bCDCDataReceived_event);
}

mUSB::~mUSB() {

}

/**
 * Test si l'on a recu une commande : A déterminer selon le protocole
 */
//TODO : Faire le protocole de communication. Ce code est à titre d'exemple
bool mUSB::getCommand(int* cmd) {
	if (this->usbPort->isDataAvailable() == true) {
		//Some data is in the buffer; begin receiving a
		char command[MAX_BUFFERSIZE]; //The entire input string from the last 'return'
		if (this->usbPort->getFullFrame(command)) { //Has the user pressed return yet?
			if (!(strcmp(command, "cmd1"))) { //Compare to string #1, and respond
				*cmd = 1;
				return true;
			} else if (!(strcmp(command, "cmd2"))) { //Compare to string #2, and respond
				*cmd = 2;
				return true;
			} else if (!(strcmp(command, "cmd3"))) { //Compare to string #2, and respond
				*cmd = 3;
				return true;
			} else {
				*cmd = 0;
				return true;
			}

		} else {
			return false;
		}
	} else {
		return false;
	}
}

/**
 * Envoie d'une string sur l'USB
 * aMessage : Message à transmettre
 */
void mUSB::sendReply(char* aMessage) {
	this->usbPort->sendFullFrame(aMessage);
}

/**
 * Test si l'USB est prêt ou non
 */
bool mUSB::isConnected() {
	switch (this->usbPort->getConnectionState()) {
	case kStateActive:
		return true;
	default:
		return false;
	}
}

/**
 * Non utilisée
 */
void mUSB::mOpen() {

}

/**
 * Non utilisée
 */
void mUSB::mClose() {

}

/**
 * Non utilisée
 */
void mUSB::mSetup() {

}
