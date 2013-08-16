

#include "mCompteur.h"

#define kMultiplexerMeter1 2
#define kMultiplexerMeter2 3
#define kMultiplexerMeterSimulation 1
#define kEnableMeter 4
#define kDisableMeter 0
#define kNumberFigures 5
#define kPositionValue 27

iUART mCompteur::uart(kUSCI_A1, kLSBFirst, k1StBits, kEven, k7bits, k300);
iDIO mCompteur::channelMultiplexer((char*) kPort_6, BIT0 | BIT1);
iDIO mCompteur::enable((char*) kPort_6, BIT2);

//m�thodes publiques
//constructeur
mCompteur::mCompteur(iMeterChannel aChannel)
    {
    //Initialisation des attributs
    if (kMeter1 == aChannel)
	{
	this->channelCodeMultiplexer = kMultiplexerMeter1;
	}
    else if (kMeter2 == aChannel)
	{
	this->channelCodeMultiplexer = kMultiplexerMeter2;
	}
    else if (kMeterSimulation == aChannel)
	{
	this->channelCodeMultiplexer = kMultiplexerMeterSimulation;
	}
    else
	{
	this->channelCodeMultiplexer = 0;
	}

    this->channelMultiplexer.SetPortDirection(kOutput);
    this->enable.SetPortDirection(kOutput);
    }

void mCompteur::mSetup()
    {
    }

void mCompteur::mOpen()
    {
    this->uart.enable();
    this->channelMultiplexer.write(channelCodeMultiplexer);
    }

void mCompteur::mClose()
    {
    this->uart.disable();
    this->channelMultiplexer.write(0);
    }

UInt32 mCompteur::mRead()
    {
    char aResponseMeter[kSciRecBufSize ] = "";
    UInt32 aRet = 0;

    mCompteur::uart.clearInternalSerialBuffer();

    this->enable.write(kDisableMeter);
    this->enable.write(kEnableMeter);


    while (mCompteur::uart.availableCharToRead() <85) // installer un time out
	{
	//if timeout then return 0 et lit quand emem avant la frame
	}

    mCompteur::uart.readFullFrame(aResponseMeter);

    for(int i=0; i<kNumberFigures; i++)
	{
	if(aResponseMeter[kPositionValue] < 48 || aResponseMeter[kPositionValue] > 57)
	    {
	    aRet=0; // cest faux
	    }
	}

    aRet = (aResponseMeter[kPositionValue] - 48) * 10000
	    + (aResponseMeter[kPositionValue+1] - 48) * 1000
	    + (aResponseMeter[kPositionValue+2] - 48) * 100
	    + (aResponseMeter[kPositionValue+3] - 48) * 10
	    + (aResponseMeter[kPositionValue+4] - 48);
    return aRet;
    }



//destructeur
mCompteur::~mCompteur()
    {
    }

