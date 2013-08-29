//*****************************************************************************
//Nom du fichier : mGSM.cpp
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#define kTimeToEnableIo 2000
#define kTimeOutResponse 3000 //TODO mettre a 10sec
#define kTimeOutSendSms 30000 //TODO a changer en 70000
#define kWaitCommand 4000
#define kWaitSendSms 200
#define kSizeStringDate 17
#define kSizeParseSms 50

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
    UInt8 i = 0;

    //autorisation de communiquer et enable des interruptions
    mGSM::uart.enable();
    mGSM::enable.write(BIT4);
    mGSM::reset.write(BIT3);

    mGSM::timeOut.startDelayMS(kTimeToEnableIo); // attend que les io soient changees
    while (!mGSM::timeOut.isDone())
	;

    mGSM::uart.clearInternalSerialBuffer(); //efface le buffer
    mGSM::uart.clearReceptionBuffer();


    //enable mode sms
    mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
    while (!mGSM::timeOut.isDone())
	;

    mGSM::uart.sendString(mGSM::commandesAtGsm.enableSMS);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

    aIsOk = mCheckResponse("OK", "ERROR", kTimeOutResponse); //test la reponse

    //maj etat module
    if (!aIsOk)
	{
	this->state = kErrorSetModeSms;
	}

    mGSM::uart.clearReceptionBuffer();
    mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
    while (!mGSM::timeOut.isDone())
	;

    //controle si la carte SIM est deja delockee
    mGSM::uart.sendString(mGSM::commandesAtGsm.questStatePIN);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

    aIsOk = mCheckResponse("+CPIN: READY", "+CPIN: SIM PIN", kTimeOutResponse); //test la reponse

    //deverouille la carte SIM, si besoin est
    if (!aIsOk)
	{
	mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
	while (!mGSM::timeOut.isDone())
	    ;

	mGSM::uart.clearReceptionBuffer();
	mGSM::uart.sendString(mGSM::commandesAtGsm.delockPIN);
	mGSM::uart.sendString(this->codePIN);
	mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
	aIsOk = mCheckResponse("OK", "ERROR", kTimeOutResponse); //test la reponse

	//maj etat module
	if (!aIsOk)
	    {
	    this->state = kErrorEnterPin;
	    }
	}

    // passe les SMS en mode texte (par défaut "Mode PDU" -> non-traitable)
    mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
    while (!mGSM::timeOut.isDone())
	;

    mGSM::uart.clearReceptionBuffer();
    mGSM::uart.sendString(mGSM::commandesAtGsm.setModeText);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
    aIsOk = mCheckResponse("OK", "ERROR", kTimeOutResponse); //test la reponse

    //maj etat module
    if (!aIsOk)
	{
	this->state = kErrorSetModeText;
	}

    // enable Service Data, pour la lecture du credit
    mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
    while (!mGSM::timeOut.isDone())
	;

    mGSM::uart.clearReceptionBuffer();
    mGSM::uart.sendString(mGSM::commandesAtGsm.enableServiceData);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

    aIsOk = mCheckResponse("OK", "ERROR", kTimeOutResponse); //test la reponse

    //maj etat module
    if (!aIsOk)
	{
	this->state = kErrorEnableServiceData;
	}

    mGSM::uart.clearInternalSerialBuffer(); //efface les buffers
    mGSM::uart.clearReceptionBuffer();
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
    char aDataReceived[kSciRecBufReceptionSize ] = ""; // data recues du buffer
    UInt8 aTemp; //variable intermediaire de retour du sscanf
    bool aIsOk=false; //variable de retour
    bool aIsError=false; //variable de retour
    bool aRet=false; //variable de retour


    // demande le prochain SMS
    mGSM::uart.clearInternalSerialBuffer(); //efface buffer
    mGSM::uart.clearReceptionBuffer();

    mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
    while (!mGSM::timeOut.isDone())
	;

    //sequence de commande
    mGSM::uart.sendString(mGSM::commandesAtGsm.getSMS);
    mGSM::uart.write((char) (indexSMS + 48));
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

    mGSM::timeOut.startDelayMS(kTimeOutResponse);
    while ((!mGSM::uart.readFrameToCRLF(aDataReceived)) && (!mGSM::timeOut.isDone()) && (!aIsError) && (!aIsOk))
	{
	aTemp = strcmp(aDataReceived, "OK");
	if (0 == aTemp) //pas de SMS a lire
	    {
	    this->indexSMS = 1;
	    //ne pas tout effacer durant les tests
	    //ne pas tout effacer durant les tests
	    //ne pas tout effacer durant les tests

	    //uartGSM->sendString(commandesATGSM->deleteSMSAll); // efface tous SMS
	    //uartGSM->sendString(commandesATGSM->endAT);
	    //aIsOk=mCheckResponse("OK", "ERROR", kTimeOutResponse); //test la reponse
	    //mGSM::uart.clearInternalSerialBuffer(); //efface le buffer

	    if (!aIsOk)
		{
		this->state = kErrorDeleteAllSms;
		}

	    aIsError = true;
	    }

	else
	    {
	    aTemp = strcmp(aDataReceived, "ERROR");
	    if (0 == aTemp) // erreur de commande
		{
		this->state = kErrorReadSms;

		aIsError = true; //ici TODO
		}
	    else //message present
		{
		if ('+' == aDataReceived[0] && 'C' == aDataReceived[1]
			&& 'M' == aDataReceived[2] && ':' == aDataReceived[5]) //controle le debut de l'entete
		    {
		    mGSM::timeOut.startDelayMS(kTimeOutResponse);
		    while (!mGSM::uart.readFrameToCRLF(aDataReceived)
			    && !mGSM::timeOut.isDone())
			; //lit le message

		    if (mGSM::timeOut.isDone())
			{
			this->state = kErrorReadSms;
			aRet = false;
			}
		    else
			{
			strcpy(aSMS, aDataReceived); // copie du SMS (il ne peut y avoir qu'une seule ligne)
			this->indexSMS++;
			aRet = true;
			}
		    }
		}
	    }
	}
    if (mGSM::timeOut.isDone())
	{
	this->state = kErrorReadSms;
	aRet = false;
	}

    return aRet;
    }

