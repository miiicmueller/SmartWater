#ifndef M_U_S_B_H
#define M_U_S_B_H

#include <string>
#include <assert.h>

#include "Module.h"

class mUSB : public Module
{
public:
	bool getCommand(int* cmd, char* values);

	void sendReply(int* values, int valNum);

	bool isConnected();

};
#endif
