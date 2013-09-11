#include <string>
#include <assert.h>

#include "gCompute.h"

gComputeMailBox gCompute::theComputeMailBox;

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
    this->theComputeMailBox.aReplyNb =
	    this->theGInput->theInputMailBox.aReplyNb;
    this->theComputeMailBox.theDate = this->theGInput->theInputMailBox.date;

    //initilisation des attributs de computeConsumption
    aMonth = 0;
    aDay = 0;
    aValue = 0;
    aLimitDay = 0;
    j = 0;
    aFullMonth = false;
    aPreviousValue[0] = 0;
    aPreviousValue[1] = 0;
    aPreviousValue[2] = 0;
    aValueBeginMonth[0] = 0;
    aValueBeginMonth[1] = 0;
    aValueBeginMonth[2] = 0;
    aPreviousDay = 0;
    }

void gCompute::setup()
    {
    this->theComputeMailBox.hasOverrun[0] = false;
    this->theComputeMailBox.hasOverrun[1] = false;
    this->theGInput->theInputMailBox.isSimulation = false;
    }

void gCompute::execute()
    {
    this->computeTerminal();

    this->computeSMS();

    this->computeConsumption();

    this->computeIsFinished();

    this->computeCredit();
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
			    kCommandError2;
		    }
		}
	    break;
	case kCommandDispo:
	    if (!this->theTools->setAvailability(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    this->theGTerminal->theTerminalMailBox.theParameters[1]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError2;
		}
	    break;
	case kCommandMode:
	    if (!this->theTools->setMode(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError2;
		}
	    break;
	case kCommandOffset:
	    if (!this->theTools->setTemperatureOffset(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError2;
		}
	    break;
	case kCommandAlarm:
	    if (!this->theTools->setAlarmNumber(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb))))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError2;
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
			    kCommandError2;
		    }
		}
	    this->theTools->getMonthsLimits(this->theComputeMailBox.aReplyUSB,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)));
	    break;
	case kCommandEtat:
	    this->theTools->getEtat(this->theComputeMailBox.aReplyUSB,
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb)),
		    this->theGInput->theInputMailBox.date,
		    this->theGInput->theInputMailBox.theCredit,
		    this->theGInput->theInputMailBox.temperature);
	    break;
	case kCommandPassu:
	    if (!this->theTools->setMdPUser(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    this->theGTerminal->theTerminalMailBox.theParameters[1],
		    UInt8(*(this->theGTerminal->theTerminalMailBox.aUserNb))))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError2;
		}
	    break;
	case kCommandPassa:
	    if (!this->theTools->setMdPAdmin(
		    this->theGTerminal->theTerminalMailBox.theParameters[0],
		    this->theGTerminal->theTerminalMailBox.theParameters[1]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError2;
		}
	    break;
	case kCommandSimulate:
	    this->theGInput->theInputMailBox.isSimulation = true;
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
			kCommandError2;
		}
	    break;
	case kCommandOwn:
	    if (!this->theTools->setOwnNumber(
		    this->theGTerminal->theTerminalMailBox.theParameters[0]))
		{
		*(this->theGTerminal->theTerminalMailBox.aAction) =
			kCommandError2;
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
    case kCommandError1:
    case kCommandError2:
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
	    else
		{
		*(this->theGInput->theInputMailBox.aAction) = kCommandError2;
		}
	    }
	break;
    case kCommandDispo:
	if (!this->theTools->setAvailability(
		this->theGInput->theInputMailBox.theParameters[0],
		this->theGInput->theInputMailBox.theParameters[1]))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandMode:
	if (!this->theTools->setMode(
		this->theGInput->theInputMailBox.theParameters[0]))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandOffset:
	if (!this->theTools->setTemperatureOffset(
		this->theGInput->theInputMailBox.theParameters[0]))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandAlarm:
	if (!this->theTools->setAlarmNumber(
		this->theGInput->theInputMailBox.theParameters[0],
		UInt8(*(this->theGInput->theInputMailBox.aUserNb))))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandLimits:
	if (*(this->theGInput->theInputMailBox.theParametersNumber) > 0)
	    {
	    if (!this->theTools->setMonthsLimits(
		    this->theGInput->theInputMailBox.theParameters,
		    *(this->theGInput->theInputMailBox.theParametersNumber),
		    UInt8(*(this->theGInput->theInputMailBox.aUserNb))))
		{
		*(this->theGInput->theInputMailBox.aAction) = kCommandError2;
		}
	    }
	this->theTools->getMonthsLimits(this->theComputeMailBox.aReplySMS,
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)));
	break;
    case kCommandEtat:
	this->theTools->getEtat(this->theComputeMailBox.aReplySMS,
		UInt8(*(this->theGInput->theInputMailBox.aUserNb)),
		this->theGInput->theInputMailBox.date,
		this->theGInput->theInputMailBox.theCredit,
		this->theGInput->theInputMailBox.temperature);
	break;
    case kCommandPassu:
	if (!this->theTools->setMdPUser(
		this->theGInput->theInputMailBox.theParameters[0],
		this->theGInput->theInputMailBox.theParameters[1],
		UInt8(*(this->theGInput->theInputMailBox.aUserNb))))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandPassa:
	if (!this->theTools->setMdPAdmin(
		this->theGInput->theInputMailBox.theParameters[0],
		this->theGInput->theInputMailBox.theParameters[1]))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandSimulate:
	this->theGInput->theInputMailBox.isSimulation = true;
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
	if (!this->theTools->setUnitName(
		this->theGInput->theInputMailBox.theParameters[0]))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandPin:
	if (!this->theTools->setPINCode(
		this->theGInput->theInputMailBox.theParameters[0]))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    case kCommandOwn:
	if (!this->theTools->setOwnNumber(
		this->theGInput->theInputMailBox.theParameters[0]))
	    {
	    *(this->theGInput->theInputMailBox.aAction) = kCommandError2;
	    }
	break;
    default:
	break;
	}

