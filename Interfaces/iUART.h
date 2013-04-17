#ifndef I_U_A_R_T_H
#define I_U_A_R_T_H

#include <string>
#include <assert.h>
#include "../Def/enum_types.h"

#include "Interface.h"

class iUART: public Interface {
private:
	UARTPortEnum serialPort;
	bool isEnabled;

public:
	iUART(UARTPortEnum aPort, UARTSendModeEnum aSendMode,
			UARTStopBitsEnum aStopBits, UARTPartityEnum aParity,
			UARTDataCfgEnum aDataCfg, int aBaudrate);
	void config(UARTSendModeEnum aSendMode, UARTStopBitsEnum aStopBits,
			UARTPartityEnum aParity, UARTDataCfgEnum aDataCfg, int aBaudrate);
	bool getStatusFlag(UARTStatusFlag aStatFlag);
	void enable();
	void disable();
	char read();
	bool write(char aData);

};
#endif
