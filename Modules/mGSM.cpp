//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#include "mGSM.h"

//méthodes publiques
//constructeur
mGSM::mGSM(iDIO* aOutputGSM, iUART* aUartGSM, tCommandesAT* aCommandesATGSM) {
	//Initialisation des attributs
	this->commandesATGSM = aCommandesATGSM;
	this->outputGSM = aOutputGSM;
	this->uartGSM = aUartGSM;
	this->isUnlocked = false;

	this->indexSMS = 0;

	//Configuration des classes associées
	mSetup();
}

/**
 * Fonction de configuration du module GSM
 */
void mGSM::mSetup() {
	// On envoie sur USCI_A0 + LSB first (on peut croiser) + pas de paritée + données de 8 bits + vitesse 115200
	this->uartGSM->config(kLSBFirst, k1StBits, kNone, k8bits, k115200);

	//La sortie reset_Gsm est sir P7.3
	this->outputGSM->SetPortDirection(kOutput);

	//Mode pleine puissance : à voir ...
	this->outputGSM->SetPortDriveStrength(kFullStrength);

	this->indexSMS = 1;
}

/**
 * Fonction permettant l'ouverture du periphérique GSM
 */
void mGSM::mOpen() {

	const char* theCommand;
	char reponseGsm[10];

	//Autorisation de communiquer et enable des interruptions
	this->uartGSM->enable();

	//Au bol : On met à 1 le reset et la sortie MOS
	this->outputGSM->write(1);

	//vitesse
	theCommand = this->commandesATGSM->configBaud19200;
	this->uartGSM->sendString(theCommand);

	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

	while (this->uartGSM->availableCharToRead() <= 5);
	this->uartGSM->readLine(reponseGsm);

	this->uartGSM->disable();
	this->uartGSM->config(kLSBFirst, k1StBits, kNone, k8bits, k9600);
	this->uartGSM->enable();

	this->uartGSM->clearReceptionBuffer();

	//Mode SMS
	theCommand = this->commandesATGSM->enableSMS;

	this->uartGSM->sendString(theCommand);

	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

	//Attente du ok

	while (this->uartGSM->availableCharToRead() <= 5)
		;
	this->uartGSM->readLine(reponseGsm);

	//delocker la carte SIM
	theCommand = this->commandesATGSM->delockPIN;
	this->uartGSM->sendString(theCommand);

	theCommand = "5906";
	this->uartGSM->sendString(theCommand);

	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

	//Attente du ok
	while (this->uartGSM->availableCharToRead() <= 5)
		;
	this->uartGSM->readLine(reponseGsm);

	//Mode SMS
	theCommand = this->commandesATGSM->setModeText;
	this->uartGSM->sendString(theCommand);

	theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(theCommand);

	//Attente du ok
	while (this->uartGSM->availableCharToRead() <= 5)
		;
	this->uartGSM->readLine(reponseGsm);

}

/**
 * Fonction permettant de fermer le periphérique GSM
 */
void mGSM::mClose() {
	//Fin de communication et on lève les interrupts
	this->uartGSM->disable();

	//Au bol : On met à 0 le reset et la sortie MOS
	this->outputGSM->write(0);
}

bool mGSM::getSMS(char* aSMS) {
	char dataReceived[200]; // data reçues du buffer
	int i = 0; // itérateur pour buffer
	int j = 0; // itérateur pour texte uniquement
	bool hasSMS = false;

	// demande au module GSM le prochain SMS
	uartGSM->sendString(commandesATGSM->getSMS);

	uartGSM->write((char) (indexSMS + 48));
	//uartGSM->write(indexSMS + 48); // choisit le message à lire
	uartGSM->sendString(commandesATGSM->endAT);

	for (unsigned int pp = 0; pp < 100; pp++) {
		for (unsigned int qq = 0; qq < 65000; qq++) {
		}
	} // attend la réponse

	uartGSM->readLine(dataReceived); // prend la trame

	// contrôle si un sms est présent dans la trame
	while (0 != dataReceived[i]
			&& !(true == hasSMS && '\r' == dataReceived[i - 2]
					&& '\n' == dataReceived[i - 1])) // s'arrete au debut du texte SMS ; ou à la fin du buffer
	{
// regarder depuis ici en sachant : OK
//		AT+CMGR=3
//		+CMGR: "REC READ","+41787526983","","13/04/18,19:47:26+08"
//		Hello2
//
//		OK
		// voir si '\r' c'est oki?

		// regarde si SMS présent
		if ('O' == dataReceived[i] && 'K' == dataReceived[i + 1]) // pas de SMS
				{
			indexSMS = 1; // tous les SMS sont lus, prochain sms à index 1
			uartGSM->sendString(commandesATGSM->deleteSMSAll); // efface tous SMS
			uartGSM->sendString(commandesATGSM->endAT);
			return false; //sms absent
		} else if ('+' == dataReceived[i] && 'C' == dataReceived[i + 1]
				&& 'M' == dataReceived[i + 2] && 'G' == dataReceived[i + 3]) // sms présent
						{
			hasSMS = true;
		}
		i++;
	}

	// transcrit le texte reçu
	while (!('O' == dataReceived[i + 4] && 'K' == dataReceived[i + 5])) // s'arrete à la fin du message texte
	{
		aSMS[j] = dataReceived[i]; // transcrit (le teste intéressant uniquement)
		i++;
		j++;
	}

	this->indexSMS++; // prochain SMS à être lu
	return true;
}

bool mGSM::sendSMS(char* aSMS, char* aPhoneNumber) {
	UInt16 timeOutIndex = 0;

	char* theAnswer;
	const char* theSMS = this->commandesATGSM->sendSMS;

	this->uartGSM->sendString(theSMS);

	theSMS = aPhoneNumber;

	this->uartGSM->sendString(theSMS);

	theSMS = "\"\r\n";

	this->uartGSM->sendString(theSMS);

	theSMS = aSMS;
	this->uartGSM->sendString(aSMS);

	this->uartGSM->write(0x1A);

}

//destructeur
mGSM::~mGSM() {
}
