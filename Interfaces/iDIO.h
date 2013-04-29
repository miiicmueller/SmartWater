//*****************************************************************************
//Nom du fichier : iDIO.h
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : interface mettant à disposition l'utilisation des ports en entrées/sorties digitales
//*****************************************************************************

#ifndef __IDIO__
#define __IDIO__

#include "Interface.h"
#include <msp430f5519.h>

//énuméré contenant les addresses de base de chaque port
typedef enum
    {
    kPort_1 = __MSP430_BASEADDRESS_PORT1_R__,
    kPort_2 = __MSP430_BASEADDRESS_PORT2_R__ + 1,
    kPort_3 = __MSP430_BASEADDRESS_PORT3_R__,
    kPort_4 = __MSP430_BASEADDRESS_PORT4_R__ + 1,
    kPort_5 = __MSP430_BASEADDRESS_PORT5_R__,
    kPort_6 = __MSP430_BASEADDRESS_PORT6_R__ + 1,
    kPort_7 = __MSP430_BASEADDRESS_PORT7_R__,
    kPort_8 = __MSP430_BASEADDRESS_PORT8_R__ + 1
    } iDIOPortAddressEnum;

//énuméré définissant la direction d'un port
typedef enum
    {
    kInput = 0,
    kOutput = 1
    } iDIOPortDirectionEnum;

//énuméré définissant l'activation ou la désactivation des résistances d'entrée du port
typedef enum
    {
    kResistorDisable = 0,
    kResistorEnable = 1
    } iDIOPortResistorActivationEnum;

//énuméré définissant le type de résistance d'entrée du port (soit pull-up, soit pull-down)
typedef enum
    {
    kPullDown = 0,
    kPullUp = 1
    } iDIOPortResistorPolarityEnum;

//énuméré définissant la force de la sortie
typedef enum
    {
    kReducedStrength = 0,
    kFullStrength = 1
    } iDIOPortDriveStrengthEnum;

class iDIO: public Interface
    {
private:
    //input
    char* thePortAddress;	//adresse de base du port
    char theMask;	//masque indiquant les bits utilisés par cette interface

public:
    //constructeur
    iDIO(char* aPortAddress, char aMask);

    //nouvelles méthodes
    void SetPortDirection(iDIOPortDirectionEnum aDirection);
    void SetPortResistorEnable(iDIOPortResistorActivationEnum aState);
    void SetPortResistorPolarity(iDIOPortResistorPolarityEnum aPolarity);
    void SetPortDriveStrength(iDIOPortDriveStrengthEnum aStrength);

    //méthodes virtuelles pures héritées devant être définies
    virtual bool write(char aData);
    virtual char read();

    //destructeur
    ~iDIO();

    };

#endif
