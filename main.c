#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    //Voici la modification faite sur un branche prob91 2
    //ceci est une nouvelle modification
    //Re modif sur la branche master 2
    // je modifie aussi cette ligne dans master

	return 0;
}
