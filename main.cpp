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

#include "Tools/tCommandesAT.h"

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

    UInt32 valeurCompteur = 0;
    // Important pour la basse consommation
    iDIO::InitAllPort();

    mCpu::configFrequency();

    __bis_SR_register(GIE);

    //mUSB commUsb(&bCDCDataReceived_event);
    //iI2C iI2C_1(k100kHz, kUSCI_B1, kMaster, 0x01A5);
    //mRTC RTC;

    /*mGSM mGsm;

     valeurCompteur++;

     iDIO enableGSM((char*) kPort_7, BIT4);
     enableGSM.SetPortDirection(kOutput);
     enableGSM.SetPortDriveStrength(kFullStrength);
     enableGSM.write(~BIT4);

     //
     iDIO resetGSM((char*) kPort_7, BIT3);
     resetGSM.SetPortDirection(kOutput);
     resetGSM.SetPortDriveStrength(kFullStrength);
     resetGSM.write(~BIT3);*/

    mDelay::mSetup();
    mDelay::mOpen();
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

    if (valeurCompteur < 300)
	{
	valeurCompteur = 300;
	}

    iDIO aLed((char*) kPort_7, BIT0);
    aLed.SetPortDirection(kOutput);
    aLed.write(0xff);

    mDelay aDelay;
    mCompteur monCompteur(kMeter1);
    monCompteur.mOpen();
    valeurCompteur = monCompteur.mRead();

    i = 0;
    aLed.write(i);
    aDelay.startDelay(1000);

    while (1)
	{

	if (aDelay.isDone())
	    {
	    i = ~i;
	    aLed.write(i);
	    aDelay.startDelay(1000);
	    }

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

	}
    }

