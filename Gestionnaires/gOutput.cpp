#include <string>
#include <assert.h>

#include "gOutput.h"

//----------------------------------------------------------------
//constructeur
//
//gCompute : le gestionnaire qui contient les donnees qui devront etre sorties
//----------------------------------------------------------------
gOutput::gOutput(gCompute* theGCompute, mGSM* theGSM, mRTC* theRTC,
	mUSB* theUSB)
    {
    this->theGCompute = theGCompute;
    this->theGSM = theGSM;
    this->theRTC = theRTC;
    this->theUSB = theUSB;
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
    //TODO : envoyer le SMS de reponse

    //mise a l'heure automatique
    //TODO : enlever les commentaires
    /*if (this->theGCompute->theComputeMailBox.mahAuto)
     {
     this->theGCompute->theComputeMailBox.mahAuto = false;

     tDate theDate;

     if (theGSM->getDate(&theDate))
     {
     theRTC->setDate(theDate->year, theDate->month, theDate->day,
     theDate->dayOfWeek);
     theRTC->setHour(theDate->hour, theDate->minute, theDate->second);
     }
     }*/
    }