//----------------------------------------------------------------
//envoi un SMS
//
//aSMS : pointe la variable contenant le SMS a envoyer
//aPhoneNumber : pointe la varialble contenant le numéro de telephone
//retour : true si le SMS a ete envoye
//----------------------------------------------------------------
bool mGSM::sendSMS(UInt8* aSMS, UInt8* aPhoneNumber)
    {
    char aAnswer[kSciRecBufSize ];
    UInt16 aValue; //variable de recuperation de valeur dans trame
    UInt8 aTemp; //variable intermediaire de retour du sscanf
    bool aIsOk = false;
    bool aIsError = false;

    mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
    while (!mGSM::timeOut.isDone())
	;

    mGSM::uart.clearInternalSerialBuffer();
    mGSM::uart.clearReceptionBuffer();

//sequence d'envoi
    mGSM::uart.sendString(mGSM::commandesAtGsm.sendSMS);
    mGSM::uart.sendString((UInt8*)aPhoneNumber);
    mGSM::uart.sendString((UInt8*)"\"\r");
    mGSM::mSenderSms((UInt8*)aSMS);
    mGSM::uart.clearReceptionBuffer();
    mGSM::uart.write(0x1A); // "Ctrl + Z" pour envoyer

    mGSM::timeOut.startDelayMS(kTimeOutSendSms);
    while (!mGSM::timeOut.isDone() && !aIsOk && !aIsError)
	{
	if (mGSM::uart.readFrameToCRLF(aAnswer))
	    {
	    aTemp = sscanf(aAnswer, "+CMGS: %d", &aValue); //message de validation d'envoi
	    if (1 == aTemp)
		{
		this->state = kOk;
		aIsOk = true;
		}
	    else
		{
		aTemp = sscanf(aAnswer, "+CMS ERROR: %d", &aValue);
		if (1 == aTemp) //message d'erreur connu
		    {
		    switch (aValue)
			{
		    case 304:
			this->state = kErrorModePDU;
			break;
		    case 305:
			this->state = kErrorModeText;
			break;
		    case 310:
			this->state = kErrorSimNotInserted;
			break;
		    case 311:
			this->state = kErrorSimRequired;
			break;
		    case 313:
			this->state = kErrorSimFailure;
			break;
		    case 314:
			this->state = kErrorSimBusy;
			break;
		    case 315:
			this->state = kErrorSimWrong;
			break;
		    case 316:
			this->state = kErrorSimPukRequired;
			break;
		    case 317:
			this->state = kErrorSimPin2Required;
			break;
		    case 318:
			this->state = kErrorSimPuk2Required;
			break;
		    case 320:
			this->state = kErrorMemoryFailure;
			break;
		    case 322:
			this->state = kErrorMemoryFull;
			break;
		    case 332:
			this->state = kErrorSendSmsTimeOut;
			break;
		    default:
			this->state = kErrorGeneral;
			}
		    aIsError = true;
		    }
		}
	    }
	}
    if (mGSM::timeOut.isDone())
	{
	//quitte le processus
	mGSM::uart.write(0x1B); //"ESC"
	mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
	mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);
	this->state = kErrorSendSmsTimeOut;
	aIsOk = false;
	}

    return aIsOk;
    }

