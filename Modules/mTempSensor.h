#ifndef M_TEMP_SENSOR_H
#define M_TEMP_SENSOR_H

#include <string>
#include <assert.h>

#include "Module.h"

class mTempSensor : public Module
{
private:
	char sensorAddress;

public:
	bool isSleeping;


public:
	int readTemp();
	int sleep();

};
#endif
