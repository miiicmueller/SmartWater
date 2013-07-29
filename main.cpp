#include <msp430.h>

#include "Interfaces/iDIO.h"
#include "Interfaces/iUART.h"
#include "Interfaces/iI2C.h"

#include "Modules/mGSM.h"
#include "Modules/mCpu.h"
#include "Modules/mEEPROM.h"
#include "Modules/mTempSensor.h"
#include "Modules/mUSB.h"

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
char tempToSend[MAX_BUFFERSIZE] = "" ;

/*
 * ======== main ========
 */
void main(void) {

	iDIO::InitAllPort();

	mCpu::configFrequency();

	mUSB commUsb(&bCDCDataReceived_event);
	iI2C iI2C_1(k100kHz, kUSCI_B1, kMaster, 0x01A5);

	mEEPROM DataBase(0x50, &iI2C_1);
	mTempSensor CaptCarte(0x48, &iI2C_1);

	CaptCarte.mOpen();
	CaptCarte.configSensor(kConfiguration, 0x60);

	__enable_interrupt();    //Enable interrupts globally

	while (1) {
		int cmd = 0;
		//Check the USB state and directly main loop accordingly
		if (commUsb.isConnected()) {
			if (commUsb.getCommand(&cmd)) {
				switch (cmd) {
				case 1:
					temperature = CaptCarte.readTemp();
					sprintf(tempToSend,"Tempe.:%d",temperature>>4);
					commUsb.sendReply(tempToSend);
					break;
				case 2:
					commUsb.sendReply("Cmd 2\r\n");
					break;
				case 3:
					commUsb.sendReply("Cmd 3\r\n");
					break;
				default:
					commUsb.sendReply("Cmd invalide\r\n");
				}
			}

		}

	}  //while(1)
} //main()

