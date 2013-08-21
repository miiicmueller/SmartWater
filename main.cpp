#include <msp430.h>

#include "Interfaces/iDIO.h"
#include "Interfaces/iI2C.h"

#include "Modules/mGSM.h"
#include "Modules/mCpu.h"
#include "Modules/mEEPROM.h"
#include "Modules/mCompteur.h"
#include "Modules/mTempSensor.h"
#include "Modules/mUSB.h"
#include "Modules/mRTC.h"
#include "Modules/mDelay.h"
#include "Def/def.h"

#include "Tools/tCommandesAT.h"
#include "Tools/tMode.h"
#include "Tools/tMonthsLimits.h"
#include "Tools/tTemperatureOffset.h"

#include "USB_API/USB_Common/types.h"

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

//OBLIGATOIRE POUR L'USB
volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation

/*
 * ======== main ========
 */
void main(void) {

	char sec = 0;
	char min = 0;
	char hr = 0;
	UInt8 aDataTab[10] = { 0 };

// Important pour la basse consommation
	iDIO::InitAllPort();

	mCpu::configFrequency();

	__bis_SR_register(GIE);

	iI2C iI2C_1(k100kHz, kUSCI_B1, kMaster, 0x01A5);

//Init de l'EEPROM
	mEEPROM test(0x50, &iI2C_1);
	test.mOpen();

	tTemperatureOffset tOffset(&test, 1);

	tOffset.aOffset.aFloatVal = 10.546;

	tOffset.save();

	tOffset.aOffset.aFloatVal = 11.238;

	tOffset.load();

	while (1) {

	}
}

