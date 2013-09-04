//*****************************************************************************
//Nom du fichier : mGSM.h
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#ifndef __MGSM__
#define __MGSM__

#include <string>
#include <stdio.h>
#include <assert.h>

#include "Module.h"
#include "../Interfaces/iUART.h"
#include "../Interfaces/iDIO.h"
#include "../Tools/tCommandesAT.h"
#include "../Tools/tDate.h"
#include "mDelay.h"

#define kNbFiguresPhone 12
#define kNbFiguresPin 4

typedef enum // choix du compteur
    {
    kOk, //valeur  generale
    kDisconnected,
    kErrorGeneral,
    kErrorEnterPin, // erreurs de parametrage
    kErrorSetModeSms,
    kErrorSetModeText,
    kErrorEnableServiceData,
    kErrorDeleteAllSms, // erreurs de lecture
    kErrorGetCredit,
    kErrorReadSms,
    kErrorModePDU, // erreurs d'envoi
    kErrorModeText,
    kErrorSimNotInserted,
    kErrorSimRequired,
    kErrorSimFailure,
    kErrorAntenna,
    kErrorDecodeDate,
    kErrorSimBusy,
    kErrorSimWrong,
    kErrorSimPukRequired,
    kErrorGetStateMemory,
    kErrorSimPin2Required,
    kErrorSimPuk2Required,
    kErrorMemoryFailure,
    kErrorMemoryFull,
    kErrorSendSmsTimeOut
    } mGSMStateEnum;

using namespace std;

class mGSM: public Module
    {
private:
    //input
    static iDIO enable;
    static iDIO reset;
    static iUART uart;

    //tools
    static tCommandesAT commandesAtGsm; //commandes pour contrôler le module GSM
    UInt16 indexSMS; //index designant le prochaine SMS a devoir etre lu
    static mDelay timeOut;

    //----------------------------------------------------------------
    //controle si une reponse recue du GSM et la compare avec deux possibilités
    //
    //aGoodResponse : bonne reponse, renvoie true
    //aBadResponse : mauvaise reponse, renvoie false
    //aTimeOutMs : duree en milliseconde durant laquelle la méthode essaie de trouver correpondance
    //retour : true si bonne reponse, false si mauvaise reponse ou si reponse differente
    //----------------------------------------------------------------
    bool mCheckResponse(char* aGoodResponse, char* aBadResponse,
	    UInt16 aTimeOutMs);

    //----------------------------------------------------------------
    //envoie le texte SMS sur l'UART en le parsant pour ne pas bourrer le FIFO du module GSM
    //
    //aSMS : le SMS à transmettre
    //----------------------------------------------------------------
    void mSenderSms(UInt8* aSMS);

public:

    UInt8 phoneNumber[kNbFiguresPhone + 1]; //numero de telephone de la carte SIM. Format : "+417********"
    UInt8 codePIN[kNbFiguresPin + 1];
    mGSMStateEnum state; // etat du module

    //----------------------------------------------------------------
    //constructeur
    //--------------------------------------------------------------
    mGSM();

    //----------------------------------------------------------------
    //destructeur
    //--------------------------------------------------------------
    ~mGSM();

    //----------------------------------------------------------------
    //parametrage du module du compteur
    //----------------------------------------------------------------
    void mSetup();

    //----------------------------------------------------------------
    //ouverture du module du compteur
    //----------------------------------------------------------------
    void mOpen();

    //----------------------------------------------------------------
    //fermeture du module du compteur
    //----------------------------------------------------------------
    void mClose();

    //----------------------------------------------------------------
    //donne le prochain SMS a etre lu
    //
    //aSMS : pointe la variable dans laquelle on veut recuperer le SMS
    //retour : 	true si aSMS contient le SMS, false si tous les SMS ont ete lus
    //----------------------------------------------------------------
    bool getSMS(char* aSMS);

    //----------------------------------------------------------------
    //envoi un SMS
    //
    //aSMS : pointe la variable contenant le SMS a envoyer
    //aPhoneNumber : pointe la varialble contenant le numéro de telephone
    //retour : 	true si le SMS a ete envoye
    //----------------------------------------------------------------
    bool sendSMS(UInt8* aSMS, UInt8* aPhoneNumber);

    //----------------------------------------------------------------
    //obtenir l'heure
    //
    //aDate : pointeur sur la date complete
    //retour : true si il n'y a a pas d'erreur
    //remarque : ce service coute un SMS
    //----------------------------------------------------------------
    bool getDate(tDate* aDate);

    //----------------------------------------------------------------
    //obtenir le credit restant
    //
    //retour : 	le credit en centimes de franc
    //----------------------------------------------------------------
    UInt16 getCredit();

    //----------------------------------------------------------------
    //fonction pour connaitre combien de SMS sont dans la memoire SIM
    //
    //retour : le nombre de SMS present dans la memoire
    //----------------------------------------------------------------
    UInt8 getNbSms();

    };
#endif
