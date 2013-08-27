#ifndef I_U_S_B_H
#define I_U_S_B_H

#include <string>
#include <assert.h>

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"               //Basic Type declarations
#include "USB_API/USB_Common/usb.h"                 //USB-specific functions
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "usbConstructs.h"

#include "../Def/def.h"
#include "Interface.h"

#define MAX_BUFFERSIZE  100

typedef enum {	kStateDisconnected,
	kStateConnNoEnum,
	kStateActive,
	kStateEnumSuspended,
	kStateInProgress,
	kStateNoEnumSuspended,
	kStateError
} iUsbStateEnum;



class iUSB: public Interface {
private:
	char* usbSerialBuffer;
	int bufferSize;
	static char usbBuffer[MAX_BUFFERSIZE];
	iUsbStateEnum usbState;
	volatile BYTE *dataReceived ;

	void config();
	BYTE retInString(char* string);
	bool write(UInt8 aData);
	UInt8 read();
public:
	iUSB(volatile BYTE *bCDCDataReceived_event);
	~iUSB();
	bool getFullFrame(char* FrameBuffer);
	void sendFullFrame(char* FrameBuffer);
	void initUSB();
	bool isDataAvailable();
	void clearSerialBuffer();
	int getBufferSize();

	iUsbStateEnum getConnectionState();

};
#endif
