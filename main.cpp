#include <msp430.h>
#include "Modules/mGSM.h"
#include "Modules/mCpu.h"
#include "Interfaces/iDIO.h"
#include "Interfaces/iUART.h"
#include "Tools/tCommandesAT.h"

#include <intrinsics.h>
#include <string.h>
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"               //Basic Type declarations
#include "USB_API/USB_Common/usb.h"                 //USB-specific functions
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "usbConstructs.h"

/*
 * main.c
 */

#ifdef __cplusplus
extern "C" {
#endif

int _system_pre_init(void) {
// turn watchdog off
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	_DINT();

	return (1);
}

#ifdef __cplusplus
}
#endif
//void Init_Clock(void);
//void SetVcoreUp(unsigned int level);

//Global flags set by events
volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation

int main(void) {

	char smsReceived[100]; // sms recu
	bool hasSMSRecu = false;

	mCpu::configFrequency();

	__bis_SR_register(GIE);

	//Declaration d'un iUart
	iUART iUart(kUSCI_A0, kLSBFirst, k1StBits, kNone, k8bits, k9600);
	iDIO iDio(0x00, 0x00);
	tCommandesAT tComAt;

	mGSM mGsm(&iDio, &iUart, &tComAt);
	mGsm.mSetup();
	mGsm.mOpen();

	while (1) {
	}
}

