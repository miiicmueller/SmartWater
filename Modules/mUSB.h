#ifndef M_U_S_B_H
#define M_U_S_B_H

#include <string>
#include <assert.h>
#include "Interfaces/iUSB.h"

#include "Module.h"

class mUSB: public Module {
private:
	iUSB *usbPort ;
	char *serialBuffer;
public:
	mUSB(volatile BYTE *bCDCDataReceived_event);
	~mUSB();
	bool getCommand(int* cmd);
	void sendReply(char* aMessage);
	bool isConnected();

	void mOpen();
	void mClose();
	void mSetup();

};
#endif
