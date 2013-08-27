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

#include "USB_API/USB_Common/types.h"

#ifdef __cplusplus
extern "C"
    {
#endif

    int _system_pre_init(void)
	{
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
void main(void)
    {
    iDIO::InitAllPort();
    mCpu::configFrequency();
    __bis_SR_register(GIE);

    mGSM monGsm;
    char messageRecu[kSciRecBufSize ] = "";
    char cestOk[1];
    bool salut;
    UInt16 monCredit;
    tDate maDate;
    tDate monCCredit;

    mDelay::mSetup();
    mDelay::mOpen();

    strcpy((char*) monGsm.codePIN, "5906");
    strcpy((char*) monGsm.phoneNumber, "+41774874473");

    monGsm.mSetup();
    monGsm.mOpen();

    //ne pas oublier le fil !
    // il faudra de temps en temps vider la memoire peut etre

    salut =
	    monGsm.sendSMS(
		    " Unite\"Nom du site\":\r\nDate et heure 18/09/12/16:53:00\r\nDisponibilite 01:00/00:15\r\nMode S\r\nIndex 03046\r\nDebit jour 10,7\r\nDebit jour mens 8,7\r\nLimite jour mens 25,0\r\nTemperature 10,2\r\nOffset temperature 0,2\r\nCredit 29,29\r\nAlarme 0041765572263",
		    "+41787526983");
    //salut=monGsm.sendSMS("Unite\"Nom du site\":\r\nDate et heure 18/09/12/16:53:00\r\n","+41787526983"); //ok

    if (salut)
	{
	cestOk[0] = 1;
	}
    else
	{
	cestOk[0] = 0;
	}

    monCCredit.year = monGsm.getCredit(); // ok
    maDate = monGsm.getDate();

    while (1)
	{
	salut = monGsm.getSMS(messageRecu);
	if (salut)
	    {
	    cestOk[0] = 1;
	    }
	else
	    {
	    cestOk[0] = 0;
	    }
	}

    }

