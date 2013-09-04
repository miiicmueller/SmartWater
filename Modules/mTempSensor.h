#ifndef M_TEMP_SENSOR_H
#define M_TEMP_SENSOR_H

#include <string>
#include <assert.h>
#include "Interfaces/iI2C.h"

#include "Module.h"

typedef enum
    {
    kTemperature = 0x00,
    kConfiguration = 0x01,
    kTempLow = 0x02,
    kTempHigh = 0x03
    } mTempSensorRegEnum;

class mTempSensor: public Module
    {
private:
    UInt8 sensorAddress;
    UInt8 aStatus;
    iI2C *i2c_1;
public:
    mTempSensor(char sensorAddress, iI2C *i2cBus);
    ~mTempSensor();
    UInt16 readTemp();
    UInt8 getStatus();
    bool configSensor(mTempSensorRegEnum aRegister, char aValue);
    void mOpen();
    void mClose();
    void mSetup();

    };
#endif
