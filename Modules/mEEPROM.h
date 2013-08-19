#ifndef M_EEPROM_H
#define M_EEPROM_H

#include <string>
#include <assert.h>
#include "Interfaces/iI2C.h"

#include "Modules/Module.h"
#include "Def/def.h"

class mEEPROM: public Module {
private:
	UInt8 moduleAddress;
	iI2C *i2c_1 ;

	UInt16 availableData;
	UInt16 usedBytes;

	bool write(UInt16 address, UInt8 value);
	char read(UInt16 address);

public:
	mEEPROM(UInt16 moduleAddress,iI2C *i2cBus);
	~mEEPROM();
	void initIdTable();
	bool malloc(UInt16 aId,UInt16 size);
	bool free(UInt16 aId);
	bool load(UInt16 aId,UInt8 aDataTab[]);
	bool store(UInt16 aId,UInt8 aDataTab[]);
	void mOpen();
	void mClose();
	void mSetup();
	void ackPolling();
};
#endif
