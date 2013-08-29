//*****************************************************************************
//Nom du fichier : iDIO.cpp
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : interface mettant e disposition l'utilisation des ports en entrees/sorties digitales
//*****************************************************************************

#include "iDIO.h"

//offset a ajouter a l'adresse de base d'un port pour atteindre ses registres
typedef enum {
	kPortInput = 0x00,
	kPortOutput = 0x02,
	kPortDirection = 0x04,
	kPortResistorEnable = 0x06,
	kPortDriveStrength = 0x08,
	kPortSelect = 0x0A
} kRegisterOffset;

//constructeur
iDIO::iDIO(char* aPortAddress, char aMask) {
	this->theMask = aMask;
	this->thePortAddress = aPortAddress;
	this->status = kUnInitialized;

	//mets les bits concernes a 0 (digital I/O function selected)
	*((this->thePortAddress) + kPortSelect) = (*((this->thePortAddress)
			+ kPortSelect) & ~(this->theMask));
}

//nouvelles methodes
void iDIO::SetPortDirection(iDIOPortDirectionEnum aPortDirection) {
	//mets les bits concernes dans la direction souhaitee
	*((this->thePortAddress) + kPortDirection) =
			(this->theMask * aPortDirection)
					| (*((this->thePortAddress) + kPortDirection)
							& ~(this->theMask));
}

void iDIO::SetPortResistorEnable(iDIOPortResistorActivationEnum aState) {
	//mets les bits concernes dans l'etat souhaite (resistors disabled/enabled)
	*((this->thePortAddress) + kPortResistorEnable) = (this->theMask * aState)
			| (*((this->thePortAddress) + kPortResistorEnable)
					& ~(this->theMask));
}

void iDIO::SetPortResistorPolarity(iDIOPortResistorPolarityEnum aPolarity) {
	//la resistance appliquee est configuree par le registre de sortie
	this->write((char) (0xFF * aPolarity));
}

void iDIO::SetPortDriveStrength(iDIOPortDriveStrengthEnum aStrength) {
	//mets les bits concernes dans l'etat souhaite (full drive strength, reduced drive strength)
	*((this->thePortAddress) + kPortDriveStrength) =
			(this->theMask * aStrength)
					| (*((this->thePortAddress) + kPortDriveStrength)
							& ~(this->theMask));
}

//methodes virtuelles pures heritees devant etre definies
bool iDIO::write(UInt8 aData) {
	*((this->thePortAddress) + kPortOutput) = (aData & (this->theMask))
			| (*(this->thePortAddress) & ~(this->theMask));

	return true;
}

UInt8 iDIO::read() {
	return (*(this->thePortAddress) & (this->theMask));
}

void iDIO::InitAllPort() {
	//Initialization of ports (all unused pins as outputs with low-level
	P1OUT = 0x00;
	P1DIR = 0xFF;
	P2OUT = 0x00;
	P2DIR = 0xFF;
	P3OUT = 0x00;
	P3DIR = 0xFF;
	P4OUT = 0x00;
	P4DIR = 0xFF;
	P5OUT = 0x00;
	P5DIR = 0xFF;
	P6OUT = 0x00;
	P6DIR = 0xFF;
	P7OUT = 0x00;
	P7DIR = 0xFF;
	P8OUT = 0x00;
	P8DIR = 0xFF;
	PJDIR = 0xFF;
	PJOUT = 0x00;
}

//destructeur
iDIO::~iDIO() {
}
