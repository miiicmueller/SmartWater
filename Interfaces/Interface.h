//*****************************************************************************
//Nom du fichier : Interface.h
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : classe abstraite de la couche interface
//*****************************************************************************

#ifndef __INTERFACE__
#define __INTERFACE__

#include "../Def/def.h"

typedef enum
    {
    kActive,
    kError,
    kSuspended,
    kClosed,
    kBusy,
    kUnInitialized
    } kStatusEnum;

class Interface
    {
public:
    //tools
    kStatusEnum status;	//etat dans lequel se trouve l'interface

public:
    //constructeur
    Interface();

    //methodes virtuelles pures que les classes filles devront implementer
    virtual bool write(UInt8 aData) = 0;
    virtual UInt8 read() = 0;

    //permet de connaetre l'etat de l'interface
    kStatusEnum getStatus();

    //destructeur
    virtual ~Interface();
    };

#endif
