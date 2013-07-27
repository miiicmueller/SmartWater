#include <msp430.h>

#include "Interfaces/iDIO.h"
#include "Interfaces/iUART.h"
#include "Interfaces/iI2C.h"

#include "Modules/mGSM.h"
#include "Modules/mCpu.h"
#include "Modules/mEEPROM.h"
#include "Modules/mTempSensor.h"

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

unsigned int monEssai ;
float temp = 0.0 ;

#ifdef __cplusplus
extern "C" {
#endif


int _system_pre_init(void) {
// turn watchdog off
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	_DINT();
	monEssai = 0 ;
	return (1);
}

#ifdef __cplusplus
}
#endif

//Global flags set by events
volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation


int main(void) {

	int i = 0;
	bool hasSMSRecu = false;

	mCpu::configFrequency();

	__bis_SR_register(GIE);

	//I2Cs
	iI2C iI2C_1(k100kHz, kUSCI_B1, kMaster, 0x01A5);

	mEEPROM DataBase(0x50, &iI2C_1);
	mTempSensor CaptCarte(0x48, &iI2C_1);

	CaptCarte.mOpen();
	CaptCarte.configSensor(kConfiguration,0x60);

	while (1) {

		monEssai = CaptCarte.readTemp();
		temp = (monEssai >> 4 ) * 0.0625;
	}

}
