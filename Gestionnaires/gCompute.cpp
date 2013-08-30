#include <string>
#include <assert.h>

#include "gCompute.h"
#include "gTerminal.h"
#include "tCommandsAnalyzer.h"

//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entrées
//----------------------------------------------------------------
gCompute::gCompute(gInput* theGInput, gTerminal* theGTerminal,
	tToolsCluster* theTools)
    {
    this->theGInput = theGInput;
    this->theGTerminal = theGTerminal;
    }

void gCompute::setup()
    {
    }

void gCompute::execute()
    {
    this->computeTerminal();

    this->computeSMS();

    this->computeConsumption();
    }

void gCompute::computeTerminal()
    {
    //pour gTerminal
    //TODO adapter le message de retour suivant la commande
    switch (*(this->theGTerminal->theTerminalMailBox.aAction))
	{
    case kCommandDisconnect:
	sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	break;
    case kCommandConnect:
	sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	break;
    case kCommandError:
	sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_ERROR_\r\n");
	break;
    case kCommandMah:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandDispo:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandMode:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandOffset:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandAlarme:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandLimites:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandEtat:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandPassu:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandPassa:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandSimulate:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandReset:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandMonths:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandDays:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandDysfunction:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandUnitName:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandPin:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandOwn:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    default:
	this->theGTerminal->theTerminalMailBox.aReply[0] = '\0';
	break;
	}
    }

void gCompute::computeSMS()
    {
    }

void gCompute::computeConsumption()
    {
    }
