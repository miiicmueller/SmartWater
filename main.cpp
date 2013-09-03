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
//
//    mGSM theGSM;
//    theGSM.mSetup();
//    theGSM.mOpen();
//
//    gInput theGInput(&theGSM);
//    gCompute theGCompute(&theGInput);
//    gOutput theGOutput(&theGCompute);
//
//    iI2C i2cBus(k100kHz, kUSCI_B1, kMaster, 0xA5);
//    UInt16 moduleAddress = 0x50;
//    mEEPROM aEEPROM(moduleAddress, &i2cBus);
//    aEEPROM.mOpen();
//    // mCompteur aCompteur(kMeterSimulation, &aEEPROM);
//
//    tToolsCluster theTools(&aEEPROM);

    char messageRecu[kSciRecBufSize ] = "";
    bool COCO[20];
    bool aMessRecu;
    tDate maDate;
    tDate monCCredit;
    UInt16 creddit;

    mDelay::mSetup();
    mDelay::mOpen();

    maled1.write(BIT0);
    mDelay monDeelay;
    monDeelay.startDelayMS(2500);
    while (!monDeelay.isDone())
	;

    maled1.write(~BIT0);

    for (int i = 0; i < 20; i++)
	{
	COCO[i] = false;
	}

    mGSM monGsm;
    strcpy((char*) monGsm.codePIN, "1405"); //1405 5906
    strcpy((char*) monGsm.phoneNumber, "+41774874478");

    monGsm.mSetup();

    maled2.write(BIT1);
    monGsm.mOpen();

    if(kOk!=monGsm.state)
	{
	maled3.write(BIT2); //erreur gsm
	}

    maled2.write(~BIT1);

    maled1.write(BIT0);

    COCO[0] = monGsm.sendSMS((UInt8*) "Coucou cocoa", (UInt8*) "+41787526983");
    if (COCO[0])
	{
	maled3.write(~BIT2);
	maled2.write(BIT1);
	}
    else
	{
	maled3.write(BIT2);
	maled2.write(BIT1);
	}

//    COCO[1] = monGsm.getCredit(&creddit);
//    monCCredit.year = creddit;

   // COCO[2] = monGsm.getDate(&maDate);

    while (1)
	{
	COCO[3] = monGsm.getSMS(messageRecu, &aMessRecu);
	COCO[4] = aMessRecu;
	}
    }
