//*****************************************************************************
//Nom du fichier : Interface.h
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : classe abstraite de la couche interface
//*****************************************************************************

#ifndef __INTERFACE__
#define __INTERFACE__

#include <string>
#include <assert.h>
#include <stdlib.h>
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
    kStatusEnum status;	//état dans lequel se trouve l'interface

public:
    //constructeur
    Interface();

    //méthodes virtuelles pures que les classes filles devront implémenter
    virtual bool write(char aData) = 0;
    virtual char read() = 0;

    //permet de connaître l'état de l'interface
    kStatusEnum getStatus();

    //destructeur
    ~Interface();
    };

#endif
