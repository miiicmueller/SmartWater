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

unsigned int temperature;
float temp = 0.0;
char tempToSend[MAX_BUFFERSIZE] = "";

/*
 * ======== main ========
 */
void main(void)
    {

    char i;

    /*char sec = 0;
     char min = 0;
     char hr = 0;*/

    // Important pour la basse consommation
    iDIO::InitAllPort();

    iDIO Pgood((char*) kPort_6, BIT4);
    Pgood.SetPortDirection(kInput);

    //On attend que l'alim démarre
    while (!(Pgood.read() == BIT4))
	;

    mCpu::configFrequency();

    __bis_SR_register(GIE);

//    gInput theGInput;
//    gCompute theGCompute(&theGInput);
//    gOutput theGOutput(&theGCompute);
//
//    mDelay::mSetup();
//    mDelay::mOpen();
//
//    /*iI2C i2cBus(k100kHz, kUSCI_B1, kMaster, 0xA5);
//     UInt16 moduleAddress = 0x50;
//     mEEPROM aEEPROM(moduleAddress, &i2cBus);
//     mCompteur aCompteur(kMeterSimulation, &aEEPROM);*/
//
//    gTerminal theTerminalUSB(&theGInput);
//
//    mDelay aDelay;

    while (1)
	{

	}
//	{
//	if (aDelay.isDone())
//	    {
//	    aDelay.startDelayMS(5);
//	    theTerminalUSB.execute();
//	    }
//	}

    /*mUSB commUsb(&bCDCDataReceived_event);
     iI2C iI2C_1(k100kHz, kUSCI_B1, kMaster, 0x01A5);
     mRTC RTC;

     mGSM mGsm;

     valeurCompteur++;

     iDIO enableGSM((char*) kPort_7, BIT4);
     enableGSM.SetPortDirection(kOutput);
     enableGSM.SetPortDriveStrength(kFullStrength);
     enableGSM.write(~BIT4);

     iDIO resetGSM((char*) kPort_7, BIT3);
     resetGSM.SetPortDirection(kOutput);
     resetGSM.SetPortDriveStrength(kFullStrength);
     resetGSM.write(~BIT3);*/

//
//	iDIO CTSel2((char*) kPort_6, BIT1);
//	enableCT.SetPortDirection(kOutput);
//	enableCT.SetPortDriveStrength(kFullStrength);
//	enableCT.write(~BIT1);
//	iDIO resetGSM((char*) kPort_7, BIT3);
//	iUART uart(kUSCI_A0, kLSBFirst, k1StBits, kNone, k8bits,
//				k9600);
//	mEEPROM DataBase(0x50, &iI2C_1);
//	mTempSensor CaptCarte(0x48, &iI2C_1);
//	DataBase.mOpen();
//	CaptCarte.mOpen();
//	RTC.mOpen();
//	mGsm.mOpen();
//CaptCarte.configSensor(kConfiguration, 0x60);
//RTC.setHour(17, 0, 0);
//RTC.setAlarm(1);
//mGsm.sendSMS("Coucou", "+41798183833");
    /*if (valeurCompteur < 300)
     {
     valeurCompteur = 300;
     }*/

//    iDIO cptEnable((char*) kPort_6, BIT2);
//    cptEnable.SetPortDirection(kOutput);
//
//    iDIO cptSim((char*) kPort_6, BIT3);
//    cptSim.SetPortDirection(kOutput);
//
//    iDIO cptSel_1((char*) kPort_6, BIT0);
//    cptSel_1.SetPortDirection(kOutput);
//
//    iDIO cptSel_2((char*) kPort_6, BIT1);
//    cptSel_2.SetPortDirection(kOutput);
//
//    iDIO cptRxd((char*) kPort_4, BIT5);
//    cptRxd.SetPortDirection(kInput);
//
//    iDIO aLed_1((char*) kPort_7, BIT0);
//    aLed_1.SetPortDirection(kOutput);
//
//    iDIO aLed_2((char*) kPort_7, BIT1);
//    aLed_2.SetPortDirection(kOutput);
//iUART uart(kUSCI_A1, kLSBFirst, k1StBits, kEven, k7bits, k300);
    /*mCompteur monCompteur(kMeter1);
     monCompteur.mOpen();
     valeurCompteur = monCompteur.mRead();*/

//    cptEnable.write(kHigh);
//    cptSel_1.write(kHigh);
//    cptSel_2.write(kLow);
//    while (1)
//	{
//	cptEnable.write(kHigh);
//	cptEnable.write(kLow);
//	cptEnable.write(kHigh);
//	cptEnable.write(kLow);
//	cptEnable.write(kHigh);
//	cptEnable.write(kLow);
//	}
//    mDelay aDelay_1;
//    i = 0xff;
//    aDelay_1.startDelayMS(1);
//
//    mDelay aDelay_2;
//    aDelay_2.startDelayMS(1);
//
//    while (1)
//	{
//
//	if (aDelay_1.isDone())
//	    {
//	    i = ~i;
//	    cptSim.write(i);
//	    aLed_1.write(i);
//	    aDelay_1.startDelayMS(20);
//	    }
//
//	if (aDelay_2.isDone())
//	    {
//	    if (cptRxd.read() != 0)
//		{
//		aLed_2.write(kHigh);
//		}
//	    else
//		{
//		aLed_2.write(kLow);
//		}
//	    aDelay_2.startDelayMS(1);
//	    }
// On endort le processeur en niveau 3 (voir datasheet page 20)
//		//Check the USB state and directly main loop accordingly
//		if (commUsb.isConnected()) {
//			if (commUsb.getCommand(&cmd)) {
//				switch (cmd) {
//				case 1:
//					temperature = CaptCarte.readTemp();
//					DataBase.write(0x0000, (char) temperature);
//					DataBase.ackPolling();
//					DataBase.write(0x0001, (char) (temperature >> 8));
//					DataBase.ackPolling();
//					sprintf(tempToSend, "Tempe.:%d\r\n", temperature >> 4);
//					commUsb.sendReply(tempToSend);
//					break;
//				case 2:
//					int eepromVal = 0;
//					eepromVal = (int) DataBase.read(0x0000);
//					eepromVal += (int) (DataBase.read(0x0001) << 8);
//
//					sprintf(tempToSend, "EEPROM:%d\r\n", eepromVal >> 4);
//					commUsb.sendReply(tempToSend);
//					break;
//				case 3:
//					RTC.readTime(&hr, &min, &sec);
//					sprintf(tempToSend, "%d:%d:%d\r\n", hr, min, sec);
//					commUsb.sendReply(tempToSend);
//					break;
//				default:
//					commUsb.sendReply("Cmd invalide\r\n");
//				}
//			}
//
//		}
//}
    }

