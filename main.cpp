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

    iUart.sendString("Hello World !");
    while (1)
	{
	// Un caractère à été recu
	if (iUart.isBufferEmpty() == false)
	    {
	    //On le renvoie
	    iUart.write(iUart.read());
	    }
	}
    return 0;

    }

/*
 * ======== Init_Clock ========
 */
void Init_Clock(void)
    {

    //Configuration de la fr�quence
    //Selectionner la fct Xt2 sur les IOs
    P5SEL |= (0x04);
    P5SEL |= (0x04);
    //Utilisation de SMCLK
    UCSCTL6 = 0x00; // Pas de drive trop fort
    UCSCTL6 &= ~XT2BYPASS; // Pas de bypass, mais crystal

    //Activer XT2CLK sur SMCLK
    UCSCTL4 |= (SELS0 | SELS2);
    UCSCTL5 &= 0xFE3F; // Division par 1

    do
	{
	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
	// Clear XT2,XT1,DCO fault flags
	SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	}
    while (UCSCTL7 & XT2OFFG != 0x00);             // Test oscillator fault flag

    }

