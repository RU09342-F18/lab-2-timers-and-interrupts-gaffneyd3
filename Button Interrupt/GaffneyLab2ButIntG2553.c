#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1SEL &= ~0x09; //selects GPIO and LED
	P1SEL2 &= ~0x09; //selects GPIO and LED

	P1DIR |= BIT0; //sets direction of p1.0 to output
	P1DIR &= ~BIT3; //sets direction of P1.3 to input
	P1REN |= BIT3; //enables the pull up-down resistor
	P1OUT |= BIT3; //sets the pull down resistor

	P1IE |= BIT3; //enables the interupt for p1.3
	P1IES &= ~BIT3; //enables rising edge for p1.3
	P1IFG &= ~BIT3; //clears the flag

	// Enter LPM0 and enable global interrupts
	_BIS_SR(LPM0_bits + GIE);
	return 0;
}
    #pragma vector = PORT1_VECTOR;
    __interrupt void Port_1(void)
    {
        P1OUT ^= BIT0; //toggles LED
        P1IFG &= ~BIT3; //clears flag
    }
