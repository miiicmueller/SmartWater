//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteur et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#include "mGSM.h"

//m�thodes publiques
//constructeur
mGSM::mGSM(iDIO* aOutputGSM, iUART* aUartGSM, tCommandesAT* aCommandesATGSM)
    {
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
void mGSM::mSetup()
    {
    // On envoie sur USCI_A0 + LSB first (on peut croiser) + pas de parit�e + donn�es de 8 bits + vitesse 115200
    this->uartGSM->config(kLSBFirst, k1StBits, kNone, k8bits, 115200);

    //La sortie reset_Gsm est sir P7.3
    this->outputGSM->SetPortDirection(kOutput);

    //Mode pleine puissance : � voir ...
    this->outputGSM->SetPortDriveStrength(kFullStrength);


    }


/**
 * Fonction permettant l'ouverture du periph�rique GSM
 */
void mGSM::mOpen()
    {
    //Autorisation de communiquer et enable des interruptions
    this->uartGSM->enable();

    //Au bol : On met � 1 le reset et la sortie MOS
    this->outputGSM->write(1);
    }

/**
 * Fonction permettant de fermer le periph�rique GSM
 */
void mGSM::mClose()
    {
    //Fin de communication et on l�ve les interrupts
    this->uartGSM->disable();

    //Au bol : On met � 0 le reset et la sortie MOS
    this->outputGSM->write(0);
    }

bool mGSM::getSMS(char* aSMS)
    {
	char dataReceived[200]; // data re�ues du buffer
	int i=0; // it�rateur pour buffer
	int j=0; // it�rateur pour texte uniquement
	bool hasSMS = false;

	// demande au module GSM le prochain SMS
	uartGSM->sendString(commandesATGSM->getSMS);
	uartGSM->sendString(indexSMS+48);
	uartGSM->sendString(commandesATGSM->endAT);

	WAIT(5000); // attend la r�ponse

	uartGSM->readFullBuffer(dataReceived); // prend la trame

	// contr�le si un sms est pr�sent dans la trame
	while(0!=dataReceived[i] && !( true==hasSMS && "\r" == dataReceived[i-2] && "\n"== dataReceived[i-1])) // s'arrete au debut du texte SMS ou � la fin du buffer
		{
		if ('O' == dataReceived[i] && 'K' == dataReceived[i+1]) // pas de SMS
			{
			indexSMS = 1; // tous les SMS sont lus, prochain sms � index 1
			uartGSM->sendString(commandesATGSM->deleteSMSAll); // efface tous SMS
			uartGSM->sendString(commandesATGSM->endAT);
			return false; //sms absent
			}
		else if ('+'==dataReceived[i] && 'C'==dataReceived[i+1] && 'M'==dataReceived[i+2] && 'G'==dataReceived[i+3]) // sms pr�sent
			{
			hasSMS = true;
			}
		i++;
		}

	// transcrit le texte re�u
	while(!('O' == dataReceived[i+5] && 'K' == dataReceived[i+6])) // s'arrete � la fin du message texte
		{
		aSMS[j]=dataReceived[i];
		i++;
		j++;
		}

	indexSMS++; // prochain SMS � �tre lu
	return true;
    }

void mGSM::sendSMS(std::string aSMS, std::string aPhoneNumber)
    {
    char aReceivedChar;
    std::string theAnswer();
    std::string theSMS(
	    this->commandesATGSM->aCommand + "=\"+" + aPhoneNumber + "\"\r"
		    + aSMS + "\r\n");

    this->uartGSM->sendString(theSMS);

    while (false == this->uartGSM->isBufferEmpty())
	{
	aReceivedChar = this->uartGSM->read();

	}

    }

//destructeur
mGSM::~mGSM()
    {
    }
