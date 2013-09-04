//*****************************************************************************
//Nom du fichier : iDIO.h
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : interface mettant a disposition l'utilisation des ports en entrees/sorties digitales
//*****************************************************************************

#ifndef __IDIO__
#define __IDIO__

#include "Interface.h"
#include <msp430f5519.h>

//enumeration contenant les addresses de base de chaque port
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

//enumeration definissant la direction d'un port
typedef enum
    {
    kInput = 0,
    kOutput = 1
    } iDIOPortDirectionEnum;

//enumeration definissant l'activation ou la desactivation des resistances d'entree du port
typedef enum
    {
    kResistorDisable = 0,
    kResistorEnable = 1
    } iDIOPortResistorActivationEnum;

//enumeration definissant le type de resistance d'entree du port (soit pull-up, soit pull-down)
typedef enum
    {
    kPullDown = 0,
    kPullUp = 1
    } iDIOPortResistorPolarityEnum;

//enumeration definissant la force de la sortie
typedef enum
    {
    kReducedStrength = 0,
    kFullStrength = 1
    } iDIOPortDriveStrengthEnum;

//enumeration definissant le niveau logique d'un port
typedef enum
    {
    kHigh = 0xff,
    kLow = 0x00
    } iDIOPortOutputLevel;

class iDIO: public Interface
    {
private:
    //input
    char* thePortAddress;	//adresse de base du port
    char theMask;	//masque indiquant les bits utilises par cette interface

public:
    //constructeur
    iDIO(char* aPortAddress, char aMask);
    //nouvelles methodes
    void SetPortDirection(iDIOPortDirectionEnum aDirection);
    void SetPortResistorEnable(iDIOPortResistorActivationEnum aState);
    void SetPortResistorPolarity(iDIOPortResistorPolarityEnum aPolarity);
    void SetPortDriveStrength(iDIOPortDriveStrengthEnum aStrength);
    static void InitAllPort();

    //methodes virtuelles pures heritees devant etre definies
    bool write(UInt8 aData);
    UInt8 read();

    //destructeur
    ~iDIO();

    };

#endif
