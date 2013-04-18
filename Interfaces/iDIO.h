#ifndef __IDIO__
#define __IDIO__

#include <string>
#include <assert.h>

#include "Interface.h"
#include <msp430.h>

typedef enum {
	kPort_1 = __MSP430_BASEADDRESS_PORT1_R__,
	kPort_2 = __MSP430_BASEADDRESS_PORT2_R__,
	kPort_3 = __MSP430_BASEADDRESS_PORT3_R__,
	kPort_4 = __MSP430_BASEADDRESS_PORT4_R__,
	kPort_5 = __MSP430_BASEADDRESS_PORT5_R__,
	kPort_6 = __MSP430_BASEADDRESS_PORT6_R__,
	kPort_7 = __MSP430_BASEADDRESS_PORT7_R__,
	kPort_8 = __MSP430_BASEADDRESS_PORT8_R__
} iDIOPortAddressEnum;

class iDIO: public Interface {
private:
	char* thePortAddress;

	char theMask;

public:
	iDIO(char* aPortAddress, char aMask);

	void SetPortDirection();

	virtual bool write(char aData);
	virtual char read();

};
#endif
