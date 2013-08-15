#include <msp430.h>

#include "Interfaces/iDIO.h"
#include "Interfaces/iI2C.h"

#include "Modules/mGSM.h"
#include "Modules/mCpu.h"
#include "Modules/mEEPROM.h"
#include "Modules/mTempSensor.h"
#include "Modules/mUSB.h"
#include "Modules/mRTC.h"

#include "Tools/tCommandesAT.h"

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

unsigned int temperature;
float temp = 0.0;
char tempToSend[MAX_BUFFERSIZE] = "";

/*
 * ======== main ========
 */
void main(void) {


	// Important pour la basse consommation
	iDIO::InitAllPort();

	mCpu::configFrequency();

	__bis_SR_register(GIE);



	mGSM mGsm;

	mGsm.mOpen();


	__enable_interrupt();    //Enable interrupts globally

	mGsm.sendSMS("Coucou2\rapreCR\napreLF\r\napreCRLF", "+41787526983");

	while (1) {}
}

