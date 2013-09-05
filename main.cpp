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
volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation

/*
 * ======== main ========
 */
void main(void)
    {
    int i;

    // Important pour la basse consommation
    iDIO::InitAllPort();

    mCpu::configFrequency();

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
    aEEPROM.mOpen();
   // aEEPROM.initIdTable();

    tToolsCluster theTools(&aEEPROM);
    // TODO : reset a enlever
//    theTools.reset();
//    theTools.saveAll();
    theTools.loadAll();

    mGSM theGSM(theTools.theSIMCard);
    theGSM.mSetup();
    //TODO : a remettre
    theGSM.mOpen();

    mTempSensor theTempSensor(0x48, &i2cBus);
    theTempSensor.mSetup();
    theTempSensor.mOpen();

    mUSB theUSB(&bCDCDataReceived_event);

    mRTC theRTC;
    theRTC.mOpen();

    mCompteur* theCountersTab[2];
    theCountersTab[0] = new mCompteur(kMeter1, &aEEPROM);
    theCountersTab[1] = new mCompteur(kMeter2, &aEEPROM);
    // mCompteur aCompteur(kMeterSimulation, &aEEPROM);

    gInput theGInput(&theGSM, theCountersTab, &theRTC, &theTempSensor,
	    &theTools, &theUSB);
    gTerminal theTerminalUSB(&theTools, &theUSB);
    gCompute theGCompute(&theGInput, &theTerminalUSB, &theTools, &theRTC);
    gOutput theGOutput(&theGCompute, &theGSM, &theRTC, &theUSB, &theTools);
    gSleep theGSleep(&theTools, &theRTC, &theGSM, theCountersTab[0],
	    &theTempSensor, &theGCompute);

    theGInput.setup();
    theTerminalUSB.setup();
    theGCompute.setup();
    theGOutput.setup();
    theGSleep.setup();

<<<<<<< HEAD
    //test de compute consumption
    theGInput.theInputMailBox.valueMeters[0].date.day = 10;
    theGInput.theInputMailBox.valueMeters[0].date.month = 9;
    theGInput.theInputMailBox.valueMeters[0].isConnected = true;
    theGInput.theInputMailBox.valueMeters[0].value = 10000;
    for (int k = 0; k < 12; k++)
	{
	theTools.theMonthsLimits[0]->limits[k] = 970;
	}

    theGCompute.computeConsumption();

    theGInput.theInputMailBox.valueMeters[0].date.day = 11; //rien
    theGInput.theInputMailBox.valueMeters[0].value = 10030;
    theGCompute.computeConsumption();

    theGInput.theInputMailBox.valueMeters[0].date.day = 11; //rien
    theGInput.theInputMailBox.valueMeters[0].value = 10031;
    theGCompute.computeConsumption();

    theGInput.theInputMailBox.valueMeters[0].date.day = 12; //rien
    theGInput.theInputMailBox.valueMeters[0].value = 10060;
    theGCompute.computeConsumption();

    theGInput.theInputMailBox.valueMeters[0].date.day = 13; //rien
    theGInput.theInputMailBox.valueMeters[0].value = 10090;
    theGCompute.computeConsumption();

    theGInput.theInputMailBox.valueMeters[0].date.day = 14; //avertissmeent le lendemain
    theGInput.theInputMailBox.valueMeters[0].value = 10190;
    theGCompute.computeConsumption();

    theGInput.theInputMailBox.valueMeters[0].date.day = 15; //alerte le lendemain
    theGInput.theInputMailBox.valueMeters[0].value = 10290;
    theGCompute.computeConsumption();

    theGInput.theInputMailBox.valueMeters[0].date.day = 15; //alerte ici
    theGInput.theInputMailBox.valueMeters[0].value = 10320;
    theGCompute.computeConsumption();

//    mDelay aDelayCompute;
//    mDelay aDelayInput;
//
//    while (1)
=======
    mDelay aDelayCompute;
    mDelay aDelayInput;

    while (1)
	{
	if (aDelayCompute.isDone())
	    {
	    aDelayCompute.startDelayMS(1);
	    theTerminalUSB.execute();
	    theGCompute.execute();
	    theGOutput.execute();
	    theGSleep.execute();
	    }
	if (aDelayInput.isDone())
	    {
	    aDelayInput.startDelayMS(20000);
	    theGInput.execute();
	    }
	}



//    //test de compute consumption
//    theGInput.theInputMailBox.valueMeters[0].date.day=10;
//    theGInput.theInputMailBox.valueMeters[0].date.month=9;
//    theGInput.theInputMailBox.valueMeters[0].isConnected=true;
//    theGInput.theInputMailBox.valueMeters[0].value=10000;
//    for(int k=0; k<12; k++)
>>>>>>> origin/master
//	{
//	theTools.theMonthsLimits[0]->limits[k]=970;
//	}
//
//    theGCompute.computeConsumption();
//
//    theGInput.theInputMailBox.valueMeters[0].date.day=11; //rien
//    theGInput.theInputMailBox.valueMeters[0].value=10030;
//    theGCompute.computeConsumption();
//
//    theGInput.theInputMailBox.valueMeters[0].date.day=11; //rien
//    theGInput.theInputMailBox.valueMeters[0].value=10031;
//    theGCompute.computeConsumption();
//
//    theGInput.theInputMailBox.valueMeters[0].date.day=12; //rien
//    theGInput.theInputMailBox.valueMeters[0].value=10060;
//    theGCompute.computeConsumption();
//
//    theGInput.theInputMailBox.valueMeters[0].date.day=13; //rien
//    theGInput.theInputMailBox.valueMeters[0].value=10090;
//    theGCompute.computeConsumption();
//
//    theGInput.theInputMailBox.valueMeters[0].date.day=14; //avertissmeent le lendemain
//    theGInput.theInputMailBox.valueMeters[0].value=10190;
//    theGCompute.computeConsumption();
//
//    theGInput.theInputMailBox.valueMeters[0].date.day=15; //alerte le lendemain
//    theGInput.theInputMailBox.valueMeters[0].value=10290;
//    theGCompute.computeConsumption();
//
//    theGInput.theInputMailBox.valueMeters[0].date.day=15; //alerte ici
//    theGInput.theInputMailBox.valueMeters[0].value=10320;
//    theGCompute.computeConsumption();

    }
