#include <string>
#include <assert.h>
#include <string.h>

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"               //Basic Type declarations
#include "USB_API/USB_Common/usb.h"                 //USB-specific functions
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "usbConstructs.h"

#include "iUSB.h"

//TODO : Rechercher une solution pour reveiller le micro par l'USB

char iUSB::usbBuffer[MAX_BUFFERSIZE] = "";

/**
 * Constructeur de l'USB
 * *bCDCDataReceived_event : Variable globale changee dans usbEventHandling.c !!!!
 * A ne pas oublier !!
 */
iUSB::iUSB(volatile BYTE *bCDCDataReceived_event) {
	this->bufferSize = MAX_BUFFERSIZE;
	this->usbState = kStateDisconnected;
	this->dataReceived = bCDCDataReceived_event;
	this->usbSerialBuffer = iUSB::usbBuffer;
	this->config();
	this->getConnectionState();
	this->clearSerialBuffer();
}

iUSB::~iUSB() {

}

/**
 * Configuration de l'USB et de ses Events
 */
void iUSB::config() {

	//Ne pas oublier d'avoir setVcore(3) avant
	//initialisation de l'USB
	this->initUSB();

	//Enable various USB event handling routines
	USB_setEnabledEvents(
			kUSB_VbusOnEvent + kUSB_VbusOffEvent + kUSB_receiveCompletedEvent
					+ kUSB_dataReceivedEvent + kUSB_UsbSuspendEvent
					+ kUSB_UsbResumeEvent + kUSB_UsbResetEvent);

	//See if we're already attached physically to USB, and if so, connect to it
	//Normally applications don't invoke the event handlers, but this is an exception.
	if (USB_connectionInfo() & kUSB_vbusPresent) {
		USB_handleVbusOnEvent();
	}

	//desactiver LDO
	USBPWRCTL &= ~(SLDOEN);      // Disable the VUSB LDO and the SLDO

}

/**
 * Macro d'initialisation de l'USB
 */
void iUSB::initUSB() {
	USB_init();
}

/**
 * Test si des donnees sont disponibles
 * retour : valeur booleenne
 */
bool iUSB::isDataAvailable() {
	return (bool) *(this->dataReceived);
}

/**
 * Nettoye le buffer de reception de l'USB
 */
void iUSB::clearSerialBuffer() {
	char i = 0;

	for (i = 0; i < this->bufferSize; i++) {              //Empty the buffer
		this->usbSerialBuffer[i] = 0x00;
	}
}

/**
 * Retourne la taille MAX du buffer configuree (est inchangeable en execution)
 */
int iUSB::getBufferSize() {
	return this->bufferSize;
}

/**
 * Renvoie une trame qui finit par "\r" !
 * FrameBuffer : tableau pour recevoir les byte. De taille this->bufferSize !
 * Revoie true si l'on a une trame disponible
 */
bool iUSB::getFullFrame(char* FrameBuffer) {

	//Tester si l'on a recu qqch
	if (*this->dataReceived) {
		char pieceOfString[MAX_BUFFERSIZE] = ""; //Holds the new addition to the string
		//Add bytes in USB buffer to theCommand
		cdcReceiveDataInBuffer((BYTE*) pieceOfString, this->bufferSize,
				CDC0_INTFNUM);        //Get the next piece of the string

		strcat(this->usbSerialBuffer, pieceOfString);
		cdcSendDataInBackground((BYTE*) pieceOfString, strlen(pieceOfString),
				CDC0_INTFNUM, 0); //Echoes back the characters received (needed
								  //for Hyperterm)
		// Test \r
		if (retInString(this->usbSerialBuffer)) {
			strcpy(FrameBuffer, this->usbSerialBuffer);
			this->clearSerialBuffer();
			*(this->dataReceived) = FALSE;
			return true;
		} else {
			*(this->dataReceived) = FALSE;
			return false;
		}

	} else {
		return false;
	}
}

/**
 * Permet de transmettre une trame sur l'USB
 * FrameBuffer : Tableau de char a  envoyer
 */
void iUSB::sendFullFrame(char* FrameBuffer) {
	cdcSendDataInBackground((BYTE*) FrameBuffer, strlen(FrameBuffer),
			CDC0_INTFNUM, 0); //Send the response over USB
	this->clearSerialBuffer();
}

/**
 * Non utilisee
 */
bool iUSB::write(UInt8 aData) {
	return false;
}

/**
 * Non utilisee
 */
UInt8 iUSB::read() {
	return 0;
}

/**
 * Permet de verifier l'etat de la connexion USB
 * retour : iUsbStateEnum etat en cours
 */
