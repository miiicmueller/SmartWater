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
    this->theTools = theTools;
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

    //commandes actives seulement si la session est ouverte
    if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
	    == kTerminalSessionOpen)
	{
	switch (*(this->theGTerminal->theTerminalMailBox.aAction))
	    {
	case kCommandMah:
	    if (this->theGTerminal->theTerminalMailBox.theParametersNumber == 0)
		{
		// TODO : mise a l'heure automatique
		}
	    else
		{
		UInt8 aHour, aMinute, aDate, aMonth, aYear;
		if ((sscanf(
			this->theGTerminal->theTerminalMailBox.theParameters[0],
			"%d:%d", &aHour, &aMinute) == 2)
			&& (sscanf(
				this->theGTerminal->theTerminalMailBox.theParameters[1],
				"%d:%d:%d", &aDate, &aMonth, &aYear) == 3))
		    {
		    // TODO : mise a l'heure avec les parametres lus
		    }
		else
		    {
		    *(this->theGTerminal->theTerminalMailBox.aAction) =
			    kCommandError;
		    }
		}
	    break;
	case kCommandDispo:
	    if (!this->theTools->setAvailability(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    this->theGTerminal->theTerminalMailBox.theParameters[1]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	case kCommandMode:
	    if (!this->theTools->setMode(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	case kCommandOffset:
	    if (!this->theTools->setTemperatureOffset(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	case kCommandAlarm:
	    if (!this->theTools->setAlarmNumber(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb))))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	case kCommandLimits:
	    if (this->theGTerminal->theTerminalMailBox.theParametersNumber > 0)
		{
		if (!this->theTools->setMonthsLimits(
			this->theGTerminal->theTerminalMailBox.theParameters,
			*(this->theGTerminal->theTerminalMailBox.theParametersNumber),
			UInt8(
				*(this->theGTerminal->theTerminalMailBox.aUserNb))))
		    {
		    *(this->theGTerminal->theTerminalMailBox.aAction) =
			    kCommandError;
		    }
		}
	    this->theTools->getMonthsLimits(
		    this->theGTerminal->theTerminalMailBox.aReply,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandEtat:
	    this->theTools->getEtat(
		    this->theGTerminal->theTerminalMailBox.aReply,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandPassu:
	    if (!this->theTools->setMdPUser(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    this->theGTerminal->theTerminalMailBox.theParameters[1],
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb))))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	case kCommandPassa:
	    if (!this->theTools->setMdPAdmin(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    this->theGTerminal->theTerminalMailBox.theParameters[1]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	case kCommandSimulate:
	    // TODO : mettre en mode simulate
	    break;
	case kCommandReset:
	    // TODO : reset des parametres
	    break;
	case kCommandMonthlyconsumption:
	    this->theTools->getMonthlyConsumption(
		    this->theGTerminal->theTerminalMailBox.aReply,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandDailyconsumption:
	    this->theTools->getDailyConsumption(
		    this->theGTerminal->theTerminalMailBox.aReply,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandDysfunction:
	    // TODO : read ERRORS
	    break;
	case kCommandUnitName:
	    this->theTools->setUnitName(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]);
	    break;
	case kCommandPin:
	    if (!this->theTools->setPINCode(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	case kCommandOwn:
	    if (!this->theTools->setOwnNumber(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError;
		}
	    break;
	default:
	    break;
	    }
	}

//commandes toujours actives
    switch (*(this->theGTerminal->theTerminalMailBox.aAction))
	{
// reponse ok
    case kCommandDisconnect:
    case kCommandConnect:
    case kCommandUnitName:
    case kCommandPin:
    case kCommandOwn:
    case kCommandMah:
    case kCommandDispo:
    case kCommandMode:
    case kCommandOffset:
    case kCommandAlarm:
    case kCommandPassu:
    case kCommandPassa:
    case kCommandSimulate:
    case kCommandReset:
	sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_");
	break;
	// reponse error
    case kCommandError:
	sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_ERROR_");
	break;
	// reponse speciale deja ecrite dans le switch precedent
    case kCommandLimits:
    case kCommandEtat:
    case kCommandMonthlyconsumption:
    case kCommandDailyconsumption:
    case kCommandDysfunction:
	break;
	// pas de reponse
    case kCommandNoCommand:
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
