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

    //assignation du contenu de la mailbox
    this->theComputeMailBox.aUserNb = this->theGInput->theInputMailBox.aUserNb;
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
	    if (*(this->theGTerminal->theTerminalMailBox.theParametersNumber)
		    == 0)
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
	    if (*(this->theGTerminal->theTerminalMailBox.theParametersNumber)
		    > 0)
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
	    this->theComputeMailBox.isSimulation = true;
	    this->theComputeMailBox.aUserSelect =
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
    //pour les SMS
    switch (*(this->theGInput->theInputMailBox.aAction))
	{
    case kCommandMah:
	if (*(this->theGInput->theInputMailBox.theParametersNumber) == 0)
	    {
	    this->theComputeMailBox.mahAuto = true;
	    }
	else
	    {
	    char aHour, aMinute, aDate, aMonth;
	    int aYear;
	    if ((sscanf(this->theGInput->theInputMailBox.theParameters[0],
		    "%d:%d", &aHour, &aMinute) == 2)
		    && (sscanf(
			    this->theGInput->theInputMailBox.theParameters[1],
			    "%d:%d:%d", &aDate, &aMonth, &aYear) == 3))
		{
		this->theRTC->setDate(aYear, aMonth, aDate, NULL);
		this->theRTC->setHour(aHour, aMinute, 0);
		}
	    }
	break;
    case kCommandDispo:
	this->theTools->setAvailability(
		this->theGInput->theInputMailBox.theParameters[0],
		this->theGInput->theInputMailBox.theParameters[1]);
	break;
    case kCommandMode:
	this->theTools->setMode(
		this->theGInput->theInputMailBox.theParameters[0]);
	break;
    case kCommandOffset:
	this->theTools->setTemperatureOffset(
		this->theGInput->theInputMailBox.theParameters[0]);
	break;
    case kCommandAlarm:
	this->theTools->setAlarmNumber(
		this->theGInput->theInputMailBox.theParameters[0],
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)));
	break;
    case kCommandLimits:
	if (*(this->theGInput->theInputMailBox.theParametersNumber) > 0)
	    {
	    if (!this->theTools->setMonthsLimits(
		    this->theGInput->theInputMailBox.theParameters,
		    *(this->theGInput->theInputMailBox.theParametersNumber),
		    UInt8(*(this->theGInput->theInputMailBox.aUserNb))))
		{
		*(this->theGInput->theInputMailBox.aAction) = kCommandError;
		}
	    }
	this->theTools->getMonthsLimits(this->theComputeMailBox.aReplySMS,
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)));
	break;
    case kCommandEtat:
	this->theTools->getEtat(this->theComputeMailBox.aReplySMS,
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)));
	break;
    case kCommandPassu:
	this->theTools->setMdPUser(
		this->theGInput->theInputMailBox.theParameters[0],
		this->theGInput->theInputMailBox.theParameters[1],
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)));
	break;
    case kCommandPassa:
	this->theTools->setMdPAdmin(
		this->theGInput->theInputMailBox.theParameters[0],
		this->theGInput->theInputMailBox.theParameters[1]);
	break;
    case kCommandSimulate:
	this->theComputeMailBox.isSimulation = true;
	this->theComputeMailBox.aUserSelect =
		*(this->theGInput->theInputMailBox.aUserNb);
	break;
    case kCommandReset:
	this->theTools->reset();
	this->theTools->saveAll();
	break;
    case kCommandMonthlyconsumption:
	this->theTools->getMonthlyConsumption(this->theComputeMailBox.aReplySMS,
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)));
	break;
    case kCommandDailyconsumption:
	this->theTools->getDailyConsumption(this->theComputeMailBox.aReplySMS,
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)));
	break;
    case kCommandDysfunction:
	// TODO : read ERRORS, envlever _OK_
	sprintf(this->theComputeMailBox.aReplySMS, "_OK_");
	break;
    case kCommandUnitName:
	this->theTools->setUnitName(
		this->theGInput->theInputMailBox.theParameters[0]);
	break;
    case kCommandPin:
	this->theTools->setPINCode(
		this->theGInput->theInputMailBox.theParameters[0]);
	break;
    case kCommandOwn:
	this->theTools->setOwnNumber(
		this->theGInput->theInputMailBox.theParameters[0]);
	break;
    default:
	break;
	}

//commandes toujours actives
    switch (*(this->theGInput->theInputMailBox.aAction))
	{
    // reponse error
    case kCommandError:
	sprintf(this->theComputeMailBox.aReplySMS, "_ERROR_");
	break;
	// reponse speciale deja ecrite dans le switch precedent
    case kCommandLimits:
    case kCommandEtat:
    case kCommandMonthlyconsumption:
    case kCommandDailyconsumption:
    case kCommandDysfunction:
	break;
	// pas de reponse
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
    case kCommandNoCommand:
    default:
	this->theComputeMailBox.aReplySMS[0] = '\0';
	break;
	}
    }

