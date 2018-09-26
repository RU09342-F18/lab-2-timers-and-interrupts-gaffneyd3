#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //unlocks the gpio pins

	P1DIR |= BIT0; //sets direction to output
	P1DIR &= ~BIT1; //sets direction to input

	P1REN |= BIT1; //enables the pull up-down resistor
	P1OUT |= BIT1; //enables pull down resistor
	
	P1IE |= BIT1; //enables the interupt for p1.0
	P1IES &= ~BIT1; //enables rising edge for p1.0
	P1IFG &= ~BIT1; //clears the flag
	_BIS_SR(LPM0_bits + GIE);
	return 0;
}
#pragma vector = PORT1_VECTOR;
    __interrupt void Port_1(void)
    {
        P1OUT ^= BIT0; //toggles LED
        P1IFG &= ~BIT1; //clears flag
    }
