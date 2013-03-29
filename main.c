#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // Voila une nouvelle modification

    //dans le prochain commit je modifie ca

	return 0;
}
