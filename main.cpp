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
//volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation

/*
 * ======== main ========
 */
void main(void)
    {
    iDIO::InitAllPort();
    mCpu::configFrequency();
    __bis_SR_register(GIE);

    iDIO maled1((char*) kPort_7, BIT0);
    iDIO maled2((char*) kPort_7, BIT1);
    iDIO maled3((char*) kPort_7, BIT2);
    maled1.SetPortDirection(kOutput);
    maled2.SetPortDirection(kOutput);
    maled3.SetPortDirection(kOutput);
    maled1.SetPortDriveStrength(kFullStrength);
    maled2.SetPortDriveStrength(kFullStrength);
    maled3.SetPortDriveStrength(kFullStrength);

    mGSM theGSM;
    theGSM.mSetup();
    theGSM.mOpen();

    gInput theGInput(&theGSM);
    gCompute theGCompute(&theGInput);
    gOutput theGOutput(&theGCompute);

    iI2C i2cBus(k100kHz, kUSCI_B1, kMaster, 0xA5);
    UInt16 moduleAddress = 0x50;
    mEEPROM aEEPROM(moduleAddress, &i2cBus);
    aEEPROM.mOpen();
    // mCompteur aCompteur(kMeterSimulation, &aEEPROM);

    tToolsCluster theTools(&aEEPROM);

    char messageRecu[kSciRecBufSize ] = "";
    char cestOk[1];
    bool salut;
    UInt16 monCredit;
    tDate maDate;
    tDate monCCredit;

    mDelay::mSetup();
    mDelay::mOpen();

    maled1.write(BIT0);
    mDelay monDeelay;
    monDeelay.startDelayMS(2500);
    while (!monDeelay.isDone())
	;

    maled1.write(~BIT0);

    mGSM monGsm;
    strcpy((char*) monGsm.codePIN, "1405"); //1405 5906
    strcpy((char*) monGsm.phoneNumber, "+41774874473");

    monGsm.mSetup();

    maled2.write(BIT1);
    monGsm.mOpen();

    maled2.write(~BIT1);

    maled1.write(BIT0);
    //ne pas oublier le fil !
    // il faudra de temps en temps vider la memoire peut etre

    salut =
	    monGsm.sendSMS(
		    (UInt8*) "Unite\"Nom du site\":\r\nDate et heure 18/09/12/16:53:00\r\nDisponibilite 01:00/00:15\r\nMode S\r\nIndex 03046\r\nDebit jour 10,7\r\nDebit jour mens 8,7\r\nLimite jour mens 25,0\r\nTemperature 10,2\r\nOffset temperature 0,2\r\nCredit 29,29\r\nAlarme 0041765572263",
		    (UInt8*) "+41787526983");
    if (salut)
	{
	cestOk[0] = 1;
	maled2.write(BIT1);
	}
    else
	{
	cestOk[0] = 0;
	maled3.write(BIT2);
	maled2.write(BIT1);
	}
//reessayer maintenant que le timeout est augmenté
    // while (1)
    //{
    monCCredit.year = monGsm.getCredit(); // ok
    //   maDate = monGsm.getDate();
//	}
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
