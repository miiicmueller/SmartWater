#ifndef I_U_S_B_H
#define I_U_S_B_H

#include <string>
#include <assert.h>
#include "../Def/def.h"
#include "Interface.h"

class iUSB: public Interface {
private:
	char* usbSerialBuffer;
	static const int MAX_BUFFERSIZE = 100;

public:
	bool getFullFrame(char* FrameBuffer);

	void sendFullFrame(char* FrameBuffer);

	kStatusEnum getStatus();

	void initUSB();

	char getConnectionState();

};
#endif
