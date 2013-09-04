#include <string>
#include <assert.h>

#include "gInput.h"

gInput::gInput(mGSM* theGSM, mCompteur* theCompteurs[2], mRTC* theRTC,
	mTempSensor* theTempSensor, tToolsCluster* theTools, mUSB* theUSB)
    {
    this->theGSM = theGSM;
    this->theRTC = theRTC;
    this->theTempSensor = theTempSensor;
    this->theCompteurs[0] = theCompteurs[0];
    this->theCompteurs[1] = theCompteurs[1];
    this->theTools = theTools;
    this->theUSB = theUSB;

    //assignation du contenu de la mailbox
    this->theInputMailBox.aUserNb = &(this->theAnalyzer.aCommandResult.aUserNb);
    this->theInputMailBox.aAction =
	    &(this->theAnalyzer.aCommandResult.aCommandEnum);
    this->theInputMailBox.theParametersNumber =
	    &(this->theAnalyzer.aCommandResult.parametersNumber);

    for (int i = 0; i < 12; i++)
	{
	this->theInputMailBox.theParameters[i] =
		this->theAnalyzer.aCommandBrut.theParameters[i];
	}
    }

void gInput::setup()
    {
    }

void gInput::execute()
    {
    //pas de gInput en mode parametrage USB
    if (!this->theUSB->isConnected())
	{
	//pour les SMS
	// TODO : a verifier -> getSMS a peut-etre change de syntaxe
	char theSMS[200];
	bool hasSMS;

	theSMS[0] = '\0';

	if (!this->theGSM->getSMS(theSMS, &hasSMS))
	    {
	    // TODO : en cas d'erreur de lecture du SMS
	    }

	this->theAnalyzer.tCommandsAnalysis(theSMS, this->theTools);

	//pour les compteurs
	// TODO : un moyen de verifier quels compteurs sont utilises
	for (int i = 0; i <= 1; i++)
	    {
	    this->theCompteurs[i]->mOpen();
	    this->theInputMailBox.valueMeters[i].value =
		    this->theCompteurs[i]->mRead();
	    this->theRTC->readTime(
		    (char*) &(this->theInputMailBox.valueMeters[i].date.hour),
		    (char*) &(this->theInputMailBox.valueMeters[i].date.minute),
		    (char*) &(this->theInputMailBox.valueMeters[i].date.second));
	    this->theRTC->readDate(
		    (int*) &(this->theInputMailBox.valueMeters[i].date.year),
		    (char*) &(this->theInputMailBox.valueMeters[i].date.month),
		    (char*) &(this->theInputMailBox.valueMeters[i].date.day),
		    (char*) &(this->theInputMailBox.valueMeters[i].date.dayOfWeek));
	    }

	this->theCompteurs[0]->mClose();

	//pour la temperature
	this->theInputMailBox.temperature = this->theTempSensor->readTemp();

	}
    }

gInput::~gInput()
    {
    }
