#ifndef I_U_A_R_T_H
#define I_U_A_R_T_H

#include <string>
#include <assert.h>

#include "Interface.h"

typedef enum {
	k8bits, k9bits
} UARTDataCfgEnum;

typedef enum {
	kLSBFirst, kMSBFirst
} UARTSendModeEnum;

typedef enum {
	kUSCI_A0, kUSCI_A1
} UARTPortEnum;


class iUART: public Interface {
private :
	UARTPortEnum serialPort;

public:
	iUART(UARTPortEnum aPort);
	void config(UARTPortEnum aPort);

};
#endif
