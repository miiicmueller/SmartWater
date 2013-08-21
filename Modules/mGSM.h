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
    kError,
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
    } iState;


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
    int indexSMS; //index designant le prochaine SMS a devoir etre lu
    iState state; // etat du module
    static mDelay timeOut;


    //----------------------------------------------------------------
    //controle si une reponse recue du GSM et la compare avec deux possibilités
    //
    //aGoodResponse : bonne reponse, renvoie true
    //aBadResponse : reponse lorsque la commande s'est mal deroulee, renvoie false
    //aTimeOutMs : duree en milliseconde durant laquelle la méthode essaie de trouver correpondance
    //----------------------------------------------------------------
    bool mCheckResponse(char* aGoodResponse, UInt16 aTimeOutMs);

public:

    char* phoneNumber; //numero de telephone de la carte SIM. Format : "+417********"
    char* codePIN;

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
    bool sendSMS(char* aSMS, char* aPhoneNumber);

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
