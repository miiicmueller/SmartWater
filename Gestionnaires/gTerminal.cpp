#include "gTerminal.h"

#include <string>
#include <assert.h>
#include <stdio.h>

//OBLIGATOIRE POUR L'USB
volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation

//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entrees
//----------------------------------------------------------------
//gTerminal::gTerminal(tToolsCluster* theTools)
//    {
//    this->theUSB = new mUSB(&bCDCDataReceived_event);
//    this->theGInput = theGInput;
//    this->theTools = theTools;
//    this->sessionOpen = false;
//    }

//----------------------------------------------------------------
//setup()
//
//configuration du terminal
//----------------------------------------------------------------
void gTerminal::setup()
    {
//    //initialisation des attributs
//    this->aTerminalState = kTerminalDisconnected;
//    this->aReply[0] = '\0';
//
//    //assignation du contenu de la mailbox
//    this->theTerminalMailBox.aReply = this->aReply;
//    this->theTerminalMailBox.aTerminalState = &(this->aTerminalState);
//    this->theTerminalMailBox.aAction =
//	    &(this->theAnalyzer.aCommandResult.aCommandEnum);
//    this->theTerminalMailBox.theParametersNumber =
//	    &(this->theAnalyzer.aCommandResult.parametersNumber);
//
//    for (int i = 0; i < 12; i++)
//	{
//	this->theTerminalMailBox.theParameters[i] =
//		this->theAnalyzer.aCommandBrut.theParameters[i];
//	}

    }

//----------------------------------------------------------------
//execute()
//
//execution de la communication avec l'USB (machine d'etat, non-blocant)
//----------------------------------------------------------------
void gTerminal::execute()
    {
//    char aMessage[100];
//    aMessage[0] = '\0';
//
//    this->theUSB->getCommand(aMessage);
//
//    //TODO pour le debuggage, a enlever
//    if (aMessage[0] != '\0')
//	{
//	nop();
//	}
//    this->theAnalyzer.tCommandAnalysis(aMessage, this->theTools);
//
//    if (!this->theUSB->isConnected())
//	{
//	this->aTerminalState = kTerminalDisconnected;
//	}
//
//    switch (this->aTerminalState)
//	{
//    case kTerminalDisconnected:
//	if (this->theUSB->isConnected())
//	    {
//	    this->aTerminalState = kTerminalConnected;
//	    }
//	break;
//    case kTerminalConnected:
//	if ((this->theAnalyzer.aState == kComplete)
//		&& (this->theAnalyzer.aCommandResult.aCommandEnum
//			== kCommandConnect))
//	    {
//	    this->aTerminalState = kTerminalSessionOpen;
//	    }
//	break;
//    case kTerminalSessionOpen:
//	if ((this->theAnalyzer.aState == kComplete)
//		&& (this->theAnalyzer.aCommandResult.aCommandEnum
//			== kCommandDisconnect))
//	    {
//	    this->aTerminalState = kTerminalConnected;
//	    }
//	break;
//    default:
//	this->aTerminalState = kTerminalDisconnected;
//	break;
//	}
//
//    if (this->aReply[0] != '\0')
//	{
//	this->theUSB->sendReply(aReply);
//	}
    }

