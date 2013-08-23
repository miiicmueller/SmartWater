#include <string>
#include <assert.h>

#include "gTerminal.h"
#include <stdio.h>

typedef enum
    {
    kTerminalDisconnected,
    kTerminalConnected,
    kTerminalSessionOpen
    } gTerminalStateEnum;

//OBLIGATOIRE POUR L'USB
volatile BYTE bCDCDataReceived_event = FALSE; //Indicates data has been received without an open rcv operation

//----------------------------------------------------------------
//constructeur
//
//gInput : le gestionnaire qui contient les entrees
//----------------------------------------------------------------
gTerminal::gTerminal(gInput* theGInput)
    {
    this->theUSB = new mUSB(&bCDCDataReceived_event);
    this->theGInput = theGInput;
    this->sessionOpen = false;
    this->aCommand.hasCommand = false;

    this->maxSizesCommands[0] = sizeMaxMode;
    this->maxSizesCommands[1] = sizeMaxMdp;
    this->maxSizesCommands[2] = sizeMaxCommand;
    this->maxSizesCommands[3] = sizeMaxParameter;
    }

//----------------------------------------------------------------
//setup()
//
//configuration du terminal
//----------------------------------------------------------------
void gTerminal::setup()
    {
    }

//----------------------------------------------------------------
//execute()
//
//execution de la communication avec l'USB (machine d'etat, non-blocant)
//----------------------------------------------------------------
void gTerminal::execute()
    {

    }

//----------------------------------------------------------------
//commandsReceiver()
//
//traite les messages recus et s'ils sont valides, les range dans
//la structure aCommand
//----------------------------------------------------------------
void gTerminal::commandsReceiver()
    {
    char aMessage[100];
    int i = 0;
    int pos = 0;
    int previous_ = 0;
    int next_ = 0;

    this->aCommand.hasCommand = false;

    if (true == this->theUSB->getCommand(aMessage))
	{
	if (aMessage[0] == '_')
	    {
	    //verification de la commande (pour securiser le sscanf)
	    while ((i <= 100) && (aMessage[i] != '\0')
		    && ((next_ - previous_) <= maxSizesCommands[pos]))
		{
		i++;
		if (aMessage[i] == '_')
		    {
		    previous_ = next_;
		    next_ = i;

		    if (pos < 3)
			{
			pos++;
			}
		    }
		}
	    if (aMessage[i] == '\0')
		{
		this->aCommand.parametersNumber = sscanf(aMessage,
			"_%s_%s_%s_%s_%s_%s_%s_%s_%s_%s_%s_%s_%s_%s_%s_",
			this->aCommand.theMode, this->aCommand.theMdp,
			this->aCommand.theCommand,
			this->aCommand.theParameters[0],
			this->aCommand.theParameters[1],
			this->aCommand.theParameters[2],
			this->aCommand.theParameters[3],
			this->aCommand.theParameters[4],
			this->aCommand.theParameters[5],
			this->aCommand.theParameters[6],
			this->aCommand.theParameters[7],
			this->aCommand.theParameters[8],
			this->aCommand.theParameters[9],
			this->aCommand.theParameters[10],
			this->aCommand.theParameters[11]);

		if (this->aCommand.parametersNumber >= 2)
		    {
		    this->aCommand.hasCommand = true;
		    this->aCommand.parametersNumber -= 2;
		    }
		}
	    }
	}
    }

//----------------------------------------------------------------
//commandsSender()
//
//envoie une chaine de caracteres sur l'usb
//----------------------------------------------------------------
void gTerminal::commandsSender(char* aReply)
    {
    }
