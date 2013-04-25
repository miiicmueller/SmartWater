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

    __bis_SR_register(GIE);

    //Declaration d'un iUart
    iUART iUart(kUSCI_A0, kLSBFirst, k1StBits, kNone, k8bits, 9600);

    //Activation de l'uart
    iUart.enable();

    iUart.sendString("Hello World !");

    // For debugger

    while (1)
	{
	if(iUart.availableCharToRead()>10)
	    {
	    char salut[200];
	    iUart.readFullBuffer(salut);
	    iUart.sendString(salut);
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
    P5SEL |= BIT2 + BIT3;                       // Port select XT2

    UCSCTL6 &= ~XT2OFF;                       // Enable XT2
    UCSCTL3 |= SELREF_2;                      // FLLref = REFO
					      // Since LFXT1 is not used,
					      // sourcing FLL with LFXT1 can cause
					      // XT1OFFG flag to set
    UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO

    // Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
    do
	{
	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
	// Clear XT2,XT1,DCO fault flags
	SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	}
    while (SFRIFG1 & OFIFG);                   // Test oscillator fault flag

    UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
					      // expected frequency
    UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2

    }



