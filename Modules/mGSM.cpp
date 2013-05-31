//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#include "mGSM.h"

//m�thodes publiques
//constructeur
mGSM::mGSM(iDIO* aOutputGSM, iUART* aUartGSM, tCommandesAT* aCommandesATGSM) {
	//Initialisation des attributs
	this->commandesATGSM = aCommandesATGSM;
	this->outputGSM = aOutputGSM;
	this->uartGSM = aUartGSM;
	this->isUnlocked = false;

	this->indexSMS = 0;

	//Configuration des classes associ�es
	mSetup();
}

/**
 * Fonction de configuration du module GSM
 */
void mGSM::mSetup() {
	// On envoie sur USCI_A0 + LSB first (on peut croiser) + pas de parit�e + donn�es de 8 bits + vitesse 115200
	this->uartGSM->config(kLSBFirst, k2StBits, kNone, k8bits, 115200);

	//La sortie reset_Gsm est sir P7.3
	this->outputGSM->SetPortDirection(kOutput);

	//Mode pleine puissance : � voir ...
	this->outputGSM->SetPortDriveStrength(kFullStrength);

}

/**
 * Fonction permettant l'ouverture du periph�rique GSM
 */
void mGSM::mOpen() {

	std::string theCommand;

	//Autorisation de communiquer et enable des interruptions
	this->uartGSM->enable();

	//Au bol : On met � 1 le reset et la sortie MOS
	this->outputGSM->write(1);

	//Mode SMS
	theCommand = this->commandesATGSM->enableSMS;

	this->uartGSM->sendString(theCommand);

	theCommand = this->commandesATGSM->endAT;

	this->uartGSM->sendString(theCommand);

	//delocker la carte SIM
	theCommand = this->commandesATGSM->delockPIN;
	this->uartGSM->sendString(theCommand);
	theCommand = "5906";
	this->uartGSM->sendString(theCommand);
	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

	//Mode SMS
	theCommand = this->commandesATGSM->setModeText;
	this->uartGSM->sendString(theCommand);
	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

//	//addp1
//	theCommand = this->commandesATGSM->addP41ToWhiteList;
//	this->uartGSM->sendString(theCommand);
//	theCommand = this->commandesATGSM->endAT;
//	this->uartGSM->sendString(theCommand);

	//Quest

	theCommand = this->commandesATGSM->questWhiteList;
	this->uartGSM->sendString(theCommand);
	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

	theCommand = this->commandesATGSM->questSMSMode;
	this->uartGSM->sendString(theCommand);
	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

	theCommand = this->commandesATGSM->questStatePIN;
	this->uartGSM->sendString(theCommand);
	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);
}

/**
 * Fonction permettant de fermer le periph�rique GSM
 */
void mGSM::mClose() {
	//Fin de communication et on l�ve les interrupts
	this->uartGSM->disable();

	//Au bol : On met � 0 le reset et la sortie MOS
	this->outputGSM->write(0);
}

bool mGSM::getSMS(char* aSMS) {
	char dataReceived[200]; // data re�ues du buffer
	int i = 0; // it�rateur pour buffer
	int j = 0; // it�rateur pour texte uniquement
	bool hasSMS = false;

	// demande au module GSM le prochain SMS
	uartGSM->sendString(commandesATGSM->getSMS);

	//uartGSM->write((char) (indexSMS + 48));
	uartGSM->write(indexSMS + 48); // choisit le message � lire
	uartGSM->sendString(commandesATGSM->endAT);

	for(int pp=0 ; pp<400 ; pp++){for(int qq=0 ; qq<65000 ; qq++){}}// attend la r�ponse



	uartGSM->readFullBuffer(dataReceived, uartGSM->availableCharToRead()); // prend la trame

	// contr�le si un sms est pr�sent dans la trame
	while (0 != dataReceived[i] && !(true == hasSMS && '\r' == dataReceived[i - 2] && '\n' == dataReceived[i - 1])) // s'arrete au debut du texte SMS ; ou � la fin du buffer
	{
// regarder depuis ici en sachant : OK
//		AT+CMGR=3
//		+CMGR: "REC READ","+41787526983","","13/04/18,19:47:26+08"
//		Hello2
//
//		OK
		// voir si '\r' c'est oki?

		// regarde si SMS pr�sent
		if ('O' == dataReceived[i] && 'K' == dataReceived[i + 1]) // pas de SMS
			{
			indexSMS = 1; // tous les SMS sont lus, prochain sms � index 1
			uartGSM->sendString(commandesATGSM->deleteSMSAll); // efface tous SMS
			uartGSM->sendString(commandesATGSM->endAT);
			return false; //sms absent
			}
		else if ('+' == dataReceived[i] && 'C' == dataReceived[i + 1] && 'M' == dataReceived[i + 2] && 'G' == dataReceived[i + 3]) // sms pr�sent
			{
			hasSMS = true;
			}
		i++;
	}

	// transcrit le texte re�u
	while (!('O' == dataReceived[i + 4] && 'K' == dataReceived[i + 5]))// s'arrete � la fin du message texte
	{
		aSMS[j] = dataReceived[i]; // transcrit (le teste int�ressant uniquement)
		i++;
		j++;
	}

	this->indexSMS++; // prochain SMS � �tre lu
	return true;
}

bool mGSM::sendSMS(char* aSMS, std::string aPhoneNumber) {
	UInt16 timeOutIndex = 0;

	std::string theAnswer("");
	std::string theSMS = this->commandesATGSM->sendSMS;

	this->uartGSM->sendString(theSMS);

	theSMS = aPhoneNumber;

	this->uartGSM->sendString(theSMS);

	theSMS = "\"\r\n";

	this->uartGSM->sendString(theSMS);

	while (65535 != timeOutIndex) {
		timeOutIndex++;
	}

	this->uartGSM->readFullBuffer(theAnswer);

	//theSMS = aSMS;
	this->uartGSM->sendString(aSMS);

	this->uartGSM->write(0x1A);

	if (std::string::npos == theAnswer.find("+CMGS:")) {
		return false;
	} else {
		return true;
	}
}

//destructeur
mGSM::~mGSM() {
}
