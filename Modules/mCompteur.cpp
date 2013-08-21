//*****************************************************************************
//Nom du fichier : mCompteur.h
//Auteurs et Date : GIGANDET Simon 19.08.2013
//But : couche module permettant l'acc�s au compteur d'eau GWF
//*****************************************************************************

#include "mCompteur.h"

#define kMultiplexerMeter1 2 // choix du compteur � lire
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
mCompteur::mCompteur(iMeterChannel aChannel) {
	//selection du compteur d'eau desire
	if (kMeter1 == aChannel) {
		this->channelCodeMultiplexer = kMultiplexerMeter1;
	} else if (kMeter2 == aChannel) {
		this->channelCodeMultiplexer = kMultiplexerMeter2;
	} else if (kMeterSimulation == aChannel) {
		this->channelCodeMultiplexer = kMultiplexerMeterSimulation;
	} else {
		this->channelCodeMultiplexer = 0;
	}

	//parametrage des entrees
	this->channelMultiplexer.SetPortDirection(kOutput);
	this->enable.SetPortDirection(kOutput);

	//Initialisation du paramètre tCompteur
	this->compteurParam.aManufacturer = "NA";
	this->compteurParam.aFluide = "NA";
	this->compteurParam.aVersNum = "NA";
	this->compteurParam.aFabDate = "NA";
	this->compteurParam.aSerialNum = "NA";
	this->compteurParam.aNominalSize = "NA";

}

//----------------------------------------------------------------
//parametrage du module du compteur
//----------------------------------------------------------------
void mCompteur::mSetup() {
}

//----------------------------------------------------------------
//ouverture du module du compteur
//----------------------------------------------------------------
void mCompteur::mOpen() {
	//activation des entrees
	this->uart.enable();
	this->channelMultiplexer.write(channelCodeMultiplexer);
}

//----------------------------------------------------------------
//fermeture du module du compteur
//----------------------------------------------------------------
void mCompteur::mClose() {
	//desactivation des entrees
	this->uart.disable();
	this->channelMultiplexer.write(0);
}

//----------------------------------------------------------------
//lecture de l'indice du compteur
//
//retour : la valeur de l'indice du compteur
//----------------------------------------------------------------
UInt32 mCompteur::mRead() {
	char aResponseMeter[kSciRecBufSize ] = "";
	UInt32 aRet = 0;

	//efface le buffer de reception
	mCompteur::uart.clearInternalSerialBuffer();

	//re-active le compteur, pour qu'il r-envoie la trame
	this->enable.write(kDisableMeter);
	this->enable.write(kEnableMeter);

	//attend la fin de la trame
	while (mCompteur::uart.availableCharToRead() < 85) // installer un time out
	{
		//if timeout then return 0 et lit quand emem avant la frame
	}

	//lecture de la trame
	mCompteur::uart.readFullFrame(aResponseMeter);

	//controle que l'indice du compteur comporte uniquement des chiffres
	for (int i = 0; i < kNumberFigures; i++) {
		if (aResponseMeter[kPositionValue] < 48
				|| aResponseMeter[kPositionValue] > 57) {
			aRet = 0; // cest faux
		}
	}

	//converti l'indice (de tableau de char en long)
	aRet = (aResponseMeter[kPositionValue] - 48) * 10000
			+ (aResponseMeter[kPositionValue + 1] - 48) * 1000
			+ (aResponseMeter[kPositionValue + 2] - 48) * 100
			+ (aResponseMeter[kPositionValue + 3] - 48) * 10
			+ (aResponseMeter[kPositionValue + 4] - 48);
	return aRet;
}

//----------------------------------------------------------------
//destructeur
//----------------------------------------------------------------wes
mCompteur::~mCompteur() {
}

