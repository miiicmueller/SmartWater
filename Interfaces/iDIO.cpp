//*****************************************************************************
//Nom du fichier : iDIO.cpp
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : interface mettant � disposition l'utilisation des ports en entr�es/sorties digitales
//*****************************************************************************

#include "iDIO.h"

//offset � ajouter � l'adresse de base d'un port pour atteindre ses registres
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

    //mets les bits concern�s � 0 (digital I/O function selected)
    *((this->thePortAddress) + kPortSelect) = (*((this->thePortAddress)
	    + kPortSelect) & ~(this->theMask));
    }

//nouvelles m�thodes
void iDIO::SetPortDirection(iDIOPortDirectionEnum aPortDirection)
    {
    //mets les bits concern�s dans la direction souhait�e
    *((this->thePortAddress) + kPortDirection) =
	    (this->theMask * aPortDirection)
		    | (*((this->thePortAddress) + kPortDirection)
			    & ~(this->theMask));
    }

void iDIO::SetPortResistorEnable(iDIOPortResistorActivationEnum aState)
    {
    //mets les bits concern�s � dans l'�tat souhait� (resistors disabled/enabled)
    *((this->thePortAddress) + kPortResistorEnable) = (this->theMask * aState)
	    | (*((this->thePortAddress) + kPortResistorEnable)
		    & ~(this->theMask));
    }

void iDIO::SetPortResistorPolarity(iDIOPortResistorPolarityEnum aPolarity)
    {
    //la r�sistance appliqu�e est configur�e par le registre de sortie
    this->write((char) (0xFF * aPolarity));
    }

void iDIO::SetPortDriveStrength(iDIOPortDriveStrengthEnum aStrength)
    {
    //mets les bits concern�s � dans l'�tat souhait� (full drive strength, reduced drive strength)
    *((this->thePortAddress) + kPortDriveStrength) =
	    (this->theMask * aStrength)
		    | (*((this->thePortAddress) + kPortDriveStrength)
			    & ~(this->theMask));
    }

//m�thodes virtuelles pures h�rit�es devant �tre d�finies
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
