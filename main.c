#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // Voila une nouvelle modification

    // Voila une nouvelle modification2

    // Voila une nouvelle modification3

    //dans le prochain commit je modifie ca

	return 0;
}
