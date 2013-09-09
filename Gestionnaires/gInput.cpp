#include <string>
#include <assert.h>

#include "gInput.h"

gInput::gInput(mGSM* theGSM, mCompteur* theCompteurs[3], mRTC* theRTC,
	mTempSensor* theTempSensor, tToolsCluster* theTools, mUSB* theUSB)
    {
    this->theGSM = theGSM;
    this->theRTC = theRTC;
    this->theTempSensor = theTempSensor;
    this->theCompteurs[0] = theCompteurs[0];
    this->theCompteurs[1] = theCompteurs[1];
    this->theCompteurs[2] = theCompteurs[2];
    this->theTools = theTools;
    this->theUSB = theUSB;

    this->theInputMailBox.date = new tDate();

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
    this->theInputMailBox.date->year = 1;
    this->theInputMailBox.date->month = 1;
    this->theInputMailBox.date->day = 1;
    this->theInputMailBox.date->hour = 0;
    this->theInputMailBox.date->minute = 0;
    this->theInputMailBox.date->second = 0;

    this->theInputMailBox.theCredit = 0;
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

	if (!this->theGSM->getSMS(theSMS, &hasSMS,
		this->theInputMailBox.aReplyNb))
	    {
	    // TODO : en cas d'erreur de lecture du SMS
	    theSMS[0] = '\0';
	    }

	this->theAnalyzer.tCommandsAnalysis(theSMS, this->theTools);

	//lecture de l'heure
	this->theRTC->readTime((char*) &(this->theInputMailBox.date->hour),
		(char*) &(this->theInputMailBox.date->minute),
		(char*) &(this->theInputMailBox.date->second));
	this->theRTC->readDate((int*) &(this->theInputMailBox.date->year),
		(char*) &(this->theInputMailBox.date->month),
		(char*) &(this->theInputMailBox.date->day),
		(char*) &(this->theInputMailBox.date->dayOfWeek));

	//pour les compteurs
	for (int i = 0; i <= 1; i++)
	    {
	    this->theCompteurs[i]->mOpen();

	    if (this->theCompteurs[i]->mRead(
		    &(this->theTools->theCompteur[i]->aData.aDataStruct.aIndex)))
		{
		this->theTools->theCompteur[i]->isConnected = true;
		}
	    else
		{
		this->theTools->theCompteur[i]->isConnected = false;
		}
	    }

	if (this->theInputMailBox.isSimulation)
	    {
	    this->theCompteurs[2]->mOpen();

	    this->theCompteurs[2]->simulationCpt(
		    this->theInputMailBox.indexOverrunSimulation);

	    if (this->theCompteurs[2]->mRead(
		    &(this->theTools->theCompteur[2]->aData.aDataStruct.aIndex)))
		{
		this->theTools->theCompteur[2]->isConnected = true;
		}
	    else
		{
		this->theTools->theCompteur[2]->isConnected = false;
		}
	    }

	this->theCompteurs[0]->mClose();

	//pour la temperature
	UInt16 temp = this->theTempSensor->readTemp();
	this->theInputMailBox.temperature.aFakeFloat.integer = temp >> 4;
	this->theInputMailBox.temperature.aFakeFloat.decimal = ((temp % 16)
		* 100) >> 4;
	}
    }

gInput::~gInput()
    {
    }
