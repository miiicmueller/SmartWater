#ifndef I_I2_C_H
#define I_I2_C_H

#include <string>
#include <assert.h>

#include "Interface.h"

class iI2C : public Interface
{
public:
	boolean config(char i2cSpeed, char i2cPort);

	void start();

	void stop();

	void reStart();

	void setWriteMode();

	void setReadMode();

};
#endif
