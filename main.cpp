#include <msp430.h>
#include "Modules/mGSM.h"
#include "Interfaces/iDIO.h"
#include "Interfaces/iUART.h"
#include "Tools/tCommandesAT.h"

/*
 * main.c
 */
int _system_pre_init(void) {
	// turn watchdog off
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	_DINT();

	return (1);
}

//Function declarations
void Init_Clock(void);

int main(void) {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	Init_Clock();

	__bis_SR_register(GIE);

	//TODO Rajouter l'initialisation iCpu

	//Declaration d'un iUart
	iUART iUart(kUSCI_A0, kLSBFirst, k2StBits, kNone, k8bits, 115200);
	iDIO iDio(0x00, 0x00);
	tCommandesAT tComAt;

	iUart.enable();

	mGSM mGsm(&iDio, &iUart, &tComAt);
	mGsm.mSetup();
	mGsm.mOpen();

	mGsm.sendSMS("Bonjour de l'it�ration (Genie Log.) IIEs test� en transmission !!", "+41767782399");

	while (1) {

		unsigned int i = 65535;

		//	iUart.write('A');

		while (i-- > 0)
			;
	}

}

/*
 * ======== Init_Clock ========
 */
void Init_Clock(void) {

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
	do {
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
		// Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	} while (SFRIFG1 & OFIFG);                   // Test oscillator fault flag

	UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
	// expected frequency
	UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2

}