//commandes toujours actives
    switch (*(this->theGInput->theInputMailBox.aAction))
	{
    // reponse error
    case kCommandError2:
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
    case kCommandError1:
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

    *(this->theGInput->theInputMailBox.aAction) = kCommandNoCommand;
    }

//----------------------------------------------------------------
//fonction de calcul de depassement de consommation d'eau pour les compteurs connectes
//met aussi a jour MeasuresStatments
//----------------------------------------------------------------
void gCompute::computeConsumption()
    {
    UInt8 aChoiceMeterSimulation = 0;
    static bool aWarningConsumption[3] =
	{
	false, false, false
	};

    //controle la consommation des compteurs physiques
    for (j = 0; j < 2; j++) //pour les deux compteurs
	{
	if (theTools->theCompteur[j]->isConnected
		&& !theGInput->theInputMailBox.isSimulation)
	    {
	    if (0 == aPreviousDay) // la premiere fois
		{
		aPreviousDay = theGInput->theInputMailBox.date->day;
		aPreviousValue[j] =
			theTools->theCompteur[j]->aData.aDataStruct.aIndex;
		aValueBeginMonth[j] = aPreviousValue[j];
		}
	    else
		{
		aDay = theGInput->theInputMailBox.date->day; // prend la date
		aMonth = theGInput->theInputMailBox.date->month;
		aValue = theTools->theCompteur[j]->aData.aDataStruct.aIndex;

		saveMeasurements();

		computeLimitDay();

		//calcul si depasse la limite quotidienne
		if (aLimitDay < (aValue - aPreviousValue[j]))
		    {
		    if (aWarningConsumption[j]) // valeur depassee
			{
			this->theComputeMailBox.hasOverrun[j] = true;
			this->theComputeMailBox.overrunLimit[j] = aLimitDay;
			this->theComputeMailBox.overrunConsumption[j] = aValue
				- aPreviousValue[j];
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

		if (aDay != aPreviousDay)
		    {
		    aPreviousValue[j] = aValue;
		    aPreviousDay = aDay;
		    }
		}
	    }
	}

    //controle la consommation du compteur de simulation
    if (theGInput->theInputMailBox.isSimulation)
	{
	static bool aFirstRun = true;

	if (this->theGInput->theInputMailBox.simulateCompteur == false)
	    {
	    this->theGInput->theInputMailBox.simulateCompteur = true;

	    if (aFirstRun)
		{
		aFirstRun = false;
		aDay = theGInput->theInputMailBox.date->day; // prend la date
		}

	    if (1 == aDay) //met a jour lorsqu'on est un nouveau mois
		{
		aFullMonth = true;
		}

	    j = 2;
	    aChoiceMeterSimulation = theComputeMailBox.aUserSelect - 1;
	    aValue = theTools->theCompteur[2]->aData.aDataStruct.aIndex;
	    aMonth = theGInput->theInputMailBox.date->month;

	    if (0 == aValueBeginMonth[2])
		{
		aValueBeginMonth[2] = aValue;
		}

	    aDay++;
	    aPreviousDay = aDay - 1;

	    computeLimitDay();
	    computeLimitNextDay();

	    //calcul si depasse la limite quotidienne
	    if ((aLimitDay < (aValue - aPreviousValue[j]))
		    && (0 != aPreviousValue[j]))
		{
		if (aWarningConsumption[j]) // valeur depassee
		    {
		    this->theComputeMailBox.hasOverrun[aChoiceMeterSimulation] =
			    true;
		    this->theComputeMailBox.overrunLimit[aChoiceMeterSimulation] =
			    aLimitDay;
		    this->theComputeMailBox.overrunConsumption[aChoiceMeterSimulation] =
			    aValue - aPreviousValue[j];
		    aPreviousDay = 0;
		    aValueBeginMonth[2] = 0;
		    this->theGInput->theInputMailBox.isSimulation = false;
		    aFirstRun = true;
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
	    }
	}
    }

void gCompute::computeIsFinished()
    {
    if ((!this->theComputeMailBox.mahAuto)
	    && (!this->theGInput->theInputMailBox.isSimulation)
	    && (*(this->theGInput->theInputMailBox.aAction) == kCommandNoCommand)
	    && (*(this->theGTerminal->theTerminalMailBox.aTerminalState)
		    == kTerminalDisconnected))
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

//----------------------------------------------------------------
//enregistre les mesures mensuelles et journalieres
//----------------------------------------------------------------
void gCompute::saveMeasurements()
    {
    UInt8 i = 0;

// enregistre le mois
    if (1 == aDay) //met a jour lorsqu'on est un nouveau mois
	{
	aFullMonth = true;

	//efface du tableau, les jours du mois n'existant pas (p. ex. le 30 fevrier)
	for (i = aPreviousDay; i < 31; i++)
	    {
	    theTools->theMeasuresStatement[j]->aData.aDataStruct.CurrentMonthConsumption[i] =
		    0;
	    }

	//enregistre la consommation du mois passe
	if (1 == aMonth) // pour le mois de decembre
	    {
	    theTools->theMeasuresStatement[j]->aData.aDataStruct.MonthlyConsumption[11] =
		    (aValue - aValueBeginMonth[j]);
	    }
	else // pour les autres mois
	    {
	    theTools->theMeasuresStatement[j]->aData.aDataStruct.MonthlyConsumption[aMonth
		    - 2] = aValue - aValueBeginMonth[j];
	    }

	aValueBeginMonth[j] = aValue;
	}
    else
	{
	//enregistre la consommation du mois courant
	theTools->theMeasuresStatement[j]->aData.aDataStruct.MonthlyConsumption[aMonth
		- 1] = aValue - aValueBeginMonth[j];
	}

// enregistre le jour
    if (aDay != aPreviousDay)
	{
	//enregistre la consommation du jour passe
	theTools->theMeasuresStatement[j]->aData.aDataStruct.CurrentMonthConsumption[aPreviousDay
		- 1] = aValue - aPreviousValue[j];
	}
    else
	{
	//enregistre la consommation du jour courant
	theTools->theMeasuresStatement[j]->aData.aDataStruct.CurrentMonthConsumption[aDay
		- 1] = aValue - aPreviousValue[j];
	}
    }

//----------------------------------------------------------------
//calcul la limite journaliere de consommation d'eau
//----------------------------------------------------------------
void gCompute::computeLimitDay()
    {
    UInt8 k = 0;
    if (theGInput->theInputMailBox.isSimulation)
	{
	k = j + theComputeMailBox.aUserSelect - 3; //place l'index sur le compteur selectionne en simulation
	}
    else
	{
	k = j;
	}
    if (aFullMonth) // cas ou les mesures sont faites des le premier jour du mois
	{
	//calcul de la limite du jour
	if (4 == aMonth || 6 == aMonth || 9 == aMonth || 11 == aMonth) //mois à 30 jours
	    {
	    aLimitDay =
		    (UInt16) (((float) (theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
			    - 1] - (aValue - aValueBeginMonth[j]))
			    / (float) (31 - aDay)) + 0.5);
	    }
	else if (2 == aMonth && 29 == aDay) //mois à 29 jours
	    {
	    aLimitDay =
		    (UInt16) ((float) (theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
			    - 1] - (aValue - aValueBeginMonth[j])) + 0.5);
	    }
	else if (2 == aMonth) //mois à 28 jours
	    {
	    aLimitDay =
		    (UInt16) (((float) (theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
			    - 1] - (aValue - aValueBeginMonth[j]))
			    / (float) (29 - aDay)) + 0.5);
	    }
	else //mois à 31 jours
	    {
	    aLimitDay =
		    (UInt16) (((float) (theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
			    - 1] - (aValue - aValueBeginMonth[j]))
			    / (float) (32 - aDay)) + 0.5);
	    }
	}
    else // cas ou le programme a commence au milieu d'un mois
	{
	aLimitDay =
		(UInt16) ((float) theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
			- 1] / (float) 30);
	}
    }

