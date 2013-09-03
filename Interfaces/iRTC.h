#ifndef I_R_T_C_H
#define I_R_T_C_H

#include <string>
#include <assert.h>
#include <msp430f5519.h>

#include "Interface.h"

class iRTC: public Interface {
private:
	char aMinuteAlarme;
	char aDeltaMinuteAlarme;
	static iRTC* RTC_A ;
	void wakeUpInterrupt();
	bool write(UInt8 aData);
	UInt8 read();

	friend void RTC_A(void);
public:
	iRTC();
	~iRTC();
	void setAlarm(char aHour,char aMinute);
	void resetAlarm();
	void readDate(int *aYear, char *aMonth, char *aDay, char *aDayOfWeek);
	void readTime(char *aHour, char *aMinute, char *aSecond);
	void setDate(int aYear, char aMonth, char aDay, char aDayOfWeek);
	void setHour(char aHour, char aMinute, char aSecond);
	void calibration(int aTemperature);
	void enableRTC();
	void disableRTC();

};
#endif
