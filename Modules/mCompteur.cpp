//*****************************************************************************
//Nom du fichier : mCompteur.h
//Auteurs et Date : GIGANDET Simon 19.08.2013
//But : couche module permettant l'acces au compteur d'eau GWF
//*****************************************************************************

#include "mCompteur.h"
#include "mDelay.h"

#define kEnableMeter 4 // activation des comtpeurs
#define kDisableMeter 0 // desactivation des comtpeurs
#define kNumberFigures 5 // nombre de chiffres que comporte l'indice du compteur
#define kPositionValue 27 // position ou se situe l'indice du compteur dans la trame
#define kBitTimeUs 33 //duree de 1 bit (a 300 bps) (3300us)
//declaration des attributs objets
iUART mCompteur::uart(kUSCI_A1, kLSBFirst, k1StBits, kEven, k7bits, k300);
iDIO mCompteur::channelMultiplexer((char*) kPort_6, BIT0 | BIT1);
iDIO mCompteur::enable((char*) kPort_6, BIT2);
iDIO mCompteur::cptSim((char*) kPort_6, BIT3);

//----------------------------------------------------------------
//constructeur
//
//aChannel : choix du compteur d'eau
//----------------------------------------------------------------
mCompteur::mCompteur(iMeterChannel aChannel, mEEPROM *mEeprom,
	tCompteur *aTCompteur)
    {
    //selection du compteur d'eau desire

    this->channelCodeMultiplexer = aChannel;

    //Verification de l'EEPROM
    if (mEeprom->getStatus() != 0)
	{
	//EEPROM ERROR
	this->aStatus = 1;
	}
    else
	{
	// A verifier
	this->compteurParam = aTCompteur;

	//Initialisation du parametre tCompteur
	strcpy((char*) this->compteurParam->aData.aDataStruct.aManufacturer, "NA");
	strcpy((char*) this->compteurParam->aData.aDataStruct.aFluide, "NA");
	strcpy((char*) this->compteurParam->aData.aDataStruct.aVersNum, "NA");
	strcpy((char*) this->compteurParam->aData.aDataStruct.aFabDate, "NA");
	strcpy((char*) this->compteurParam->aData.aDataStruct.aSerialNum, "NA");
	strcpy((char*) this->compteurParam->aData.aDataStruct.aNominalSize, "NA");

	this->aStatus = 0;
	}
    }

//----------------------------------------------------------------
//parametrage du module du compteur
//----------------------------------------------------------------
void mCompteur::mSetup()
    {
//parametrage des entrees
    this->channelMultiplexer.SetPortDirection(kOutput);
    this->enable.SetPortDirection(kOutput);
    this->cptSim.SetPortDirection(kOutput);
    }

//----------------------------------------------------------------
//ouverture du module du compteur
//----------------------------------------------------------------
void mCompteur::mOpen()
    {
//activation des entrees
    this->uart.enable();
    this->channelMultiplexer.write(channelCodeMultiplexer);
    //this->enable.write(kHigh);
    }

//----------------------------------------------------------------
//fermeture du module du compteur
//----------------------------------------------------------------
void mCompteur::mClose()
    {
//desactivation des entrees
    this->uart.disable();
    this->channelMultiplexer.write(0);
    this->enable.write(kLow);
    }

