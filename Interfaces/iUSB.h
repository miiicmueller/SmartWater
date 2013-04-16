#ifndef I_U_S_B_H
#define I_U_S_B_H

#include <string>
#include <assert.h>

#include "Interface.h"
#include "kStatusEnum.h"

class iUSB : public Interface
{
private:
	char[MAX_BUFFERSIZE] usbSerialBuffer;


public:
	boolean getFullFrame(char FrameBuffer[][]);

	void sendFullFrame(char FrameBuffer[][]);

	kStatusEnum getStatus();

	void initUSB();

	char getConnectionState();

};
#endif
