//*****************************************************************************
//Nom du fichier : Interface.cpp
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : classe abstraite de la couche interface
//*****************************************************************************

#include <string>
#include <assert.h>
#include "Interface.h"

//constructeur
Interface::Interface()
    {
    }

//permet de connaître l'état de l'interface
kStatusEnum Interface::getStatus()
    {
    return this->status;
    }

//destructeur
Interface::~Interface()
    {
    }

