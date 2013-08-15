//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#include "mGSM.h"
#include "Def/def.h"

iUART mGSM::uartGSMStat(kUSCI_A0, kLSBFirst, k1StBits, kNone, k8bits, k115200);

void clear_buffer(char* buffer, int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		buffer[i] = 0;
	}
}

//m�thodes publiques
//constructeur
mGSM::mGSM() {
	//Initialisation des attributs
	this->commandesATGSM = new tCommandesAT;
	//Activation GSM
	this->enableGSM = new iDIO((char*) kPort_7, BIT4);
	this->resetGSM = new iDIO((char*) kPort_7, BIT3);

	this->uartGSM = &mGSM::uartGSMStat;

	this->isUnlocked = false;
	this->indexSMS = 1;

	//Configuration des classes associ�es
	mSetup();
}

/**
 * Fonction de configuration du module GSM
 */
void mGSM::mSetup() {
	// On envoie sur USCI_A0 + LSB first (on peut croiser) + pas de parit�e + donn�es de 8 bits + vitesse 115200
	this->uartGSM->config(kLSBFirst, k1StBits, kNone, k8bits, k115200);

	this->enableGSM->SetPortDirection(kOutput);
	this->enableGSM->SetPortDriveStrength(kFullStrength);
	this->resetGSM->SetPortDirection(kOutput);
	this->resetGSM->SetPortDriveStrength(kFullStrength);
}

/**
 * Fonction permettant l'ouverture du periph�rique GSM
 */
void mGSM::mOpen() {

	char reponseGsm[kSciRecBufSize ];

	bool isOk, isError;

	//Autorisation de communiquer et enable des interruptions
	this->uartGSM->enable();

	//Au bol : On met � 1 le reset et la sortie MOS
	this->enableGSM->write(BIT4);
	_delay_us(1000);
	this->resetGSM->write(BIT3);

	_delay_us(1000000);


	//Mode SMS
	//theCommand = this->commandesATGSM->enableSMS;

	// il faudra mieux tester et ne pas faire ce qui vient, par la suite !
	//this->uartGSM->sendString(this->commandesATGSM->questSMSMode);
	//this->uartGSM->sendString(this->commandesATGSM->endAT);




	this->uartGSM->sendString(this->commandesATGSM->enableSMS);

	//theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(this->commandesATGSM->endAT);

	_delay_us(1000000);

	//Test de la réponse
	isOk = false;
	isError = false;
	clear_buffer(reponseGsm, kSciRecBufSize );


	while ( (isOk == false) && (isError == false) )
	{
		this->uartGSM->readFrameSimon(reponseGsm);
		for(int i=0; i<kSciRecBufSize; i++)
		{
			if ( reponseGsm[i] == 'E' && reponseGsm[i+1] == 'R' && reponseGsm[i+2] == 'R' && reponseGsm[i+3] == 'O' && reponseGsm[i+4] == 'R')
			{
				isError = true;
			}
			else if ( reponseGsm[i] == 'O' && reponseGsm[i+1] == 'K')
			{
				isOk = true;
			}
		}
	}


	this->uartGSM->clearReceptionBuffer();
	this->uartGSM->clearInternalSerialBuffer();

	_delay_us(1000000);




	//controle (mal) si la carte sim est deja delock�e
	////this->uartGSM->sendString(this->commandesATGSM->questStatePIN);
	////this->uartGSM->sendString(this->commandesATGSM->endAT);





	//delocker la carte SIM
	//theCommand = this->commandesATGSM->delockPIN;
	this->uartGSM->sendString(this->commandesATGSM->delockPIN);

	//theCommand = "5906";
	this->uartGSM->sendString("5906");

	//theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(this->commandesATGSM->endAT);


	_delay_us(1000000);

	//Test de la réponse
	isOk = false;
	isError = false;
	clear_buffer(reponseGsm, kSciRecBufSize );

	while ( (isOk == false) && (isError == false) )
	{
		this->uartGSM->readFrameSimon(reponseGsm);
		for(int i=0; i<kSciRecBufSize; i++)
		{
			if ( reponseGsm[i] == 'E' && reponseGsm[i+1] == 'R' && reponseGsm[i+2] == 'R' && reponseGsm[i+3] == 'O' && reponseGsm[i+4] == 'R')
			{
				isError = true;
			}
			else if ( reponseGsm[i] == 'O' && reponseGsm[i+1] == 'K')
			{
				isOk = true;
			}
		}
	}


	this->uartGSM->clearReceptionBuffer();
	this->uartGSM->clearInternalSerialBuffer();


	//Mode SMS
	//theCommand = this->commandesATGSM->setModeText;
	this->uartGSM->sendString(this->commandesATGSM->setModeText);

	//theCommand = this->commandesATGSM->endAT;
	this->uartGSM->sendString(this->commandesATGSM->endAT);


	_delay_us(1000000);

	//Test de la réponse
	isOk = false;
	isError = false;
	clear_buffer(reponseGsm, kSciRecBufSize );

	while ( (isOk == false) && (isError == false) )
	{
		this->uartGSM->readFrameSimon(reponseGsm);
		for(int i=0; i<kSciRecBufSize; i++)
		{
			if ( reponseGsm[i] == 'E' && reponseGsm[i+1] == 'R' && reponseGsm[i+2] == 'R' && reponseGsm[i+3] == 'O' && reponseGsm[i+4] == 'R')
			{
				isError = true;
			}
			else if ( reponseGsm[i] == 'O' && reponseGsm[i+1] == 'K')
			{
				isOk = true;
			}
		}
	}

	this->uartGSM->clearReceptionBuffer();
	this->uartGSM->clearInternalSerialBuffer();

}

