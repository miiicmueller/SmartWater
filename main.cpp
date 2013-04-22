#include <msp430.h> 
#include "Interfaces/iUART.h"

//Function declarations
void Init_Clock(void);

/*
 * main.c
 */
int main(void)
    {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    Init_Clock();
    //TODO Rajouter l'initialisation iCpu

    //Declaration d'un iUart
    iUART iUart(kUSCI_A0, kLSBFirst, k2StBits, kNone, k8bits, 9600);

    //Activation de l'uart
    iUart.enable();

    while (1)
	{
	//Envoie d'un truc
	iUart.write('S');
	}
    return 0;

    }

/*
 * ======== Init_Clock ========
 */
void Init_Clock(void)
    {

    //Configuration de la fréquence
    //Utilisation de SMCLK
    //Activer XT2CLK sur SMCLK
    UCSCTL4 |= (SELS0 | SELS2);
    UCSCTL5 &= 0xFE3F; // Division par 1
    UCSCTL6 = 0x00; // Pas de drive trop fort
    UCSCTL6 &= ~XT2BYPASS; // Pas de bypass, mais crystal


    UCSCTL7 &= XT2OFFG ;

    }

