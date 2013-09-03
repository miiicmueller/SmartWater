#include "gTerminal.h"

#include <string>
#include <assert.h>
#include <stdio.h>

//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entrees
//----------------------------------------------------------------
gTerminal::gTerminal(tToolsCluster* theTools, mUSB* theUSB)
    {
    this->theUSB = theUSB;
    this->theGInput = theGInput;
    this->theTools = theTools;
    this->sessionOpen = false;
    }

//----------------------------------------------------------------
//setup()
//
//configuration du terminal
//----------------------------------------------------------------
void gTerminal::setup()
    {
    //initialisation des attributs
    this->aTerminalState = kTerminalDisconnected;

    //assignation du contenu de la mailbox
    this->theTerminalMailBox.aTerminalState = &(this->aTerminalState);
    this->theTerminalMailBox.aUserNb =
	    &(this->theAnalyzer.aCommandResult.aUserNb);
    this->theTerminalMailBox.aAction =
	    &(this->theAnalyzer.aCommandResult.aCommandEnum);
    this->theTerminalMailBox.theParametersNumber =
	    &(this->theAnalyzer.aCommandResult.parametersNumber);

    for (int i = 0; i < 12; i++)
	{
	this->theTerminalMailBox.theParameters[i] =
		this->theAnalyzer.aCommandBrut.theParameters[i];
	}

    }

//----------------------------------------------------------------
//execute()
//
//execution de la communication avec l'USB (machine d'etat, non-blocant)
//----------------------------------------------------------------
void gTerminal::execute()
    {
    char aMessage[100];
    aMessage[0] = '\0';

    if (!this->theUSB->isConnected())
	{
	this->aTerminalState = kTerminalDisconnected;
	}

    if (this->aTerminalState != kTerminalDisconnected)
	{
	this->theUSB->getCommand(aMessage);
	this->theAnalyzer.tCommandsAnalysis(aMessage, this->theTools);
	}

    switch (this->aTerminalState)
	{
    case kTerminalDisconnected:
	if (this->theUSB->isConnected())
	    {
	    this->aTerminalState = kTerminalConnected;
	    }
	break;
    case kTerminalConnected:
	if ((this->theAnalyzer.aStateEnum == kComplete)
		&& (this->theAnalyzer.aCommandResult.aCommandEnum
			== kCommandConnect))
	    {
	    this->aTerminalState = kTerminalSessionOpen;
	    }
	break;
    case kTerminalSessionOpen:
	if ((this->theAnalyzer.aStateEnum == kComplete)
		&& (this->theAnalyzer.aCommandResult.aCommandEnum
			== kCommandDisconnect))
	    {
	    this->aTerminalState = kTerminalConnected;
	    }
	break;
    default:
	this->aTerminalState = kTerminalDisconnected;
	break;
	}
    }

