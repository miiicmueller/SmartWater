//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteur et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#include "mGSM.h"

//méthodes publiques
//constructeur
mGSM::mGSM(iDIO* aOutputGSM, iUART* aUartGSM, tCommandesAT* aCommandesATGSM)
    {
    this->commandesATGSM = aCommandesATGSM;
    this->outputGSM = aOutputGSM;
    this->uartGSM = aUartGSM;

    this->isUnlocked = false;

    }


bool mGSM::getSMS(char* aSMS)
    {
	char dataReceived[200]; // data reçues du buffer
	int i=0; // itérateur pour buffer
	int j=0; // itérateur pour texte uniquement
	bool hasSMS = false;

	// demande au module GSM le prochain SMS
	uartGSM->sendString(commandesATGSM->getSMS);
	uartGSM->sendString(indexSMS+48);
	uartGSM->sendString(commandesATGSM->endAT);

	WAIT(5000); // attend la réponse

	uartGSM->readFullBuffer(dataReceived); // prend la trame

	// contrôle si un sms est présent dans la trame
	while(0!=dataReceived[i] && !( true==hasSMS && "\r" == dataReceived[i-2] && "\n"== dataReceived[i-1])) // s'arrete au debut du texte SMS ou à la fin du buffer
		{
		if ('O' == dataReceived[i] && 'K' == dataReceived[i+1]) // pas de SMS
			{
			indexSMS = 1; // tous les SMS sont lus, prochain sms à index 1
			uartGSM->sendString(commandesATGSM->deleteSMSAll); // efface tous SMS
			uartGSM->sendString(commandesATGSM->endAT);
			return false; //sms absent
			}
		else if ('+'==dataReceived[i] && 'C'==dataReceived[i+1] && 'M'==dataReceived[i+2] && 'G'==dataReceived[i+3]) // sms présent
			{
			hasSMS = true;
			}
		i++;
		}

	// transcrit le texte reçu
	while(!('O' == dataReceived[i+5] && 'K' == dataReceived[i+6])) // s'arrete à la fin du message texte
		{
		aSMS[j]=dataReceived[i];
		i++;
		j++;
		}

	indexSMS++; // prochain SMS à être lu
	return true;
    }

void mGSM::sendSMS(std::string data)
    {
    }

//destructeur
mGSM::~mGSM()
    {
    }




OK
AT+CMGR=2
+CMGR: "REC READ","+41787526983","","13/04/18,19:44:55+08"
Hello2

OK
AT+CMGR=3
+CMGR: "REC READ","+41787526983","","13/04/18,19:47:26+08"
Hello2

OK
AT+CMGR=4
+CMGR: "REC READ","+41787526983","","13/04/18,19:51:09+08"
aaaaaaaaaaaaaaaaaaaaaaa

OK
AT+CMGR=5
+CMGR: "REC READ","+41787526983","","13/04/18,19:51:22+08"
bbbbbbbbbbbbbbbbbbbbb

OK
AT+CMGR=6
OK
AT+CMGL=1
