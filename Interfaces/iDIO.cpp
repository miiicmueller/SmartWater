//*****************************************************************************
//Nom du fichier : iDIO.cpp
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : interface mettant à disposition l'utilisation des ports en entrées/sorties digitales
//*****************************************************************************

#include "iDIO.h"

//offset à ajouter à l'adresse de base d'un port pour atteindre ses registres
typedef enum
    {
    kPortInput = 0x00,
    kPortOutput = 0x02,
    kPortDirection = 0x04,
    kPortResistorEnable = 0x06,
    kPortDriveStrength = 0x08,
    kPortSelect = 0x0A
    } kRegisterOffset;

//constructeur
iDIO::iDIO(char* aPortAddress, char aMask)
    {
    this->theMask = aMask;
    this->thePortAddress = aPortAddress;
    this->status = kUnInitialized;

    //mets les bits concernés à 0 (digital I/O function selected)
    *((this->thePortAddress) + kPortSelect) = (*((this->thePortAddress)
	    + kPortSelect) & ~(this->theMask));
    }

//nouvelles méthodes
void iDIO::SetPortDirection(iDIOPortDirectionEnum aPortDirection)
    {
    //mets les bits concernés dans la direction souhaitée
    *((this->thePortAddress) + kPortDirection) =
	    (this->theMask * aPortDirection)
		    | (*((this->thePortAddress) + kPortDirection)
			    & ~(this->theMask));
    }

void iDIO::SetPortResistorEnable(iDIOPortResistorActivationEnum aState)
    {
    //mets les bits concernés à dans l'état souhaité (resistors disabled/enabled)
    *((this->thePortAddress) + kPortResistorEnable) = (this->theMask * aState)
	    | (*((this->thePortAddress) + kPortResistorEnable)
		    & ~(this->theMask));
    }

void iDIO::SetPortResistorPolarity(iDIOPortResistorPolarityEnum aPolarity)
    {
    //la résistance appliquée est configurée par le registre de sortie
    this->write((char) (0xFF * aPolarity));
    }

void iDIO::SetPortDriveStrength(iDIOPortDriveStrengthEnum aStrength)
    {
    //mets les bits concernés à dans l'état souhaité (full drive strength, reduced drive strength)
    *((this->thePortAddress) + kPortDriveStrength) =
	    (this->theMask * aStrength)
		    | (*((this->thePortAddress) + kPortDriveStrength)
			    & ~(this->theMask));
    }

//méthodes virtuelles pures héritées devant être définies
bool iDIO::write(char aData)
    {
    *((this->thePortAddress) + kPortOutput) = (aData & (this->theMask))
	    | (*(this->thePortAddress) & ~(this->theMask));

    return true;
    }

char iDIO::read()
    {
    return (*(this->thePortAddress) & (this->theMask));
    }

//destructeur
iDIO::~iDIO()
    {
    }