//destructeur
mGSM::~mGSM()
    {
    }

//----------------------------------------------------------------
//obtenir l'heure
//
//retour :  la date complete
//----------------------------------------------------------------
tDate mGSM::getDate()
    {
    tDate aDate;
    char aDataReceived[kSciRecBufReceptionSize ] = ""; // data recues du buffer
    char aDateString[kSizeStringDate] = "";
    char aNumberPhoneString[kSizeStringDate] = "";
    bool aIsOk = false;
    bool aIsSms = true;
    UInt8 aIndex = this->indexSMS;
    UInt16 i = 0;
    UInt8 j = 0;

    if (mGSM::sendSMS((UInt8*)"getDate", (UInt8*)this->phoneNumber)) // on s'envoie un SMS
	{
	while (aIsSms)
	    {
	    // demande le prochain SMS
	    mGSM::uart.clearInternalSerialBuffer(); //efface
	    mGSM::uart.sendString(mGSM::commandesAtGsm.getSMS);
	    mGSM::uart.write((char) (aIndex + 48));
	    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

	    mGSM::timeOut.startDelayMS(kTimeOutResponse);
	    while (!mGSM::uart.readFrameToCRLF(aDataReceived)
		    && !mGSM::timeOut.isDone())
		; //attend premiere partie (echo de la commande : non-interessant)

	    if (mGSM::timeOut.isDone()) //erreur
		{
		this->state = kErrorReadSms;
		}

	    for (int i = 0;
		    0 != aDataReceived[i] && i < kSciRecBufReceptionSize ; i++) //efface la premiere partie
		{
		aDataReceived[i] = 0;
		}

	    mGSM::timeOut.startDelayMS(kTimeOutResponse);
	    while (!mGSM::uart.readFrameToCRLF(aDataReceived)
		    && !mGSM::timeOut.isDone())
		; //attend deuxieme partie

	    if ('+' != aDataReceived[0]) //verifie qu'il y aie bien un sms
		{
		aIsSms = false;
		}
	    else
		{
		i = 0;
		while (!(aDataReceived[i] == '+' && aDataReceived[i - 1] == '\"')) // recherche la position de la date
		    {
		    i++;
		    }

		for (j = 0; j < kNbFiguresPhone; i++, j++)
		    {
		    aNumberPhoneString[j] = aDataReceived[i]; // copie le numero
		    }

		if (0 == strcmp(aNumberPhoneString, (char*) this->phoneNumber)) // si c'est le bon numero
		    {
		    i = 0;
		    while (aDataReceived[i] != '/') // recherche la position de la date
			{
			i++;
			}

		    for (i -= 2, j = 0; j < kSizeStringDate; i++, j++)
			{
			aDateString[j] = aDataReceived[i]; // copie la date
			}

		    if (sscanf(aDateString, "%d/%d/%d,%d:%d:%d", &aDate.year,
			    &aDate.month, &aDate.day, &aDate.hour,
			    &aDate.minute, &aDate.second))
			{
			this->state = kOk;
			}
		    }
		}
	    }
	}
    return aDate;
    }

