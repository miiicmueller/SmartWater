#include <string.h>
#include <assert.h>

#include "Interfaces/iUSB.h"

#include "mUSB.h"

mUSB::mUSB(volatile BYTE *bCDCDataReceived_event) {
	this->usbPort = new iUSB(bCDCDataReceived_event);
}

mUSB::~mUSB() {

}

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

void mUSB::sendReply(char* aMessage) {
	this->usbPort->sendFullFrame(aMessage);
}

bool mUSB::isConnected() {
	switch (this->usbPort->getConnectionState()) {
	case kStateActive:
		return true;
	default:
		return false;
	}
}

void mUSB::mOpen() {

}

void mUSB::mClose() {

}

void mUSB::mSetup() {

}
