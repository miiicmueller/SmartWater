#ifndef M_E_E_P_R_O_M_H
#define M_E_E_P_R_O_M_H

#include <string>
#include <assert.h>

#include "Module.h"

class mEEPROM : public Module
{
private:
	char moduleAddress;


public:
	boolean write(int address, char value);

	char read(int address);

};
#endif
