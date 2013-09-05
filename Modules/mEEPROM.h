#ifndef M_EEPROM_H
#define M_EEPROM_H

#include <string>
#include <assert.h>
#include "Interfaces/iI2C.h"

#include "Modules/Module.h"
#include "Def/def.h"

//ID de base pour les parametres
#define kMODE_BASE_ID 		0x0100
#define kMONTHSLIM_BASE_ID 	0x0200
#define kUNITNAME_BASE_ID 	0x0300
#define kTEMPOFFSET_BASE_ID 	0x0400
#define kMEASSTAT_BASE_ID 	0x0500
#define kMPUSER_BASE_ID 	0x0600
#define kMPADMIN_BASE_ID 	0x0700
#define kAVAIL_BASE_ID 		0x0800
#define kALARMNUM_BASE_ID 	0x0900
#define kCOMPTEUR_BASE_ID 	0x0A00
#define kSIMCARD_BASE_ID 	0x0B00
#define kFREE_BASE_ID 		0xFF01

class mEEPROM: public Module
    {
private:
    UInt8 moduleAddress;
    iI2C *i2c_1;

    UInt16 availableData;
    UInt16 usedBytes;
    UInt8 aStatus;

    bool write(UInt16 address, UInt8 value);
    char read(UInt16 address);

public:
    mEEPROM(UInt16 moduleAddress, iI2C *i2cBus);
    ~mEEPROM();
    void initIdTable();
    UInt8 getStatus();
    bool malloc(UInt16 aId, UInt16 size);
    bool free(UInt16 aId);
    bool load(UInt16 aId, UInt8 aDataTab[]);
    bool store(UInt16 aId, UInt8 aDataTab[]);
    void mOpen();
    void mClose();
    void mSetup();
    bool ackPolling();
    bool ackPollingWr(UInt8 aAdr_hi);
    };
#endif
