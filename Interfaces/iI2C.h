#ifndef I_I2_C_H
#define I_I2_C_H

#include <string>
#include <assert.h>

#include "Interface.h"
#include <msp430f5519.h>

#define I2C_PORT_SEL_B0  P3SEL
#define I2C_PORT_SEL_B1  P4SEL
#define I2C_PORT_OUT_B0  P3OUT
#define I2C_PORT_REN_B0  P3REN
#define I2C_PORT_OUT_B1  P4OUT
#define I2C_PORT_REN_B1  P4REN
#define I2C_PORT_DIR_B0  P3DIR
#define I2C_PORT_DIR_B1  P4DIR
#define SDA_PIN_B0       BIT0                  // UCB0SDA pin
#define SCL_PIN_B0       BIT1                  // UCB0SCL pin
#define SDA_PIN_B1       BIT1                  // UCB0SDA pin
#define SCL_PIN_B1       BIT2					// UCB0SCL pin
typedef enum {
	kUSCI_B0 = 0, kUSCI_B1 = 1
} iI2CPortEnum;

typedef enum {
	k100kHz, k400kHz
} iI2CSpeedEnum;

typedef enum {

} iI2CStatusFlagEnum;

typedef enum {
	kMaster, kSlave
} iI2CModesEnum;

typedef enum {
	kTXIFG, kSTT, kNACK, kBUSY, kSTP,kRXIFG
} iI2CFlagEnum;

class iI2C: public Interface {
private:
	iI2CPortEnum i2cPort;
	bool isEnabled;
	//Variable global pour g�rer l'affectations des
	// interruptions
	static iI2C* USCI_B0;
	static iI2C* USCI_B1;

public:
	iI2C(iI2CSpeedEnum i2cSpeed, iI2CPortEnum i2cPort, iI2CModesEnum i2cMode,
			char i2cAddress);
	~iI2C();
	void config(iI2CSpeedEnum i2cSpeed, iI2CModesEnum i2cMode, char i2cAddress);
	void start();
	void stop();
	void reStart();
	void setWriteMode();
	void setReadMode();
	void enable();
	void disable();
	void setSlaveAddr(char aSlaveAddr);
	bool write(UInt8 aData);
	UInt8 read();
	bool getStatusFlag(iI2CFlagEnum aFlag);

};
#endif
