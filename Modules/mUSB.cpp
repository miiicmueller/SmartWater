#include <string.h>
#include <assert.h>

#include "Interfaces/iUSB.h"

#include "mUSB.h"

/**
 * Constructeur de base
 * *bCDCDataReceived_event : Variable globale changee dans usbEventHandling.c !!!!
 * A ne pas oublier !!
 */
mUSB::mUSB(volatile BYTE *bCDCDataReceived_event)
    {
    this->usbPort = new iUSB(bCDCDataReceived_event);
    }

mUSB::~mUSB()
    {

    }

/**
 * Test si l'on a recu une commande : A determiner selon le protocole
 */
bool mUSB::getCommand(char* aChain)
    {
    if (this->usbPort->isDataAvailable() == true)
	{
	nop();
	//Some data is in the buffer; begin receiving a
	if (this->usbPort->getFullFrame(aChain))
	    {
	    return true;
	    }
	else
	    {
	    return false;
	    }
	}
    else
	{
	return false;
	}
    }

/**
 * Envoi d'une string sur l'USB
 * aMessage : Message a  transmettre
 */
void mUSB::sendReply(char* aMessage)
    {
    this->usbPort->sendFullFrame(aMessage);
    }

/**
 * Test si l'USB est pret ou non
 */
bool mUSB::isConnected()
    {
    switch (this->usbPort->getConnectionState())
	{
    case kStateActive:
	return true;
    default:
	return false;
	}
    }

/**
 * Non utilisee
 */
void mUSB::mOpen()
    {

    }

/**
 * Non utilisee
 */
void mUSB::mClose()
    {

    }

/**
 * Non utilisee
 */
void mUSB::mSetup()
    {

    }
