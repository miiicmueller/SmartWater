#ifndef TCOMPTEUR_H_
#define TCOMPTEUR_H_

#include <string>
#include <assert.h>

#include "tParameters.h"

class tCompteur: public tParameters
    {
public:
    char aManufacturer[4]; // Fabriquant : GWF
    char aFluide[10]; //Fluide contenu : Wasser ou Gas
    char aVersNum[6]; //Version de compteur : VX.X
    char aSerialNum[10]; //Numero de serie : xxxxxxx
    char aFabDate[10]; //Date de fabrication ou calibration : xx-xx-xx
    char aNominalSize[10]; // Taille nominal : (xxxx)

    tCompteur(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    };

#endif
