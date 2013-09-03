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
gCompute::gCompute(gInput* theGInput)
    {
    this->theGInput = theGInput;
    }

void gCompute::setup()
    {
    }

void gCompute::execute()
    {
    this->computeTerminal();

    this->computeSMS();

    //this->computeConsumption(); //TODO adapter
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
    case kCommandAlarm:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandLimits:
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
    case kCommandMonthlyconsumption:
	if (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		== kTerminalSessionOpen)
	    {
	    sprintf(this->theGTerminal->theTerminalMailBox.aReply, "_OK_\r\n");
	    }
	break;
    case kCommandDailyconsumption:
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

