#ifndef M_BATTERY_H
#define M_BATTERY_H

#include <string>
#include <assert.h>

#include "Module.h"

class mBattery : public Module
{
private:
	int batteryValue;


public:
	mBattery();
	bool CheckBattery();

	int GetBatteryValue();

};
#endif
