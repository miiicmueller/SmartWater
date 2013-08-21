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
#include <string.h>

#include "Tools/tCommandesAT.h"
#include "Tools/tMode.h"
#include "Tools/tMonthsLimits.h"
#include "Tools/tTemperatureOffset.h"

#include "USB_API/USB_Common/types.h"

#include "Gestionnaires/gInput.h"
#include "Gestionnaires/gCompute.h"
#include "Gestionnaires/gOutput.h"
#include "Gestionnaires/gSleep.h"
#include "Gestionnaires/gTerminal.h"

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

unsigned int temperature;
float temp = 0.0;
char tempToSend[MAX_BUFFERSIZE] = "";

/*
 * ======== main ========
 */
void main(void) {

	char i;

	UInt32 valeurCompteur = 0;
	// Important pour la basse consommation
	iDIO::InitAllPort();

	mCpu::configFrequency();

	__bis_SR_register(GIE);

	gInput theGInput;
	gCompute theGCompute(&theGInput);
	gOutput theGOutput(&theGCompute);

	mDelay::mSetup();
	mDelay::mOpen();

	iI2C iI2C_1(k100kHz, kUSCI_B1, kMaster, 0x01A5);
	mEEPROM eeprom(0x50, &iI2C_1);
	eeprom.mOpen();
	//iUART uart(kUSCI_A1, kLSBFirst, k1StBits, kEven, k7bits, k300);

	mCompteur monCompteur(kMeter1,&eeprom);
	monCompteur.mOpen();
	valeurCompteur = monCompteur.mRead();

	while (1) {
	}
}

