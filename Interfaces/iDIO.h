//*****************************************************************************
//Nom du fichier : iDIO.h
//Auteur et Date : SAVY Cyrille 18.04.2013
//But : interface mettant � disposition l'utilisation des ports en entr�es/sorties digitales
//*****************************************************************************

#ifndef __IDIO__
#define __IDIO__

#include "Interface.h"
#include <msp430f5519.h>

//�num�r� contenant les addresses de base de chaque port
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

//�num�r� d�finissant la direction d'un port
typedef enum
    {
    kInput = 0,
    kOutput = 1
    } iDIOPortDirectionEnum;

//�num�r� d�finissant l'activation ou la d�sactivation des r�sistances d'entr�e du port
typedef enum
    {
    kResistorDisable = 0,
    kResistorEnable = 1
    } iDIOPortResistorActivationEnum;

//�num�r� d�finissant le type de r�sistance d'entr�e du port (soit pull-up, soit pull-down)
typedef enum
    {
    kPullDown = 0,
    kPullUp = 1
    } iDIOPortResistorPolarityEnum;

//�num�r� d�finissant la force de la sortie
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
    char theMask;	//masque indiquant les bits utilis�s par cette interface

public:
    //constructeur
    iDIO(char* aPortAddress, char aMask);
    //nouvelles m�thodes
    void SetPortDirection(iDIOPortDirectionEnum aDirection);
    void SetPortResistorEnable(iDIOPortResistorActivationEnum aState);
    void SetPortResistorPolarity(iDIOPortResistorPolarityEnum aPolarity);
    void SetPortDriveStrength(iDIOPortDriveStrengthEnum aStrength);
    static void InitAllPort();

    //m�thodes virtuelles pures h�rit�es devant �tre d�finies
    virtual bool write(char aData);
    virtual char read();

    //destructeur
    ~iDIO();

    };

#endif
