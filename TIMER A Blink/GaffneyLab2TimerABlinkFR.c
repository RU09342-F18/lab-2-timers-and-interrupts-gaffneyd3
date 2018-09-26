#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//BCSCTL3 = LFXT1S_2; //tells MC to use internal crystal
	PM5CTL0 &= ~LOCKLPM5; //unlocks the gpio pins
	P1DIR |= BIT0; //sets direction
	P2DIR |= BIT0;

	//TIMER B MODULE
    TB0CTL = TBSSEL_2 + ID_3 + MC_1; //TASSEL_2 sets it to SMCLK ID_3 sets it to 8 divider, MC_1 sets it to up, TACLR
    TB0CCR0 = 0x8000; //blinks 4 times a second
    TB0CCTL0 |= CCIE; //ENABLES INTERUPT

    TB1CTL = TBSSEL_2 + ID_3 + MC_1; //TASSEL_2 sets it to SMCLK ID_3 sets it to 8 divider, MC_1 sets it to up, TACLR
    TB1CCR0 = 0x2000; //blinks
    TB1CCTL0 |= CCIE; //ENABLES INTERUPT
    _BIS_SR(LPM0_bits + GIE); //lower power mode and enable global interupts
	return 0;
}
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0(void) {
    //timer 0 toggle LED p1.6
    P1OUT ^= BIT0;

}
#pragma vector=TIMER1_B0_VECTOR
__interrupt void TIMER1_B0(void) {
    //timer 1 toggle lED p1.0
    P2OUT ^= BIT0;
}
