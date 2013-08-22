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
mCompteur::mCompteur(iMeterChannel aChannel, mEEPROM *mEeprom) {
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

	//Vérification de l'EEPROM
	if (mEeprom->getStatus() != 0) {
		//EEPROM ERROR
		this->aStatus = 1;
	} else {
		// A vérifier
		this->compteurParam = new tCompteur(mEeprom, aChannel);

		//Initialisation du paramètre tCompteur
		strcpy((char*) this->compteurParam->aManufacturer, "NA");
		strcpy((char*) this->compteurParam->aFluide, "NA");
		strcpy((char*) this->compteurParam->aVersNum, "NA");
		strcpy((char*) this->compteurParam->aFabDate, "NA");
		strcpy((char*) this->compteurParam->aSerialNum, "NA");
		strcpy((char*) this->compteurParam->aNominalSize, "NA");

		this->aStatus = 0;
	}
}

//----------------------------------------------------------------
//parametrage du module du compteur
//----------------------------------------------------------------
void mCompteur::mSetup() {
//parametrage des entrees
	this->channelMultiplexer.SetPortDirection(kOutput);
	this->enable.SetPortDirection(kOutput);
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
//retour : la valeur de l'indice du compteur, 0 si la valeur n'a pas pu etre lue
//
//exemple de format de trame : "/GWF Wasser      V4.1\r\n7.0(02514*m3)\r\n0.09(03-11-04)\r\n0.00(0434448)\r\n0.01(DN20)\r\n!\r\n"
//avec 02514 comme indice
//----------------------------------------------------------------
UInt32 mCompteur::mRead() {
	UInt8 aFabFlVers[22] = { 0 };
	UInt8 aDebitMesure[14] = { 0 };
	UInt8 aDateFabr[15] = { 0 };
	UInt8 aSerialNum[15] = { 0 };
	UInt8 aTailleNom[15] = { 0 };

	UInt8 aDummy[5] = { 0 };

	UInt32 aRet = 0;
	bool aIsOk;
	UInt8 aNumb1; //variables bidons recuperant des valeurs non-importantes de la trame
	UInt8 aNumb2;

	//efface le buffer de reception
	mCompteur::uart.clearInternalSerialBuffer();

	//re-active le compteur, pour qu'il r-envoie la trame
	this->enable.write(kDisableMeter);
	this->enable.write(kEnableMeter);

	//lecture de la premi�re partie de la trame

	//FIXME Quand le fonction  "readFrame" sera modifiée, il faut enlever la lecture des Dummy et attendre d'abord les 85 caractères

	//Recupération des données fabricant fluide et version
	while (!mCompteur::uart.readFrame(aFabFlVers))
		;
	while (!mCompteur::uart.readFrame(aDummy))
		;

	//Recuperation de la valeur du compteur
	while (!mCompteur::uart.readFrame(aDebitMesure))
		;
	while (!mCompteur::uart.readFrame(aDummy))
		;

	//Recupération de la date de fabrication
	while (!mCompteur::uart.readFrame(aDateFabr))
		;
	while (!mCompteur::uart.readFrame(aDummy))
		;

	//Récuperation du numéro de série
	while (!mCompteur::uart.readFrame(aSerialNum))
		;
	while (!mCompteur::uart.readFrame(aDummy))
		;

	//Récuperation de la taille normalisée
	while (!mCompteur::uart.readFrame(aTailleNom))
		;
	while (!mCompteur::uart.readFrame(aDummy))
		;

	//Fin de trame
	while (!mCompteur::uart.readFrame(aDummy))
		;
	while (!mCompteur::uart.readFrame(aDummy))
		;

	//Récuperation du fabricant, fluide, version
	sscanf((char*) aFabFlVers, "/%s %s      %s",
			&(this->compteurParam->aManufacturer),
			&(this->compteurParam->aFluide), &(this->compteurParam->aVersNum));

	//Récuperation de la date de fabrication
	sscanf((char*) aDateFabr, "%d.%d(%s)", &aNumb1, &aNumb2,
			&(this->compteurParam->aFabDate));

	this->compteurParam->aFabDate[strlen((char*) this->compteurParam->aFabDate)
			- 1] = 0x00;

	//Récuperation du numéro de série
	sscanf((char*) aSerialNum, "%d.%d(%s)", &aNumb1, &aNumb2,
			&(this->compteurParam->aSerialNum));

	this->compteurParam->aSerialNum[strlen(
			(char*) this->compteurParam->aSerialNum) - 1] = 0x00;

	//Récuperation de la taille nominale
	sscanf((char*) aTailleNom, "%d.%d(%s)", &aNumb1, &aNumb2,
			&(this->compteurParam->aNominalSize));

	this->compteurParam->aNominalSize[strlen(
			(char*) this->compteurParam->aNominalSize) - 1] = 0x00;

	//Récupération de l'indice
	aIsOk = sscanf((char*) aDebitMesure, "%d.%d(%d*m3)", &aNumb1, &aNumb2,
			&aRet);

//retour : la valeur de l'indice du compteur, 0 si la valeur n'a pas pu etre lue
	if (aIsOk) {
		return aRet;
	} else {
		return 0;
	}
}

//----------------------------------------------------------------
//destructeur
//----------------------------------------------------------------wes
mCompteur::~mCompteur() {
}

