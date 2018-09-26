#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCSCTL3 = LFXT1S_2; //tells MC to use internal crystal

	P1SEL &= ~0x41;//LED set 0100 0001
	P1SEL2 &= ~0x41;//LED set
	P1DIR |= 0x41; //sets direction to output

	TA0CTL = TASSEL_2 + ID_3 + MC_1; //TASSEL_2 sets it to SMCLK ID_3 sets it to 8 divider, MC_1 sets it to up, TACLR
	TA0CCR0 = 0x8000;
	TA0CCTL0 |= CCIE; //ENABLES INTERUPT

	TA1CTL = TASSEL_2 + ID_3 + MC_1; //TASSEL_2 sets it to SMCLK ID_3 sets it to 8 divider, MC_1 sets it to up, TACLR
	TA1CCR0 = 0x2000;
	TA1CCTL0 |= CCIE; //ENABLES INTERUPT
	_BIS_SR(LPM0_bits + GIE); //lower power mode and enable global interupts
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0(void) {
    //timer 0 toggle LED p1.6
    P1OUT ^= BIT6;

}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0(void) {
    //timer 1 toggle lED p1.0
    P1OUT ^= BIT0;
}
