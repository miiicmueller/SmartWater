//*****************************************************************************
//Nom du fichier : mGSM.h
//Auteurs et Date : SAVY Cyrille 24.04.2013
//But : couche module permettant d'utiliser le module GSM de Telit : GL865
//*****************************************************************************

#ifndef __MGSM__
#define __MGSM__

#include <string>
#include <assert.h>

#include "Module.h"
#include "../Interfaces/iUART.h"
#include "../Interfaces/iDIO.h"
#include "../Tools/tCommandesAT.h"
#include "../Tools/tDate.h"
#include "mDelay.h"

typedef enum // choix du compteur
    {
    kOk, //valeur  generale
    kDisconnected,
    kErrorGeneral,
    kErrorEnterPin, // erreurs de parametrage
    kErrorSetModeSms,
    kErrorSetModeText,
    kErrorDeleteAllSms, // erreurs de lecture
    kErrorReadSms,
    kErrorModePDU, // erreurs d'envoi
    kErrorModeText,
    kErrorSimNotInserted,
    kErrorSimRequired,
    kErrorSimFailure,
    kErrorSimBusy,
    kErrorSimWrong,
    kErrorSimPukRequired,
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
    static tCommandesAT commandesAtGsm; //commandes pour contr�ler le module GSM
    UInt16 indexSMS; //index designant le prochaine SMS a devoir etre lu
    mGSMStateEnum state; // etat du module
    static mDelay timeOut;


    //----------------------------------------------------------------
    //controle si une reponse recue du GSM et la compare avec deux possibilit�s
    //
    //aGoodResponse : bonne reponse, renvoie true
    //aBadResponse : reponse lorsque la commande s'est mal deroulee, renvoie false
    //aTimeOutMs : duree en milliseconde durant laquelle la m�thode essaie de trouver correpondance
    //----------------------------------------------------------------
    bool mCheckResponse(UInt8* aGoodResponse, UInt16 aTimeOutMs);

public:

    UInt8* phoneNumber; //numero de telephone de la carte SIM. Format : "+417********"
    UInt8* codePIN;

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
    bool getSMS(UInt8* aSMS);

    //----------------------------------------------------------------
    //envoi un SMS
    //
    //aSMS : pointe la variable contenant le SMS a envoyer
    //aPhoneNumber : pointe la varialble contenant le num�ro de telephone
    //retour : 	true si le SMS a ete envoye
    //----------------------------------------------------------------
    bool sendSMS(UInt8* aSMS, UInt8* aPhoneNumber);

    //----------------------------------------------------------------
    //obtenir l'heure
    //
    //retour :  la date complete
    //----------------------------------------------------------------
    tDate getHour();

    //----------------------------------------------------------------
    //obtenir le credit restant
    //
    //retour : 	le credit en centimes de franc
    //----------------------------------------------------------------
    UInt16 getCredit();




    };
#endif
