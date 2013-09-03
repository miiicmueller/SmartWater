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
    int salut, ok;

    // Important pour la basse consommation
    iDIO::InitAllPort();

    mCpu::configFrequency();

    //attente que l'alim soit stabilisee
    iDIO pGood((char*) kPort_6, BIT4);
    pGood.SetPortDirection(kInput);

    while (pGood.read() == 0)
	{
	}

    //On endort le porcesseur
//    mCpu::setPowerMode(kLPM3);

    __bis_SR_register(GIE);

    iI2C i2cBus(k100kHz, kUSCI_B1, kMaster, 0xA5);
    UInt16 moduleAddress = 0x50;
    mEEPROM aEEPROM(moduleAddress, &i2cBus);

    mDelay::mSetup();
    mDelay::mOpen();
    aEEPROM.mOpen();

    mGSM theGSM;
    mCompteur aCompteur(kMeterSimulation, &aEEPROM);
    mTempSensor theTempSens(0x48, &i2cBus);
    mRTC theRTC;

    theRTC.mOpen();

    strcpy((char*) theGSM.codePIN, "5906");

    theGSM.mSetup();
    theTempSens.mSetup();
    aCompteur.mSetup();

    theGSM.mOpen();
    theTempSens.mOpen();
    aCompteur.mOpen();

    tToolsCluster theTools(&aEEPROM);

    theTools.theAvailability->aIntervalMn = 10;
    theTools.theAvailability->aTimeMn = 1;

    gSleep theGslp(&theTools, &theRTC, &theGSM, &aCompteur, &theTempSens);
    theGslp.setup();

    while (1)
	{
	theGslp.execute();
	}
    }

