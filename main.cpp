//#define FIRST_INIT

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
#include "Modules/mWDT.h"
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
volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation

/*
 * ======== main ========
 */
void main(void)
    {
    //Configuration de la fréquence
    mCpu::configFrequency();

    // Important pour la basse consommation
    iDIO::InitAllPort();

    mWDT theWatchDog;
    //Demmarage du watchdog
    //   theWatchDog.startWatchDog();

    //attente que l'alim soit stabilisee
    iDIO pGood((char*) kPort_6, BIT4);
    pGood.SetPortDirection(kInput);

    while (pGood.read() == 0)
	{
	}

    //activation des interruptions
    __bis_SR_register(GIE);

    //instanciation des interfaces
    //parametrage des interfaces
    //instanciation des modules
    //parametrage des modules
    //instanciation des utilitaires
    //parametrage des utilitaires
    //instanciation des gestionnaires
    //parametrage des gestionnaires

    mDelay::mSetup();
    mDelay::mOpen();

    iI2C i2cBus(k100kHz, kUSCI_B1, kMaster, 0xA5);
    UInt16 eePromAddress = 0x50;
    mEEPROM aEEPROM(eePromAddress, &i2cBus);

#ifdef FIRST_INIT

    theWatchDog.stopWatchDog();

    aEEPROM.initIdTable();
    aEEPROM.mOpen();
    tToolsCluster theTools(&aEEPROM);
    theTools.reset();
    theTools.saveAll();

    //On attend pour rien faire d'autre
    while(1);
#else
    aEEPROM.mOpen();
    tToolsCluster theTools(&aEEPROM);
    theTools.loadAll();
#endif

    mGSM theGSM(theTools.theSIMCard);
    theGSM.mSetup();
    theGSM.mOpen();

    mTempSensor theTempSensor(0x48, &i2cBus);
    theTempSensor.mSetup();
    theTempSensor.mOpen();

    mUSB theUSB(&bCDCDataReceived_event);

    mRTC theRTC;
    theRTC.mOpen();

    mCompteur* theCountersTab[3];
    theCountersTab[0] = new mCompteur(kMeter1, &aEEPROM,
	    theTools.theCompteur[0]);
    theCountersTab[1] = new mCompteur(kMeter2, &aEEPROM,
	    theTools.theCompteur[1]);
    theCountersTab[2] = new mCompteur(kMeterSimulation, &aEEPROM,
	    theTools.theCompteur[2]);

    gInput theGInput(&theGSM, theCountersTab, &theRTC, &theTempSensor,
	    &theTools, &theUSB);
    gTerminal theTerminalUSB(&theTools, &theUSB);
    gCompute theGCompute(&theGInput, &theTerminalUSB, &theTools, &theRTC);
    gOutput theGOutput(&theGCompute, &theGSM, &theRTC, &theUSB, &theTools);
    gSleep theGSleep(&theTools, &theRTC, &theGSM, theCountersTab[0],
	    &theTempSensor, &theGCompute, &theWatchDog);

    theGInput.setup();
    theTerminalUSB.setup();
    theGCompute.setup();
    theGOutput.setup();
    theGSleep.setup();

    //On endort le processeur
    mCpu::setPowerMode(kLPM3);

    mDelay aDelayCompute;
    mDelay aDelayInput;
    aDelayCompute.startDelayMS(2);
    aDelayInput.startDelayMS(1);

    while (1)
	{
	//theWatchDog.resetWatchDog();
	if (aDelayCompute.isDone())
	    {
	    aDelayCompute.startDelayMS(1);
	    theTerminalUSB.execute();
	    theGCompute.execute();
	    theGOutput.execute();
	    //theGSleep.execute();
	    }
	if (aDelayInput.isDone())
	    {
	    aDelayInput.startDelayMS(20000);
	    theGInput.execute();
	    }
	}

    }
