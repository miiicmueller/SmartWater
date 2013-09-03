#include <string>
#include <assert.h>

#include "gInput.h"

gInput::gInput(mGSM* theGSM, mCompteur* theCompteurs[2], mRTC* theRTC,
	mTempSensor* theTempSensor)
    {
    this->theGSM = theGSM;
    this->theRTC = theRTC;
    this->theTempSensor = theTempSensor;
    this->theCompteurs[0] = theCompteurs[0];
    this->theCompteurs[1] = theCompteurs[1];
    }

void gInput::setup()
    {
    }

void gInput::execute()
    {
    }

gInput::~gInput()
    {
    }