iUsbStateEnum iUSB::getConnectionState() {
	switch (USB_connectionState()) {
	case ST_USB_DISCONNECTED:
// This state indicates that VBUS is not present, meaning there is no USB connection.
// If a device is self-powered, this becomes the main loop when there is no USB connection.

// Enter LPM3 until VBUS-on event
// Here, write the main loop for how the device should behave when USB is disconnected.
		this->usbState = kStateDisconnected;

		break;

	case ST_USB_CONNECTED_NO_ENUM:
// This state indicates that VBUS is present but USB_connect() has not yet been called (the PUR signal has
// not yet been pulled high).  Most USB devices respond to a VBUS-on event by pulling PUR high -- and so the
// recommendation is to call USB_connect() from USB_handleVbusOnEvent().  If this is done, then this state
// is very short-lived, thus there is no code here.  This state is provided because some applications may not
// wish to assert PUR immediately upon connection.
		this->usbState = kStateConnNoEnum;
		break;

	case ST_ENUM_ACTIVE:
// This state indicates that the device has successfully enumerated on a USB host.  When connected to USB, the
// code in this branch becomes the main loop of the program.  Those familiar with common MSP430 coding
// practices recognize the immediate entry into LPM0, out of which an interrupt can be used to make one run
// through the main loop.  (This of course is application-specific, and the s/w engineer is free to use other
// constructs.)  Note that during an active USB connection (enumerated and not suspended), the MSP430 should
// not be placed into a mode below LPM0 (no LPM3/4/5).

// Enter LPM0 + enable interrupts

// Here, write the main loop for how the device should behave when USB is connected and active.
		this->usbState = kStateActive;
		break;

	case ST_ENUM_SUSPENDED:
// This state indicates  the device is enumerated on a USB host, but the host has suspended it.  The device is
// not allowed to draw more than 2.5mA from VBUS during this time, and thus the main loop might look different
// than it did during ST_ENUM_ACTIVE.  It's recommended to insert code into handleSuspendEvent() (or here)
// that disables any circuitry drawing excessive current from VBUS.  During suspend, the power mode may enter
// LPM3 or LPM4.

// Enter LPM3, until a resume or VBUS-off event
// Here, write the main loop for how the device should behave when USB is disconnected.
		this->usbState = kStateEnumSuspended;

		break;

	case ST_ENUM_IN_PROGRESS:
// This state indicates the device is in the process of being enumerated on a USB host.  This process is usually brief,
// although in rare enumeration failures it might stay here indefinitely.  A timeout could be implemented for such

// the API doesn't implement this timeout internally.  During enumeration, the USB module must stay fully active;
// therefore, the power mode shouldn't enter LPM3/4.  Since it's typically very brief, there's often no LPM entry
		this->usbState = kStateInProgress;
		break;

	case ST_NOENUM_SUSPENDED:
// This state indicates that VBUS is present, the device attempted to enumerate by pulling PUR high, but then the host

// the device.  This differs from ST_ENUM_IN_PROGRESS, in that ST_ENUM_IN_PROGRESS doesn't involve the device getting
// This state might happen from a failed enumeration; becoming attached to a host that is in standby; or becoming
// to a powered hub without a host upstream.  To handle this, code has been placed in USB_handleSuspendEvent() to
// enumeration.  As a result, this state shouldn't last very long, and no code is placed here.
// Another way of handling might be to simply stay in this state until an active host attempts to enumerate.
		this->usbState = kStateNoEnumSuspended;
		break;

	case ST_ERROR:
		this->usbState = kStateError;
		break;

	default:
		this->usbState = kStateDisconnected;
		;
	}
	return this->usbState;
}

/*
 * ======== retInString ========
 */
//This function returns TRUE if there's an 0x0D character in the string; and if so,
//it trims the 0x0D and anything that had followed it.
BYTE iUSB::retInString(char* string) {
	BYTE retPos = 0, i, len;
	char tempStr[MAX_BUFFERSIZE] = "";

	strncpy(tempStr, string, strlen(string));        //Make a copy of the string
	len = strlen(tempStr);
	while ((tempStr[retPos] != 0x0A) && (tempStr[retPos] != 0x0D)
			&& (retPos++ < len))
		;        //Find 0x0D; if not found, retPos ends up at len

	if ((retPos < len) && (tempStr[retPos] == 0x0D)) { //If 0x0D was actually found...
		for (i = 0; i < this->bufferSize; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy(string, tempStr, retPos); //...trim the input string to just before 0x0D
		return (TRUE); //...and tell the calling function that we did so
	} else if ((retPos < len) && (tempStr[retPos] == 0x0A)) { //If 0x0D was actually found...
		for (i = 0; i < this->bufferSize; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy(string, tempStr, retPos); //...trim the input string to just before 0x0D
		return (TRUE); //...and tell the calling function that we did so
	} else if (tempStr[retPos] == 0x0D) {
		for (i = 0; i < this->bufferSize; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy(string, tempStr, retPos); //...trim the input string to just before 0x0D
		return (TRUE); //...and tell the calling function that we did so
	} else if (retPos < len) {
		for (i = 0; i < this->bufferSize; i++) {       //Empty the buffer
			string[i] = 0x00;
		}
		strncpy(string, tempStr, retPos); //...trim the input string to just before 0x0D
		return (TRUE); //...and tell the calling function that we did so
	}

	return (FALSE);                                 //Otherwise, it wasn't found
}

/*
 * ======== UNMI_ISR ========
 */
#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR(VOID) {
	switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG)) {
	case SYSUNIV_NONE:
		__no_operation();
		break;
	case SYSUNIV_NMIIFG:
		__no_operation();
		break;
	case SYSUNIV_OFIFG:
		UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT2OFFG); //Clear OSC flaut Flags fault flags
		SFRIFG1 &= ~OFIFG; //Clear OFIFG fault flag
		break;
	case SYSUNIV_ACCVIFG:
		__no_operation();
		break;
	case SYSUNIV_BUSIFG:

//If bus error occured - the cleaning of flag and re-initializing of
//USB is required.
		SYSBERRIV = 0;		//clear bus error flag
		USB_disable();		//Disable
	}
}
