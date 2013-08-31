/*
 * tCommandsAnalyzer.cpp
 *
 *  Created on: 30 août 2013
 *      Author: cyrille.savy
 */

#include "tCommandsAnalyzer.h"
#include <stdio.h>
#include <string.h>

using namespace std;

tCommandsAnalyzer::tCommandsAnalyzer()
    {
    this->maxSizesCommands[0] = sizeMaxMode;
    this->maxSizesCommands[1] = sizeMaxMdp;
    this->maxSizesCommands[2] = sizeMaxCommand;
    this->maxSizesCommands[3] = sizeMaxParameter;
    }

void tCommandsAnalyzer::tCommandsAnalysis(char* aMessage,
	tToolsCluster* theTools)
    {
    this->aStateEnum = kEmpty;
    this->aCommandResult.aCommandEnum = kCommandNoCommand;
    this->tCommandsParser(aMessage);

    if (this->aStateEnum == kPending)
	{

	//verification du mode
	if (strcmp(this->aCommandBrut.theMode, "A") == 0)
	    {
	    this->aCommandResult.aModeTypeEnum = kAdmin;
	    }
	else if (strcmp(this->aCommandBrut.theMode, "A1") == 0)
	    {
	    this->aCommandResult.aModeTypeEnum = kAdmin1;
	    }
	else if (strcmp(this->aCommandBrut.theMode, "A2") == 0)
	    {
	    this->aCommandResult.aModeTypeEnum = kAdmin2;
	    }
	else if (strcmp(this->aCommandBrut.theMode, "U1") == 0)
	    {
	    this->aCommandResult.aModeTypeEnum = kUser1;
	    }
	else if (strcmp(this->aCommandBrut.theMode, "U2") == 0)
	    {
	    this->aCommandResult.aModeTypeEnum = kUser2;
	    }
	else
	    {
	    this->aCommandResult.aCommandEnum = kCommandError;
	    }

	//verification du mot de passe
	if (this->aCommandResult.aCommandEnum == kCommandNoCommand)
	    {
	    switch (this->aCommandResult.aModeTypeEnum)
		{
	    case kAdmin:
	    case kAdmin1:
	    case kAdmin2:
		if (strcmp(this->aCommandBrut.theMdp,
			theTools->theMdPAdmin->mdPAdmin) != 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandError;
		    }
		break;
	    case kUser1:
		if (strcmp(this->aCommandBrut.theMdp,
			theTools->theMdPUser[0]->mdPUser) != 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandError;
		    }
		break;
	    case kUser2:
		if (strcmp(this->aCommandBrut.theMdp,
			theTools->theMdPUser[1]->mdPUser) != 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandError;
		    }
		break;
	    default:
		break;
		}
	    }

	//recuperation de la commande
	//commandes utilisateur et USB
	if (this->aCommandResult.aCommandEnum == kCommandNoCommand)
	    {
	    if (strcmp(this->aCommandBrut.theCommand, "disconnect") == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandDisconnect;
		}
	    else if (strcmp(this->aCommandBrut.theCommand, "connect") == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandConnect;
		}
	    else if (strcmp(this->aCommandBrut.theCommand, "alarm") == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandAlarm;
		}
	    else if (strcmp(this->aCommandBrut.theCommand, "limits") == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandLimits;
		}
	    else if (strcmp(this->aCommandBrut.theCommand, "etat") == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandEtat;
		}
	    else if (strcmp(this->aCommandBrut.theCommand, "passu") == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandPassu;
		}
	    else if (strcmp(this->aCommandBrut.theCommand, "monthlyconsumption")
		    == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandMonthlyconsumption;
		}
	    else if (strcmp(this->aCommandBrut.theCommand, "dailyconsumption")
		    == 0)
		{
		this->aCommandResult.aCommandEnum = kCommandDailyconsumption;
		}
	    //commandes administrateur
	    else if ((this->aCommandResult.aModeTypeEnum == kAdmin)
		    || (this->aCommandResult.aModeTypeEnum == kAdmin1)
		    || (this->aCommandResult.aModeTypeEnum == kAdmin2))
		{
		if (strcmp(this->aCommandBrut.theCommand, "mah") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandMah;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "dispo") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandDispo;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "mode") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandMode;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "offset") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandOffset;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "passa") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandPassa;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "simulate") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandSimulate;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "reset") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandReset;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "dysfunction")
			== 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandDysfunction;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "unitname") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandUnitName;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "pin") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandPin;
		    }
		else if (strcmp(this->aCommandBrut.theCommand, "own") == 0)
		    {
		    this->aCommandResult.aCommandEnum = kCommandOwn;
		    }
		else
		    {
		    this->aCommandResult.aCommandEnum = kCommandError;
		    }
		}
	    else
		{
		this->aCommandResult.aCommandEnum = kCommandError;
		}
	    }

	}
    if (this->aCommandResult.aCommandEnum != kCommandNoCommand)
	{
	this->aStateEnum = kComplete;
	}
    }

//separe les champs du message recu
int tCommandsAnalyzer::tCommandsParser(char* aMessage)
    {
    int i = 0;
    int pos = 0;
    int posPara = 0;
    int previous_ = 0;
    int next_ = 0;
    int theParametersNumber = 0;

    if (aMessage[i] == '_')
	{
	//verification de la commande (pour securiser le sscanf)
	do
	    {
	    if (aMessage[i] == '_')
		{
		previous_ = next_;
		next_ = i;

		aMessage[i] = ' ';

		posPara++;

		if ((pos < 3) && (previous_ > 0))
		    {
		    pos++;
		    }
		}
	    i++;
	    }
	while ((i <= 100) && (aMessage[i] != '\0')
		&& ((next_ - previous_) <= (maxSizesCommands[pos]))
		&& (posPara <= 15));
	if (aMessage[i] == '\0')
	    {
	    theParametersNumber = sscanf(aMessage,
		    " %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s ",
		    this->aCommandBrut.theMode, this->aCommandBrut.theMdp,
		    this->aCommandBrut.theCommand,
		    this->aCommandBrut.theParameters[0],
		    this->aCommandBrut.theParameters[1],
		    this->aCommandBrut.theParameters[2],
		    this->aCommandBrut.theParameters[3],
		    this->aCommandBrut.theParameters[4],
		    this->aCommandBrut.theParameters[5],
		    this->aCommandBrut.theParameters[6],
		    this->aCommandBrut.theParameters[7],
		    this->aCommandBrut.theParameters[8],
		    this->aCommandBrut.theParameters[9],
		    this->aCommandBrut.theParameters[10],
		    this->aCommandBrut.theParameters[11]);

	    if (theParametersNumber >= 3)
		{
		this->aStateEnum = kPending;
		theParametersNumber -= 3;
		}
	    }
	}
    return theParametersNumber;
    }

tCommandsAnalyzer::~tCommandsAnalyzer()
    {
    }
