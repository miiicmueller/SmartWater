#ifndef M_R_T_C_H
#define M_R_T_C_H

#include <string>
#include <assert.h>

#include "Module.h"

class mRTC : public Module
{
public:
	void readDate(int year, char month, char date);

	void readTime(char hour, char minute, char second);

	void setDate(int year, char month, char date);

	void setHour(char hour, char minute, char second);

	void setAlarm(char hour, char minute, char second);

};
#endif
