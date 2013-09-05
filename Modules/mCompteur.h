//*****************************************************************************
//Nom du fichier : mCompteur.h
//Auteurs et Date : GIGANDET Simon 19.08.2013
//But : couche module permettant l'acces au compteur d'eau GWF
//*****************************************************************************

#ifndef M_COMPTEUR_H
#define M_COMPTEUR_H

#include "Module.h"
#include "../Def/def.h"
#include "../Interfaces/iUART.h"
#include "../Interfaces/iDIO.h"
#include "../Tools/tCompteur.h"
#include "mDelay.h"

typedef enum // choix du compteur
    {
    kMeter1 = 2,
    kMeter2 = 3,
    kMeterSimulation = 1
    } iMeterChannel;

using namespace std;

class mCompteur: public Module
    {
private:
    // entree
    static iUART uart; // uart de reception de la trame du compteur
    static iDIO enable; // entree d'activation de la lecteur des compteurs
    static iDIO channelMultiplexer; // entree de selection du comtpeur desire
    static iDIO cptSim; //sortie sur l'interface de simulation d'un compteur

    //tool
    UInt8 channelCodeMultiplexer; // code pour que le multiplexeur selectionne le bon compteur
    tCompteur *compteurParam;
    UInt8 aStatus;

    void sendFrame(char* aFrame);
    void sendChar(char aChar);

public:
    //----------------------------------------------------------------
    //constructeur
    //
    //aChannel : choix du compteur d'eau
    //----------------------------------------------------------------
    mCompteur(iMeterChannel aChannel, mEEPROM *mEeprom);

    //----------------------------------------------------------------
    //destructeur
    //----------------------------------------------------------------
    ~mCompteur();

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
    //lecture de l'indice du compteur
    //
    //retour : la valeur de l'indice du compteur, 0 si la valeur n'a pas pu etre lue
    //
    //exemple de format de trame : "/GWF Wasser      V4.1\r\n7.0(02514*m3)\r\n0.09(03-11-04)\r\n0.00(0434448)\r\n0.01(DN20)\r\n!\r\n"
    //avec 02514 comme indice
    //----------------------------------------------------------------
    bool mRead(UInt32* aIndex);

    //----------------------------------------------------------------
    //envoi d'une trame a la partie simulation de l'interface compteur
    //
    //aIndex : int : la valeur de l'index qui est envoyee
    //
    //exemple de format de trame : "/GWF Wasser      V4.1\r\n7.0(02514*m3)\r\n0.09(03-11-04)\r\n0.00(0434448)\r\n0.01(DN20)\r\n!\r\n"
    //avec 02514 comme indice
    //----------------------------------------------------------------
    void simulationCpt(int aIndex);

    };
#endif
