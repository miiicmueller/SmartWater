//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#define kTimeOutResponse 4000
#define kTimeOutSendSms 65000

#include "mGSM.h"
#include "Def/def.h"

//declaration des attributs objets
iUART mGSM::uart(kUSCI_A0, kLSBFirst, k1StBits, kNone, k8bits, k115200);
iDIO mGSM::enable((char*) kPort_7, BIT4);
iDIO mGSM::reset((char*) kPort_7, BIT3);
tCommandesAT mGSM::commandesAtGsm;
mDelay mGSM::timeOut;


//----------------------------------------------------------------
//constructeur
//----------------------------------------------------------------
mGSM::mGSM()
    {
    //Initialisation des attributs
    this->indexSMS = 1;
    this->state = kDisconnected; // etat initial
    }

//----------------------------------------------------------------
// Fonction de configuration du module GSM
//----------------------------------------------------------------
void mGSM::mSetup()
    {
    // On envoie sur USCI_A0 + LSB first (on peut croiser) + pas de paritee + donneees de 8 bits + vitesse 115200
    mGSM::uart.config(kLSBFirst, k1StBits, kNone, k8bits, k115200);

    //parametrage des entrees
    mGSM::enable.SetPortDirection(kOutput);
    mGSM::enable.SetPortDriveStrength(kFullStrength);
    mGSM::reset.SetPortDirection(kOutput);
    mGSM::reset.SetPortDriveStrength(kFullStrength);
    }

//----------------------------------------------------------------
// Fonction permettant l'ouverture du peripherique GSM
//----------------------------------------------------------------
void mGSM::mOpen()
    {
    bool aIsOk = false;
    this->state = kOk;

    //autorisation de communiquer et enable des interruptions
    mGSM::uart.enable();
    mGSM::enable.write(BIT4);
    mGSM::reset.write(BIT3);

    mGSM::uart.clearInternalSerialBuffer(); //efface le buffer

    //enable mode sms
    mGSM::uart.sendString(mGSM::commandesAtGsm.enableSMS);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
    aIsOk=mCheckResponse("OK",kTimeOutResponse); //test la reponse

    //maj etat module
    if (!aIsOk)
	{
	this->state = kErrorSetModeSms;
	}

    //controle si la carte SIM est deja delockee
    mGSM::uart.sendString(mGSM::commandesAtGsm.questStatePIN);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
    aIsOk=mCheckResponse("+CPIN: READY",kTimeOutResponse); //test la reponse

    //deverouille la carte SIM, si besoin est
    if (!aIsOk)
	{
	mGSM::uart.sendString(mGSM::commandesAtGsm.delockPIN);
	mGSM::uart.sendString(this->codePIN);
	mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
	aIsOk=mCheckResponse("OK",kTimeOutResponse); //test la reponse

	//maj etat module
	if (!aIsOk)
	    {
	    this->state = kErrorEnterPin;
	    }
	}

    // passe les SMS en mode texte (par défaut "Mode PDU" -> non-traitable)
    mGSM::uart.sendString(mGSM::commandesAtGsm.setModeText);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
    aIsOk=mCheckResponse("OK",kTimeOutResponse); //test la reponse

    mGSM::uart.clearInternalSerialBuffer(); //efface les buffers
    mGSM::uart.clearReceptionBuffer();

    //maj etat module
    if (!aIsOk)
	{
	this->state = kErrorSetModeSms;
	}
    }

//----------------------------------------------------------------
//fermeture du module du compteur
//----------------------------------------------------------------
void mGSM::mClose()
    {
    //Fin de communication et on leve les interrupts
    mGSM::uart.disable();

    //desactivation des io
    mGSM::enable.write(~BIT0);
    mGSM::reset.write(~BIT3);

    this->state = kDisconnected;
    }

