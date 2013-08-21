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
#include "Def/def.h"
#include <string.h>

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

	char maString[10] = {'s','a','l','1','2','3','r','r','w', '\0'};
	UInt32 valeurCompteur=0;
	bool retourRRR;
	bool retourRRR2;
	long lavaleur=0;
	long lavaleur2=0;
	// Important pour la basse consommation
	iDIO::InitAllPort();

	mCpu::configFrequency();

	__bis_SR_register(GIE);


	__enable_interrupt(); //Enable interrupts globally

	valeurCompteur++;



	retourRRR=retourRRR2;

	if (retourRRR || retourRRR2)
	    {
	    lavaleur=0;
	    }


	mCompteur monCompteur(kMeter1);
	monCompteur.mOpen();
	valeurCompteur = monCompteur.mRead();

	if (valeurCompteur<300)
	    {
	    valeurCompteur=300;
	    }




	while (1) {

	}
}