/**
 * Fonction permettant de fermer le periph�rique GSM
 */
void mGSM::mClose() {
	//Fin de communication et on l�ve les interrupts
	this->uartGSM->disable();

	//Au bol : On met � 0 le reset et la sortie MOS
	this->enableGSM->write(~BIT0);
	this->resetGSM->write(~BIT3);
}

bool mGSM::getSMS(char* aSMS) {
	char dataReceived[kSciRecBufSize]; // data re�ues du buffer
	int i = 13; // it�rateur pour buffer
	int j = 0; // it�rateur pour texte uniquement
	bool hasSMS = false;

	// demande au module GSM le prochain SMS
	uartGSM->sendString(commandesATGSM->getSMS);

	uartGSM->write((char) (indexSMS + 48));
	//uartGSM->write(indexSMS + 48); // choisit le message � lire
	uartGSM->sendString(commandesATGSM->endAT);

	for (unsigned int pp = 0; pp < 100; pp++) {
		for (unsigned int qq = 0; qq < 65000; qq++) {
		}
	} // attend la r�ponse

	this->uartGSM->readFrameSimon(dataReceived);

	// contr�le si un sms est pr�sent dans la trame
	while (0 != dataReceived[i]
			&& !(true == hasSMS && '\r' == dataReceived[i - 2]
					&& '\n' == dataReceived[i - 1])) // s'arrete au debut du texte SMS ; ou � la fin du buffer
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
			//ne pas tout effacer durant les tests
			//ne pas tout effacer durant les tests
			//ne pas tout effacer durant les tests
			//uartGSM->sendString(commandesATGSM->deleteSMSAll); // efface tous SMS
			//uartGSM->sendString(commandesATGSM->endAT);
			return false; //sms absent
		} else if ('+' == dataReceived[i] && 'C' == dataReceived[i + 1]
				&& 'M' == dataReceived[i + 2] && 'G' == dataReceived[i + 3]) // sms pr�sent
						{
			hasSMS = true;
		}
		i++;
	}

	// transcrit le texte re�u
	while (!('O' == dataReceived[i + 4] && 'K' == dataReceived[i + 5])) // s'arrete � la fin du message texte
	{
		aSMS[j] = dataReceived[i]; // transcrit (le teste int�ressant uniquement)
		i++;
		j++;
	}

	this->indexSMS++; // prochain SMS � �tre lu
	return true;
}

bool mGSM::sendSMS(char* aSMS, char* aPhoneNumber) {

	char theAnswer[kSciRecBufSize];
	bool isOk = false;
	bool isError = false;

	_delay_us(1000000);

	this->uartGSM->clearReceptionBuffer();
	this->uartGSM->clearInternalSerialBuffer();
	clear_buffer(theAnswer,kSciRecBufSize);

	//char theSMS[kSciRecBufSize] = this->commandesATGSM->sendSMS;

	this->uartGSM->sendString(this->commandesATGSM->sendSMS);

	_delay_us(1000000);

	//theSMS = aPhoneNumber;

	this->uartGSM->sendString(aPhoneNumber);

	_delay_us(1000000);

	//theSMS = "\"\r\n";

	this->uartGSM->sendString("\"\r\n");

	_delay_us(1000000);

	//theSMS = aSMS;
	this->uartGSM->sendString(aSMS);

	_delay_us(1000000);

	this->uartGSM->write(0x1A);

	//Test de la réponse
	isOk = false;
	isError = false;

	do {
		if (this->uartGSM->readFrame(theAnswer) == true) {
			if (!(strcmp(theAnswer, "+CMS ERROR: 331"))) { //Compare to string #1, and respond
				isError = true;
			}
			if (!(strcmp(theAnswer, "+CMS ERROR: 311"))) { //Compare to string #1, and respond
				isError = true;
			} else if (!(strcmp(theAnswer, "OK"))) { //Compare to string #2, and respond
				isOk = true;
			} else {

			}
		}
	} while ((isOk == false) && (isError == false));

}

//destructeur
mGSM::~mGSM() {
}

//Fonciton utile
void mGSM::_delay_us(long aDelay) {
	long i = 0;
	for (i = 0; i < aDelay; i++) {
		//Pour 1us
		__delay_cycles(25);
	}
}
