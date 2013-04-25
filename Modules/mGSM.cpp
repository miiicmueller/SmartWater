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
    //Initialisation des attributs
    this->commandesATGSM = aCommandesATGSM;
    this->outputGSM = aOutputGSM;
    this->uartGSM = aUartGSM;
    this->isUnlocked = false;

    //Configuration des classes associées
    mSetup();
    }

/**
 * Fonction de configuration du module GSM
 */
void mGSM::mSetup()
    {
    // On envoie sur USCI_A0 + LSB first (on peut croiser) + pas de paritée + données de 8 bits + vitesse 115200
    this->uartGSM->config(kUSCI_A0, kLSBFirst, k1StBits, kNone, k8bits, 115200);

    //La sortie reset_Gsm est sir P7.3
    this->outputGSM->SetPortDirection(kOutput);

    //Mode pleine puissance : à voir ...
    this->outputGSM->SetPortDriveStrength(kFullStrength);

    }

/**
 * Fonction permettant l'ouverture du periphérique GSM
 */
void mGSM::mOpen()
    {
    //Autorisation de communiquer et enable des interruptions
    this->uartGSM->enable();

    //Au bol : On met à 1 le reset et la sortie MOS
    this->outputGSM->write(1);
    }

/**
 * Fonction permettant de fermer le periphérique GSM
 */
void mGSM::mClose()
    {
    //Fin de communication et on lève les interrupts
    this->uartGSM->disable();

    //Au bol : On met à 0 le reset et la sortie MOS
    this->outputGSM->write(0);
    }

bool mGSM::getSMS(char* aSMS)
    {
    return "";
    }

void mGSM::sendSMS(std::string data)
    {
    }

//destructeur
mGSM::~mGSM()
    {
    }
