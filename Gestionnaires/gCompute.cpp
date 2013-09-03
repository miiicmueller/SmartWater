#include <string>
#include <assert.h>

#include "gCompute.h"

//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entrées
//----------------------------------------------------------------
gCompute::gCompute(gInput* theGInput, gTerminal* theGTerminal,
	tToolsCluster* theTools, mRTC* theRTC)
    {
    this->theGInput = theGInput;
    this->theGTerminal = theGTerminal;
    this->theTools = theTools;
    this->theRTC = theRTC;
    }

void gCompute::setup()
    {
    }

void gCompute::execute()
    {
    this->computeTerminal();

    this->computeSMS();

    //this->computeConsumption(); //TODO adapter

    this->computeIsFinished();
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
		this->theComputeMailBox.mahAuto = true;
		}
	    else
		{
		char aHour, aMinute, aDate, aMonth;
		int aYear;
		if ((sscanf(
			this->theGTerminal->theTerminalMailBox.theParameters[0],
			"%d:%d", &aHour, &aMinute) == 2)
			&& (sscanf(
				this->theGTerminal->theTerminalMailBox.theParameters[1],
				"%d:%d:%d", &aDate, &aMonth, &aYear) == 3))
		    {
		    this->theRTC->setDate(aYear, aMonth, aDate, NULL);
		    this->theRTC->setHour(aHour, aMinute, 0);
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
	    this->theTools->getMonthsLimits(this->theComputeMailBox.aReplyUSB,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandEtat:
	    this->theTools->getEtat(this->theComputeMailBox.aReplyUSB,
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
	    this->theComputeMailBox.simulation = true;
	    this->theComputeMailBox.aUserSimulation =
		    *(this->theGTerminal->theTerminalMailBox.aUserNb);
	    break;
	case kCommandReset:
	    this->theTools->reset();
	    this->theTools->saveAll();
	    break;
	case kCommandMonthlyconsumption:
	    this->theTools->getMonthlyConsumption(
		    this->theComputeMailBox.aReplyUSB,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandDailyconsumption:
	    this->theTools->getDailyConsumption(
		    this->theComputeMailBox.aReplyUSB,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandDysfunction:
	    // TODO : read ERRORS, envlever _OK_
	    sprintf(this->theComputeMailBox.aReplyUSB, "_OK_");
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
	sprintf(this->theComputeMailBox.aReplyUSB, "_OK_");
	break;
	// reponse error
    case kCommandError:
	sprintf(this->theComputeMailBox.aReplyUSB, "_ERROR_");
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
	this->theComputeMailBox.aReplyUSB[0] = '\0';
	break;
	}
    }

void gCompute::computeSMS()
    {
    }

//----------------------------------------------------------------
//fonction de calcul de depassement de consommation d'eau
//
//retourne true s'il y a un depassement de consommation
//----------------------------------------------------------------
bool gCompute::computeConsumption(iMeterChannel aChannel)
    {
    UInt8 aMonth = 0;
    static UInt8 aPreviousDay = 0;
    UInt8 aDay = 0;
    static UInt8 aValueBeginMonth = 0; //consommation le premier jour du mois
    static UInt32 aPreviousValue = 0;
    UInt32 aValue = 0;
    UInt8 aTemp = 0;
    bool aWarningConsumption = false;
    bool aRet = false;

//    if (kMeterSimulation != aChannel)
//	{
//	if (0 == aPreviousDay) // la premiere fois
//	    {
//	    aDay = theGInput->valueMeters->date.day;
//	    aPreviousDay = aDay;
//	    aPreviousValue = theGInput->valueMeters->value;
//	    }
//	else
//	    {
//	    aDay = theGInput->valueMeters->date.day; // prend la nouvelle date
//
//	    if (aDay != aPreviousDay) // un nouveau jour est passe
//		{
//		aValue = theGInput->valueMeters->value;
//
//		if (1 == aDay) //met a jour pour le premier jour du mois
//		    {
//		    aValueBeginMonth = aValue;
//		    }
//
//		if (ceil(
//			(tMonthsLimits::limits[aMonth - 1]
//				- (aValue - aValueBeginMonth)) / (32 - aDay))
//			< (aValue - aPreviousValue)) //calcul si depasse la limite quotidienne
//		    {
//		    if (aWarningConsumption)
//			{
//			this->overrunConsumption = true;
//			}
//		    else // premier jour de depassement de la limite
//			{
//			aWarningConsumption = true;
//			}
//		    }
//		else // pas de depassement
//		    {
//		    aWarningConsumption = false;
//		    this->overrunConsumption = false;
//		    }
//
//		aPreviousValue = aValue;
//		aPreviousDay = aDay;
//		}
//	    }
//	}
//    else // il s'agit d'un compteur de simulation
//	{
//
//	}
    return aRet;
    }

void gCompute::computeIsFinished()
    {
    // TODO : enlever les conditions en commentaire
    if ((!this->theComputeMailBox.mahAuto)
	    && (!this->theComputeMailBox.simulation)/*&&(!this->theGInput->gInputMailBox.hasSMS)&&(!this->theGTerminal->gTerminalMailBox.aTerminalState==kTerminalDisconnected)*/)
	{
	this->theComputeMailBox.isWorkFinished = true;
	}
    else
	{
	this->theComputeMailBox.isWorkFinished = false;
	}
    }
