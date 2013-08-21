#ifndef TCOMPTEUR_H_
#define TCOMPTEUR_H_

#include <string>
#include <assert.h>

#include "tParameters.h"

class tCompteur : public tParameters
{
public:
	UInt8 aManufacturer[4]; // Fabriquant : GWF
	UInt8 aFluide[10]; //Fluide contenu : Wasser ou Gas
	UInt8 aVersNum[5]; //Version de compteur : VX.X
	UInt8 aSerialNum[8]; //Numero de serie : xxxxxxx
	UInt8 aFabDate[9]; //Date de fabrication ou calibration : xx-xx-xx
	UInt8 aNominalSize[10]; // Taille nominal : (xxxx)

	tCompteur(mEEPROM *mEeprom,UInt16 aModeNum);
	void save();
	void load();

};


#endif
