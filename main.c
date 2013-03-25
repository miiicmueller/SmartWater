#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // ceci est une nouvelle modification
    int a = 2 ;
    int b = 3 ;
	
	return 0;
}
