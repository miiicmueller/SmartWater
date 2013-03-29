#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    //Voici la modification faite sur un branche prob91
    //ceci est une nouvelle modification
	return 0;
}
