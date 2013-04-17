#ifndef I_U_A_R_T_H
#define I_U_A_R_T_H

#include <string>
#include <assert.h>
#include "../Def/enum_types.h"

#include "Interface.h"

class iUART: public Interface {
private:
	UARTPortEnum serialPort;

public:
	iUART(UARTPortEnum aPort);
	void config(UARTSendModeEnum aSendMode);
	bool getStatusFlag(UARTStatusFlag aStatFlag);
	void enable();
	void disable();

};
#endif
