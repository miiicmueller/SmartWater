#include <string>
#include <assert.h>

#include "gOutput.h"
#include "stdio.h"

//----------------------------------------------------------------
//constructeur
//
//gCompute : le gestionnaire qui contient les donnees qui devront etre sorties
//----------------------------------------------------------------
gOutput::gOutput(gCompute* theGCompute, mGSM* theGSM, mRTC* theRTC,
	mUSB* theUSB, tToolsCluster* theTools)
    {
    this->theGCompute = theGCompute;
    this->theGSM = theGSM;
    this->theRTC = theRTC;
    this->theUSB = theUSB;
    this->theTools = theTools;
    }

void gOutput::setup()
    {
    }

void gOutput::execute()
    {
    //reponse USB
    if (this->theGCompute->theComputeMailBox.aReplyUSB[0] != '\0')
	{
	strcat(this->theGCompute->theComputeMailBox.aReplyUSB, "\r\n");
	this->theUSB->sendReply(this->theGCompute->theComputeMailBox.aReplyUSB);
	}

    //reponse SMS
    if (this->theGCompute->theComputeMailBox.aReplySMS[0] != '\0')
	{
	if (!this->theGSM->sendSMS(
		(UInt8*) (this->theGCompute->theComputeMailBox.aReplySMS),
		(UInt8*) (this->theGCompute->theComputeMailBox.aReplyNb)))
	    {
	    // TODO : en cas d'erreur d'envoi de SMS
	    }
	}

    //alarme SMS
    for (int i = 0; i <= 1; i++)
	{
	if (this->theGCompute->theComputeMailBox.hasOverrun[i])
	    {
	    char aAlarm[80];

	    sprintf(aAlarm,
		    "consumption alarm on : %s\r\nlimit : %d\r\nconsumption : %d",
		    this->theTools->theUnitName->aName,
		    this->theGCompute->theComputeMailBox.overrunLimit[i],
		    this->theGCompute->theComputeMailBox.overrunConsumption[i]);

	    this->theGCompute->theComputeMailBox.hasOverrun[i] = false;

	    if (!this->theGSM->sendSMS((UInt8*) aAlarm,
		    (UInt8*) (this->theTools->theAlarmNumber[i]->aTelNumber)))
		{
		// TODO : en cas d'erreur d'envoi de SMS
		}
	    }
	}

    //mise a l'heure automatique
    if (this->theGCompute->theComputeMailBox.mahAuto)
	{
	this->theGCompute->theComputeMailBox.mahAuto = false;

	tDate theDate;

	if (theGSM->getDate(&theDate))
	    {
	    theRTC->setDate((int) theDate.year, (char) theDate.month,
		    (char) theDate.day, (char) theDate.dayOfWeek);
	    theRTC->setHour((char) theDate.hour, (char) theDate.minute,
		    (char) theDate.second);
	    }
	}
    }

gOutput::~gOutput()
    {
    }