//----------------------------------------------------------------
//fonction de calcul de depassement de consommation d'eau pour les compteurs connectes
//met aussi a jour MeasuresStatments
//----------------------------------------------------------------
void gCompute::computeConsumption()
    {
    UInt8 aMonth = 0;
    UInt8 aDay = 0;
    UInt32 aValue = 0;
    UInt16 aLimitDay = 0;
    bool aOverrunConsumption = false; // variable de retour
    UInt8 j = 0;
    static UInt8 aValueBeginMonth[2] =
	{
	0, 0
	}; //consommation le premier jour du mois
    static UInt8 aPreviousDay[2] =
	{
	0, 0
	};
    static UInt32 aPreviousValue[2] =
	{
	0, 0
	};
    static bool aFullMonth[2] =
	{
	false, false
	}; // le programme n'a pas commence au milieu de ce mois
    static bool aWarningConsumption[2] =
	{
	false, false
	}; // depassement la veille - car il faut un depassement deux jours de suite pour alerter

    for (j = 0; j < 2; j++)
	{
	if (theGInput->theInputMailBox.valueMeters[j].isConnected
		|| this->theComputeMailBox.isSimulation)
	    {
	    if (0 == aPreviousDay[j]) // la premiere fois
		{
		aPreviousDay[j] =
			theGInput->theInputMailBox.valueMeters[j].date.day;
		aPreviousValue[j] =
			theGInput->theInputMailBox.valueMeters[j].value;
		aValueBeginMonth[j] = aPreviousValue[j];
		}
	    else
		{
		aDay = theGInput->theInputMailBox.valueMeters[j].date.day; // prend la date

		if (aDay != aPreviousDay[j]) // un nouveau jour est passe
		    {
		    aMonth =
			    theGInput->theInputMailBox.valueMeters[j].date.month;
		    aValue = theGInput->theInputMailBox.valueMeters[j].value;

		    //met a jour lorsqu'on est un nouveau mois
		    if (1 == aDay)
			{
			aFullMonth[j] = true;

			if (!this->theComputeMailBox.isSimulation) // ne met pas a jour les statistiques en simu
			    {
			    //enregistre la consommation du mois passe
			    if (1 == aMonth) // pour le mois de decembre
				{
				theTools->theMeasuresStatement[j]->MonthlyConsumption[11] =
					(aValue - aValueBeginMonth[j]);
				}
			    else // pour les autres mois
				{
				theTools->theMeasuresStatement[j]->MonthlyConsumption[aMonth
					- 2] = aValue - aValueBeginMonth[j];
				}

			    //efface les consommations des jours du mois passe
			    for (int i = 0; i < 31; i++)
				{
				theTools->theMeasuresStatement[j]->CurrentMonthConsumption[i] =
					0;
				}
			    }

			aValueBeginMonth[j] = aValue;
			}

		    if (!this->theComputeMailBox.isSimulation) // ne met pas a jour les statistiques en simu
			{
			theTools->theMeasuresStatement[j]->CurrentMonthConsumption[aDay
				- 2] = aValue - aPreviousValue[j]; //enregistre la consommation de la veille
			}

		    if (aFullMonth[j]) // cas ou le programme commence ce mois des le debut
			{
			//calcul de la limite du jour
			if (4 == aMonth || 6 == aMonth || 9 == aMonth
				|| 11 == aMonth) //mois à 30 jours
			    {
			    aLimitDay =
				    (UInt16) (((float) (theTools->theMonthsLimits[j]->limits[aMonth
					    - 1]
					    - (aValue - aValueBeginMonth[j]))
					    / (float) (31 - aDay)) + 0.5);
			    }
			else if (2 == aMonth && 29 == aDay) //mois à 29 jours
			    {
			    aLimitDay =
				    (UInt16) ((float) (theTools->theMonthsLimits[j]->limits[aMonth
					    - 1]
					    - (aValue - aValueBeginMonth[j]))
					    + 0.5);
			    }
			else if (2 == aMonth) //mois à 28 jours
			    {
			    aLimitDay =
				    (UInt16) (((float) (theTools->theMonthsLimits[j]->limits[aMonth
					    - 1]
					    - (aValue - aValueBeginMonth[j]))
					    / (float) (29 - aDay)) + 0.5);
			    }
			else //mois à 31 jours
			    {
			    aLimitDay =
				    (UInt16) (((float) (theTools->theMonthsLimits[j]->limits[aMonth
					    - 1]
					    - (aValue - aValueBeginMonth[j]))
					    / (float) (32 - aDay)) + 0.5);
			    }
			}
		    else // le programme a commence au milieu de ce mois, il faut calculer la limite differemment
			{
			aLimitDay =
				(UInt16) ((float) theTools->theMonthsLimits[j]->limits[aMonth
					- 1] / (float) 30);
			}

		    this->theComputeMailBox.indexOverrunSimulation =
			    (UInt16) ((float) (-62 + 2 * aDay - 31 * aValue
				    + aDay * aValue
				    - theTools->theMonthsLimits[j]->limits[aMonth
					    - 1]) / (float) (-32 + aDay)); // calcul d'indice pour le jour prochain pour avoir un depassement

		    if (aLimitDay < (aValue - aPreviousValue[j])) //calcul si depasse la limite quotidienne
			{
			if (aWarningConsumption[j])
			    {
			    ///this->theComputeMailBox.overrunConsumption = true;
			    }
			else // premier jour de depassement de la limite
			    {
			    aWarningConsumption[j] = true;
			    }
			}
		    else // pas de depassement
			{
			aWarningConsumption[j] = false;
			}

		    aPreviousValue[j] = aValue;
		    aPreviousDay[j] = aDay;
		    }
		}
	    }
	}
    }

void gCompute::computeIsFinished()
    {
    if ((!this->theComputeMailBox.mahAuto)
	    && (!this->theComputeMailBox.isSimulation)
	    && (!this->theGInput->theInputMailBox.aAction == kCommandNoCommand)
	    && (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		    != kTerminalDisconnected))
	{
	this->theComputeMailBox.isWorkFinished = true;
	}
    else
	{
	this->theComputeMailBox.isWorkFinished = false;
	}
    }

gCompute::~gCompute()
    {
    }
