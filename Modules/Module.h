//*****************************************************************************
//Nom du fichier : Module.h
//Auteur et Date : SAVY Cyrille 24.04.2013
//But : classe abstraite de la couche Module
//*****************************************************************************

#ifndef __MODULE__
#define __MODULE__

class Module
    {
public:
    //constructeur
    Module();

    //ouverture du module
    virtual void mOpen() = 0;

    //fermeture du module
    virtual void mClose() = 0;

    //configuration du module
    virtual void mSetup() = 0;

    //destructeur
    virtual ~Module();

    };

#endif