//----------------------------------------------------------------
//donne le prochain SMS a etre lu
//
//aSMS : pointe la variable dans laquelle on veut recuperer le SMS
//retour : true si aSMS contient le SMS, false si tous les SMS ont ete lus
//----------------------------------------------------------------
bool mGSM::getSMS(char* aSMS)
    {
    char aDataReceived[kSciRecBufReceptionSize]; // data recues du buffer
    bool aIsOk = false;

    // demande le prochain SMS
    mGSM::uart.clearInternalSerialBuffer(); //efface
    mGSM::uart.sendString(mGSM::commandesAtGsm.getSMS);
    mGSM::uart.write((char) (indexSMS + 48));
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

    mGSM::timeOut.startDelayMS(kTimeOutResponse);
    while(!mGSM::uart.readFrame(aDataReceived) && !mGSM::timeOut.isDone()); //attend premiere partie (echo de la commande : non-interessant)

    if(mGSM::timeOut.isDone()) //erreur
	{
	this->state=kErrorReadSms;
	return false;
	}

    for(int i=0; 0!=aDataReceived[i] && i<kSciRecBufReceptionSize; i++) //efface la premiere partie
	{
	aDataReceived[i]=0;
	}

    mGSM::timeOut.startDelayMS(kTimeOutResponse);
    while(!mGSM::uart.readFrame(aDataReceived) && !mGSM::timeOut.isDone()); //attend deuxieme partie

    if(mGSM::timeOut.isDone())
	{
	this->state=kErrorReadSms;
	return false;
	}
    else if (0==strcmp(aDataReceived,"OK")) //pas de SMS a lire
	{
    	this->indexSMS=1;
    	//ne pas tout effacer durant les tests
    	//ne pas tout effacer durant les tests
    	//ne pas tout effacer durant les tests

    	//mGSM::uart.clearInternalSerialBuffer(); //efface le buffer
    	//uartGSM->sendString(commandesATGSM->deleteSMSAll); // efface tous SMS
    	//uartGSM->sendString(commandesATGSM->endAT);
        //aIsOk=mCheckResponse("OK",kTimeOutResponse); //test la reponse
        //mGSM::uart.clearInternalSerialBuffer(); //efface le buffer

    	if (!aIsOk)
    	    {
    	    this->state = kErrorDeleteAllSms;
    	    }

    	return false;
    	}
    else if (0==strcmp(aDataReceived,"ERROR")) // erreur de commande
    	{
	this->state = kErrorReadSms;

    	return false;
    	}
    else //message present
	{
	while(!mGSM::uart.readFrame(aDataReceived)); //lit le message

	for(int i=0; aDataReceived[i]!=0 && i<kSciRecBufReceptionSize; i++)
	    {
	    aSMS[i]=aDataReceived[i]; // copie le SMS
	    }

	this->indexSMS++;

	return true;
	}
    }

//----------------------------------------------------------------
//envoi un SMS
//
//aSMS : pointe la variable contenant le SMS a envoyer
//aPhoneNumber : pointe la varialble contenant le numéro de telephone
//retour : true si le SMS a ete envoye
//----------------------------------------------------------------
bool mGSM::sendSMS(char* aSMS, char* aPhoneNumber)
    {
    char aAnswer[kSciRecBufReceptionSize];
    UInt16 aValue; //variable de recuperation de valeur dans trame

    //sequence d'envoi
    mGSM::uart.clearInternalSerialBuffer();
    mGSM::uart.sendString(mGSM::commandesAtGsm.sendSMS);
    mGSM::uart.sendString(aPhoneNumber);
    mGSM::uart.sendString("\"\r\n");
    mGSM::uart.sendString(aSMS);
    mGSM::uart.write(0x1A); // "Ctrl + Z"

    mGSM::timeOut.startDelayMS(kTimeOutSendSms);
    while (!mGSM::uart.readFrame(aAnswer) && !mGSM::timeOut.isDone()); // attend reponse

    if(mGSM::timeOut.isDone()) //timeOut échu
	{
	//quitte le processus
	mGSM::uart.write(0x1B); //"ESC"
	mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
	mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

	this->state=kErrorSendSmsTimeOut;
	return false;
	}
    else if (sscanf(aAnswer,"+CMGS: %d",&aValue)) //message de validation d'envoi
	{
	this->state=kOk;
	return true;
	}
    else if (sscanf(aAnswer,"+CMS ERROR: %d",&aValue)) //message d'erreur connu
	{
	switch(aValue)
	    {
	    case 304 :
		this->state=kErrorModePDU; break;
	    case 305 :
		this->state=kErrorModeText; break;
	    case 310 :
		this->state=kErrorSimNotInserted; break;
	    case 311 :
		this->state=kErrorSimRequired; break;
	    case 313 :
		this->state=kErrorSimFailure; break;
	    case 314 :
		this->state=kErrorSimBusy; break;
	    case 315 :
		this->state=kErrorSimWrong; break;
	    case 316 :
		this->state=kErrorSimPukRequired; break;
	    case 317 :
		this->state=kErrorSimPin2Required; break;
	    case 318 :
		this->state=kErrorSimPuk2Required; break;
	    case 320 :
		this->state=kErrorMemoryFailure; break;
	    case 322 :
		this->state=kErrorMemoryFull; break;
	    case 332 :
		this->state=kErrorSendSmsTimeOut; break;
	    default :
		this->state=kErrorGeneral;
	    }
	return false;
	}
    else //message d'erreur non-connu
	{
	this->state=kErrorGeneral;
	return false;
	}
    }

//destructeur
mGSM::~mGSM()
    {
    }

//----------------------------------------------------------------
//controle si une reponse recue du GSM et la compare avec deux possibilités
//
//aGoodResponse : bonne reponse, renvoie true
//aTimeOutMs : duree en milliseconde durant laquelle la méthode essaie de trouver correpondance
//----------------------------------------------------------------
bool mGSM::mCheckResponse(char* aGoodResponse, UInt16 aTimeOutMs)
    {
    char aAnswer[kSciRecBufReceptionSize ];

    mGSM::timeOut.startDelayMS(aTimeOutMs);

    while(!mGSM::uart.readFrame(aAnswer) && !mGSM::timeOut.isDone()); //lit le message

    if (0==strcmp(aAnswer,aGoodResponse))
	{
	return true;
	}
    else
	{
	return false;
	}
    }






