//----------------------------------------------------------------
//lecture de l'indice du compteur
//
//retour : la valeur de l'indice du compteur, 0 si la valeur n'a pas pu etre lue
//
//exemple de format de trame : "/GWF Wasser      V4.1\r\n7.0(02514*m3)\r\n0.09(03-11-04)\r\n0.00(0434448)\r\n0.01(DN20)\r\n!\r\n"
//avec 02514 comme indice
//----------------------------------------------------------------
bool mCompteur::mRead(UInt32* aIndex)
    {
    UInt8 aFabFlVers[22] =
	{
	0
	};
    UInt8 aDebitMesure[14] =
	{
	0
	};
    UInt8 aDateFabr[15] =
	{
	0
	};
    UInt8 aSerialNum[15] =
	{
	0
	};
    UInt8 aTailleNom[15] =
	{
	0
	};

    UInt8 aDummy[25] =
	{
	0
	};

    int i = 0, j = 0;
    bool aIsOk = false;
    UInt8 aNumb1; //variables bidons recuperant des valeurs non-importantes de la trame
    UInt8 aNumb2;
    mDelay aDelayTimeout;

    //efface le buffer de reception
    mCompteur::uart.clearInternalSerialBuffer();

    //re-active le compteur, pour qu'il r-envoie la trame
    this->enable.write(kDisableMeter);
    aDelayTimeout.startDelayMS(100);
    //On attend
    while (!aDelayTimeout.isDone())
	;
    this->enable.write(kEnableMeter);

    //Attente d'un certains temps pour recevoir les caractere
    aDelayTimeout.startDelayMS(5000); //Timeout ce 3s
    //On attend
    while ((mCompteur::uart.availableCharToRead() < 85)
	    && !aDelayTimeout.isDone())
	;
    if (!aDelayTimeout.isDone())
	{
	for (i = 0, j = 0; (i < 7) && (j < 6);)
	    {
	    if (mCompteur::uart.readFrameToCRLF((char*) aDummy))
		{
		i++;

		switch (i - 1)
		    {
		case 0:
		    strcpy((char*) aFabFlVers, (char*) aDummy);
		    break;
		case 1:
		    strcpy((char*) aDebitMesure, (char*) aDummy);
		    break;
		case 2:
		    strcpy((char*) aDateFabr, (char*) aDummy);
		    break;
		case 3:
		    strcpy((char*) aSerialNum, (char*) aDummy);
		    break;
		case 4:
		    strcpy((char*) aTailleNom, (char*) aDummy);
		    break;
		case 5:
		    strcpy((char*) aDummy, (char*) aDummy);
		    break;
		default:
		    return 0;
		    }
		}
	    else
		{
		j++;
		}
	    }

	if ((i == j) && (i == 6))
	    {
	    //Recuperation du fabricant, fluide, version
	    sscanf((char*) aFabFlVers, "/%s %s      %s",
		    &(this->compteurParam->aData.aDataStruct.aManufacturer),
		    &(this->compteurParam->aData.aDataStruct.aFluide),
		    &(this->compteurParam->aData.aDataStruct.aVersNum));

	    //Recuperation de la date de fabrication
	    sscanf((char*) aDateFabr, "%d.%d(%s)", &aNumb1, &aNumb2,
		    &(this->compteurParam->aData.aDataStruct.aFabDate));

	    this->compteurParam->aData.aDataStruct.aFabDate[strlen(
		    (char*) this->compteurParam->aData.aDataStruct.aFabDate) - 1] = 0x00;

	    //Recuperation du numero de serie
	    sscanf((char*) aSerialNum, "%d.%d(%s)", &aNumb1, &aNumb2,
		    &(this->compteurParam->aData.aDataStruct.aSerialNum));

	    this->compteurParam->aData.aDataStruct.aSerialNum[strlen(
		    (char*) this->compteurParam->aData.aDataStruct.aSerialNum) - 1] = 0x00;

	    //Recuperation de la taille nominale
	    sscanf((char*) aTailleNom, "%d.%d(%s)", &aNumb1, &aNumb2,
		    &(this->compteurParam->aData.aDataStruct.aNominalSize));

	    this->compteurParam->aData.aDataStruct.aNominalSize[strlen(
		    (char*) this->compteurParam->aData.aDataStruct.aNominalSize) - 1] = 0x00;

	    *aIndex = 0;
	    //retour : la valeur de l'indice du compteur, 0 si la valeur n'a pas pu etre lue
	    if (sscanf((char*) aDebitMesure, "%d.%d(%d*m3)", &aNumb1, &aNumb2,
		    aIndex) == 3)
		{
		aIsOk = true;
		}
	    }
	}
    return aIsOk;
    }

//----------------------------------------------------------------
//envoi d'une trame a la partie simulation de l'interface compteur
//
//aIndex : int : la valeur de l'index qui est envoyee
//
//exemple de format de trame : "/GWF Wasser      V4.1\r\n7.0(02514*m3)\r\n0.09(03-11-04)\r\n0.00(0434448)\r\n0.01(DN20)\r\n!\r\n"
//avec 02514 comme indice
//----------------------------------------------------------------
void mCompteur::simulationCpt(int aIndex)
    {
    char aFrame[90];

    sprintf(aFrame,
	    "/SIM Wasser      V1.0\r\n7.0(%5d*m3)\r\n0.09(22-08-13)\r\n0.00(0000000)\r\n0.01(DN20)\r\n!\r\n",
	    aIndex);

    this->channelMultiplexer.write(channelCodeMultiplexer);
    this->enable.write(kEnableMeter);

    this->sendFrame(aFrame);

    this->enable.write(kDisableMeter);
    }

//----------------------------------------------------------------
//envoi d'une trame a la partie simulation de l'interface compteur
//
//aFrame : char* : la trame a envoyer
//----------------------------------------------------------------
void mCompteur::sendFrame(char* aFrame)
    {
    int i = 0;

    while (aFrame[i] != '\0')
	{
	this->sendChar(aFrame[i]);
	i++;
	}

    return;
    }

//----------------------------------------------------------------
//envoi d'un caractere a la partie simulation de l'interface compteur
//
//aChar : char : le caractere a envoyer
//----------------------------------------------------------------
void mCompteur::sendChar(char aChar)
    {
    int i;

    mDelay aDelay;

    this->cptSim.write(kHigh);	//bit de start

    aDelay.startDelay100US(kBitTimeUs);
    while (!aDelay.isDone())
	{
	}
    //Delay10TCYx (NMEA_TimeBit); //attendre 1 bit

    for (i = 7; i >= 0; i--)
	{
	if ((aChar & 0x01) == 1)
	    {
	    this->cptSim.write(kLow);
	    }
	else
	    {
	    this->cptSim.write(kHigh);
	    }

	aChar = aChar >> 1;

	aDelay.startDelay100US(kBitTimeUs);
	while (!aDelay.isDone())
	    {
	    }
	//Delay10TCYx(NMEA_TimeBit); //attendre 1 bit
	}

    this->cptSim.write(kLow); //stop bit

    aDelay.startDelay100US(kBitTimeUs);
    while (!aDelay.isDone())
	{
	}
    //Delay10TCYx(NMEA_TimeBit); //attendre 1 bit

    return;
    }

//----------------------------------------------------------------
//destructeur
//----------------------------------------------------------------
mCompteur::~mCompteur()
    {
    }