//----------------------------------------------------------------
//calcul la limite journaliere qu'il ne faudra pas depasser demain
// -> cette fonction est uniquement utilisee pour la simulation de depassement de consommation,
// pour connaitre quel doit etre l'indice pour avoir un depassement de consommation
//----------------------------------------------------------------
void gCompute::computeLimitNextDay()
    {
    UInt8 k = 0;
    if (theGInput->theInputMailBox.isSimulation)
	{
	k = j + theComputeMailBox.aUserSelect - 3; //place l'index sur le compteur selectionne en simulation
	}
    else
	{
	k = j;
	}
    if (aFullMonth) // cas ou les mesures sont faites des le premier jour du mois
	{
	if (4 == aMonth || 6 == aMonth || 9 == aMonth || 11 == aMonth) //mois à 30 jours
	    {
	    theGInput->theInputMailBox.indexOverrunSimulation =
		    aValueBeginMonth[j]
			    + (UInt32) ((float) (30
				    * (aValue - aValueBeginMonth[j])
				    - aDay * (aValue - aValueBeginMonth[j])
				    + theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
					    - 1]) / (float) (31 - aDay));
	    }
	else if (2 == aMonth && 29 == aDay) //mois à 29 jours
	    {
	    theGInput->theInputMailBox.indexOverrunSimulation =
		    aValueBeginMonth[j]
			    + (UInt32) ((float) (29
				    * (aValue - aValueBeginMonth[j])
				    - aDay * (aValue - aValueBeginMonth[j])
				    + theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
					    - 1]) / (float) (30 - aDay));
	    }
	else if (2 == aMonth) //mois à 28 jours
	    {
	    theGInput->theInputMailBox.indexOverrunSimulation =
		    aValueBeginMonth[j]
			    + (UInt32) ((float) (28
				    * (aValue - aValueBeginMonth[j])
				    - aDay * (aValue - aValueBeginMonth[j])
				    + theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
					    - 1]) / (float) (29 - aDay));
	    }
	else //mois à 31 jours
	    {
	    theGInput->theInputMailBox.indexOverrunSimulation =
		    aValueBeginMonth[j]
			    + (UInt32) ((float) (31
				    * (aValue - aValueBeginMonth[j])
				    - aDay * (aValue - aValueBeginMonth[j])
				    + theTools->theMonthsLimits[k]->aData.aDataStruct.limits[aMonth
					    - 1]) / (float) (32 - aDay));
	    }
	}
    else // cas ou le programme a commence au milieu d'un mois
	{
	theGInput->theInputMailBox.indexOverrunSimulation = aLimitDay
		+ aValueBeginMonth[j];
	}
    theGInput->theInputMailBox.indexOverrunSimulation += 10; //ajoute 10 pour avoir un depassement
    }

//pour verifier le credit restant
void gCompute::computeCredit()
    {
    static UInt16 thePreviousCredit = 10000;

    if (this->theComputeMailBox.aReplySMS[0] == '\0')
	{
	if ((this->theGInput->theInputMailBox.theCredit < 500)
		&& (thePreviousCredit >= 500))
	    {
	    if (this->theTools->theAlarmNumber[0]->aTelNumber[0] == '+')
		{
		sprintf(this->theComputeMailBox.aReplySMS,
			"Remaining credit is low (%d.%d)",
			(this->theGInput->theInputMailBox.theCredit / 100),
			(this->theGInput->theInputMailBox.theCredit % 100));

		strcpy(this->theComputeMailBox.aReplyNb,
			this->theTools->theAlarmNumber[0]->aTelNumber);
		}
	    }
	thePreviousCredit = this->theGInput->theInputMailBox.theCredit;
	}
    }