//----------------------------------------------------------------
//obtenir le credit restant
//
//retour : 	le credit en centimes de franc
//----------------------------------------------------------------
UInt16 mGSM::getCredit()
    {
    UInt16 aCredit = 0;
    UInt16 i = 0;
    bool aIsOk = false;
    char aDataReceived[kSciRecBufReceptionSize ] = ""; // data recues du buffer

    mGSM::uart.clearReceptionBuffer();
    mGSM::uart.clearInternalSerialBuffer();

    mGSM::timeOut.startDelayMS(kWaitCommand); // attend avant commande
    while (!mGSM::timeOut.isDone())
	;

    mGSM::uart.sendString(mGSM::commandesAtGsm.getCredit);
    mGSM::uart.sendString(mGSM::commandesAtGsm.endAT);

    mGSM::timeOut.startDelayMS(kTimeOutResponse);
    while (!aIsOk && !mGSM::timeOut.isDone()) // cherche la deuxieme partie
	{
	if (mGSM::uart.readFrameToCRLF(aDataReceived))
	    {
	    if ('+' == aDataReceived[0] && 'C' == aDataReceived[1]
		    && 'U' == aDataReceived[2] && 'S' == aDataReceived[3]
		    && 'D' == aDataReceived[4])
		{
		aIsOk = true;
		}
	    }
	}

    if (aIsOk)
	{
	aIsOk = false;
	while (!aIsOk && i < kSciRecBufSize - 2)
	    {
	    if (aDataReceived[i] <= 57 && aDataReceived[i] >= 48
		    && (aDataReceived[i + 1] == '.'
			    || aDataReceived[i + 1] == ',')
		    && aDataReceived[i + 2] <= 57 && aDataReceived[i + 2] >= 48) //cherche le montant dans la chaine de la forme x.x ou x,x
		{
		aIsOk = true;
		}
	    else
		{
		i++;
		}
	    }

	if (aIsOk)
	    {
	    if (aDataReceived[i - 1] <= 57 && aDataReceived[i - 1] >= 48)
		{
		aCredit = (aDataReceived[i - 1] - 48) * 1000; // ajoute les dizaines de franc
		}
	    aCredit += (aDataReceived[i] - 48) * 100
		    + (aDataReceived[i + 2] - 48) * 10
		    + (aDataReceived[i + 3] - 48) * 1; // ajoute le reste
	    }
	else
	    {
	    this->state = kErrorGetCredit;
	    }
	}
    else
	{
	this->state = kErrorGetCredit;
	}

    return aCredit;
    }

//----------------------------------------------------------------
//controle si une reponse recue du GSM et la compare avec deux possibilités
//
//aGoodResponse : bonne reponse, renvoie true
//aBadResponse : mauvaise reponse, renvoie false
//aTimeOutMs : duree en milliseconde durant laquelle la méthode essaie de trouver correpondance
//----------------------------------------------------------------
bool mGSM::mCheckResponse(char* aGoodResponse, char* aBadResponse,
	UInt16 aTimeOutMs)
    {
    char aAnswer[kSciRecBufReceptionSize ] = "";
    bool aTemp; // variable temporaire de recuperation de retour de fonction
    int aTemp2 = 1;
    bool aIsOk = false;
    bool aIsError = false;

    mGSM::timeOut.startDelayMS(aTimeOutMs);
    while (!mGSM::timeOut.isDone() && !aIsOk && !aIsError) //lit le message
	{
	aTemp = false;
	aTemp = mGSM::uart.readFrameToCRLF(aAnswer);
	if (true == aTemp)
	    {
	    aTemp2 = strcmp(aAnswer, aGoodResponse);
	    if (0 == aTemp2)
		{
		aIsOk = true;
		}
	    else
		{
		aTemp2 = strcmp(aAnswer, aBadResponse);
		if (0 == aTemp2)
		    {
		    aIsError = true;
		    }
		}
	    }
	}

    if (mGSM::timeOut.isDone())
	{
	aIsError = true;
	}

    return aIsOk;
    }

//----------------------------------------------------------------
//envoie le texte SMS sur l'UART en le parsant pour ne pas bourrer le FIFO du module GSM
//
//aSMS : le SMS à transmettre
//----------------------------------------------------------------
void mGSM::mSenderSms(UInt8* aSMS)
    {
    UInt16 i = 0;
    while (aSMS[i] != 0)
	{
	mGSM::uart.write(aSMS[i]); // envoie la chaine char par char

	if (0 == i % kSizeParseSms)
	    {
	    mGSM::timeOut.startDelayMS(kWaitSendSms);
	    while (!mGSM::timeOut.isDone())
		; // attend pour ne pas bourrer le FIFO du module GSM
	    }

	i++;
	}
    }

