#ifndef M_R_T_C_H
#define M_R_T_C_H

#include <string>
#include <assert.h>
#include "Interfaces/iRTC.h"

#include "Module.h"

class mRTC: public Module
    {
private:
    iRTC *iRtc;
public:
    mRTC();
    ~mRTC();
    void mOpen();
    void mClose();
    void mSetup();
    void readDate(int *aYear, char *aMonth, char *aDay, char *aDayOfWeek);
    void readTime(char *aHour, char *aMinute, char *aSecond);
    void setDate(int aYear, char aMonth, char aDay, char aDayOfWeek);
    void setHour(char aHour, char aMinute, char aSecond);
    void setAlarm(char aHour, char aMinute);
    void calibration(int aTemperature);
    };
#endif
