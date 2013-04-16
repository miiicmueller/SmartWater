#ifndef I_R_T_C_H
#define I_R_T_C_H

#include <string>
#include <assert.h>

#include "Interface.h"

class iRTC : public Interface
{
private:
	static void wakeUpInterrupt();

public:
	void setAlarm(char day, char dayOW, char hour, char min);

	void calibration();

};
#endif
