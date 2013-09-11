/*
 * gError.cpp
 *
 *  Created on: 6 sept. 2013
 *      Author: cyrille.savy
 */

#include "gError.h"

gError::gError(mGSM* theGSM, mTempSensor* theTempSensor, mEEPROM* theEEPROM)
    {
    this->theGSM = theGSM;
    this->theTempSensor = theTempSensor;
    this->theEEPROM = theEEPROM;
    }

void gError::setup()
    {
    for (int i = 0; i < kGErrorNbErrors; i++)
	{
	this->gErrorList[i] = true;
	}
    }

void gError::execute()
    {
    if (this->aDelay.isDone())
	{
	//erreur sur le GSM
	switch (this->theGSM->state)
	    {
	case kOk:
	    this->gErrorList[kGErrorGSM] = false;
	    break;
	case kDisconnected:
	    this->theGSM->mOpen();
	    break;
	case kErrorGeneral:
	case kErrorSetModeSms:
	case kErrorSetModeText:
	case kErrorEnableServiceData:
	case kErrorDeleteAllSms:
	case kErrorGetCredit:
	case kErrorModePDU:
	case kErrorModeText:
	case kErrorSimRequired:
	case kErrorSimFailure:
	case kErrorAntenna:
	case kErrorDecodeDate:
	case kErrorSimBusy:
	case kErrorSimPukRequired:
	case kErrorGetStateMemory:
	case kErrorMemoryFailure:
	case kErrorSendSmsTimeOut:
	    this->theGSM->mClose();
	    this->gErrorList[kGErrorGSM] = true;
	    break;
	case kErrorMemoryFull:
	case kErrorSimPin2Required:
	case kErrorSimPuk2Required:
	case kErrorEnterPin:
	case kErrorSimNotInserted:
	case kErrorSimWrong:
	case kErrorReadSms:
	default:
	    break;
	    }

	//erreur sur le capteur de temperature
//	switch (this->theTempSensor->getStatus())
//	    {
//	case kTempSensorOK:
//	    this->gErrorList[kGErrorTempSensor] = false;
//	    break;
//	case kTempSensorCommError:
//	case kTempSensorMissing:
//	    this->gErrorList[kGErrorTempSensor] = true;
//	default:
//	    break;
//	    }

	this->aDelay.startDelayMS(2000);
	}
    }

gError::~gError()
    {
    }

