#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    //ceci est une nouvelle modification
    //Re modif sur la branche master
	return 0;
}
