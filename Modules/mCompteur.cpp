//*****************************************************************************
//Nom du fichier : mCompteur.h
//Auteurs et Date : GIGANDET Simon 19.08.2013
//But : couche module permettant l'accès au compteur d'eau GWF
//*****************************************************************************


#include "mCompteur.h"

#define kMultiplexerMeter1 2 // choix du compteur à lire
#define kMultiplexerMeter2 3
#define kMultiplexerMeterSimulation 1
#define kEnableMeter 4 // activation des comtpeurs
#define kDisableMeter 0 // desactivation des comtpeurs
#define kNumberFigures 5 // nombre de chiffres que comporte l'indice du compteur
#define kPositionValue 27 // position ou se situe l'indice du compteur dans la trame


//declaration des attributs objets
iUART mCompteur::uart(kUSCI_A1, kLSBFirst, k1StBits, kEven, k7bits, k300);
iDIO mCompteur::channelMultiplexer((char*) kPort_6, BIT0 | BIT1);
iDIO mCompteur::enable((char*) kPort_6, BIT2);


//----------------------------------------------------------------
//constructeur
//
//aChannel : choix du compteur d'eau
//----------------------------------------------------------------
mCompteur::mCompteur(iMeterChannel aChannel)
    {
    //selection du compteur d'eau desire
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
    }


//----------------------------------------------------------------
//parametrage du module du compteur
//----------------------------------------------------------------
void mCompteur::mSetup()
    {
    //parametrage des entrees
    this->channelMultiplexer.SetPortDirection(kOutput);
    this->enable.SetPortDirection(kOutput);
    }


//----------------------------------------------------------------
//ouverture du module du compteur
//----------------------------------------------------------------
void mCompteur::mOpen()
    {
    //activation des entrees
    this->uart.enable();
    this->channelMultiplexer.write(channelCodeMultiplexer);
    }


//----------------------------------------------------------------
//fermeture du module du compteur
//----------------------------------------------------------------
void mCompteur::mClose()
    {
    //desactivation des entrees
    this->uart.disable();
    this->channelMultiplexer.write(0);
    }


//----------------------------------------------------------------
//lecture de l'indice du compteur
//
//retour : la valeur de l'indice du compteur, 0 si la valeur n'a pas pu etre lue
//
//exemple de format de trame : "/GWF Wasser      V4.1\r\n7.0(02514*m3)\r\n0.09(03-11-04)\r\n0.00(0434448)\r\n0.01(DN20)\r\n!\r\n"
//avec 02514 comme indice
//----------------------------------------------------------------
UInt32 mCompteur::mRead()
    {
    char aResponseMeter[kSciRecBufSize ] = "";
    char aDummy[kSciRecBufSize ] = "";
    UInt32 aRet = 0;
    bool aIsOk;
    UInt8 aNumb1; //variables bidons recuperant des valeurs non-importantes de la trame
    UInt8 aNumb2;

    //efface le buffer de reception
    mCompteur::uart.clearInternalSerialBuffer();

    //re-active le compteur, pour qu'il r-envoie la trame
    this->enable.write(kDisableMeter);
    this->enable.write(kEnableMeter);


    //lecture de la première partie de la trame
    while(!mCompteur::uart.readFrame(aDummy));
    while(!mCompteur::uart.readFrame(aDummy));
    while(!mCompteur::uart.readFrame(aResponseMeter));
    while(!mCompteur::uart.readFrame(aDummy));
    while(!mCompteur::uart.readFrame(aDummy));
    while(!mCompteur::uart.readFrame(aDummy));
    while(!mCompteur::uart.readFrame(aDummy));


    //capture de l'indice
    aIsOk=sscanf(aResponseMeter,"%d.%d(%d*m3)", &aNumb1, &aNumb2, &aRet);

    //retour : la valeur de l'indice du compteur, 0 si la valeur n'a pas pu etre lue
    if (aIsOk)
	{
	return aRet;
	}
    else
	{
	return 0;
	}
    }


//----------------------------------------------------------------
//destructeur
//----------------------------------------------------------------wes
mCompteur::~mCompteur()
    {
    }

