#ifndef TCOMPTEUR_H_
#define TCOMPTEUR_H_

#include <string>
#include <assert.h>

#include "tParameters.h"

#define kSizeManufacturer	4
#define kSizeFluide		10
#define kSizeVersNum		6
#define kSizeSerialNum		10
#define kSizeFabDate		10
#define kSizeNominalSize	10
#define kSizeSerializerCompteur 50

class tCompteur: public tParameters
    {
public:
    char aManufacturer[kSizeManufacturer]; // Fabriquant : GWF
    char aFluide[kSizeFluide]; //Fluide contenu : Wasser ou Gas
    char aVersNum[kSizeVersNum]; //Version de compteur : VX.X
    char aSerialNum[kSizeSerialNum]; //Numero de serie : xxxxxxx
    char aFabDate[kSizeFabDate]; //Date de fabrication ou calibration : xx-xx-xx
    char aNominalSize[kSizeNominalSize]; // Taille nominal : (xxxx)

    tCompteur(mEEPROM *mEeprom, UInt16 aModeNum);
    void save();
    void load();

    };

#endif
