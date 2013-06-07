#include <assert.h>
#include <msp430.h>

#include "iCpu.h"

void iCpu::setPowerMode(powerModeEnum aMode)
    {
    }

void iCpu::configFrequency()
    {
    volatile unsigned int i;

    P1DIR |= BIT1;                            // P1.1 output

    P1DIR |= BIT0;                            // ACLK set out to pins
    P1SEL |= BIT0;
    P2DIR |= BIT2;                            // SMCLK set out to pins
    P2SEL |= BIT2;
    P7DIR |= BIT7;                            // MCLK set out to pins
    P7SEL |= BIT7;

    //Selectionner la fct Xt2 sur les IOs
    P5SEL |= BIT2 + BIT3;                       // Port select XT2

    // Increase Vcore setting to level3 to support fsystem=25MHz
    // NOTE: Change core voltage one level at a time..
    SetVcoreUp(0x01);
    SetVcoreUp(0x02);
    SetVcoreUp(0x03);

    UCSCTL3 = SELREF_2;               // Set DCO FLL reference = REFO

    __bis_SR_register(SCG0);
    // Disable the FLL control loop
    UCSCTL0 = 0x0000;                 // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_7;              // Select DCO range 50MHz operation
    UCSCTL2 = FLLD_0 + 762;           // Set DCO Multiplier for 25MHz
				      // (N + 1) * FLLRef = Fdco
				      // (762 + 1) * 32768 = 25MHz
				      // Set FLL Div = fDCOCLK/2
    __bic_SR_register(SCG0);
    // Enable the FLL control loop

    // Worst-case settling time for the DCO when the DCO range bits have been
    // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
    // UG for optimization.
    // 32 x 32 x 25 MHz / 32,768 Hz ~ 780k MCLK cycles for DCO to settle
    __delay_cycles(782000);

    // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
    do
	{
	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
	// Clear XT2,XT1,DCO fault flags
	SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	}
    while (SFRIFG1 & OFIFG);                   // Test oscillator fault flag

    UCSCTL5 = 0x0000;	//all dividers divide by 1
    UCSCTL6 = XT2DRIVE_1 | XT2BYPASS | XT1OFF;//activation de xt2 et d�sactivation de xt1
    UCSCTL4 = SELA_2 | SELS_5 | SELM_3;	// Set ACLK = REFO
					// Set SMCLK = XT2CLK
					// Set MCLK = DCOCLK

    while (1)
	{
	P1OUT ^= BIT1;                          // Toggle P1.1
	__delay_cycles(600000);                 // Delay
	}
    }

void iCpu::SetVcoreUp(unsigned int level)
    {
    // Open PMM registers for write
    PMMCTL0_H = PMMPW_H;
    // Set SVS/SVM high side new level
    SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
    // Set SVM low side to new level
    SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
    // Wait till SVM is settled
    while ((PMMIFG & SVSMLDLYIFG)== 0);
    // Clear already set flags
    PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
    // Set VCore to new level
    PMMCTL0_L = PMMCOREV0 * level;
    // Wait till new level reached
    if ((PMMIFG & SVMLIFG))
	while ((PMMIFG & SVMLVLRIFG)== 0);
    // Set SVS/SVM low side to new level
    SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
    // Lock PMM registers for write access
    PMMCTL0_H = 0x00;
    }
