#ifndef M_EEPROM_H
#define M_EEPROM_H

#include <string>
#include <assert.h>
#include "Interfaces/iI2C.h"

#include "Modules/Module.h"

class mEEPROM: public Module {
private:
	char moduleAddress;
	iI2C *i2c_1 ;
public:
	mEEPROM(char moduleAddress,iI2C *i2cBus);
	~mEEPROM();
	bool write(int address, char value);
	char read(int address);
	void mOpen();
	void mClose();
	void mSetup();
	void ackPolling();
};
#endif
