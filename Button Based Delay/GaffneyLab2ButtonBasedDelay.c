#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCSCTL3 = LFXT1S_2; //tells MC to use internal crystal
	
	P1DIR |= BIT0; //sets direction of p1.0 to output
	P1OUT |= BIT3; //sets p1out to be button
	P1DIR &= ~BIT3; //sets direction of P1.3 to input

	P1DIR |= BIT6;// sets as output to gpio and turns it off
    P1OUT &=~BIT6;

	P1REN |= BIT3; //enables the pull up-down resistor
	P1OUT |= BIT3; //sets the pull down resistor

	P1DIR &=~BIT3; //sets input to button

    TA0CTL=TASSEL_1 + MC_1 + ID_3; //sets clock to: A clk sets mc to: up mode sets ID to: 8 divider
    CCTL0 = CCIE; //enables interupt
    CCR0 = 200; //sets register to 250
    P1IE |= BIT3; //enables button interupt
    P1IES |=BIT3; //sets to rising edge
    P1IFG &=~BIT3; //clears interupt flag
    _BIS_SR(LPM0_bits + GIE);
	return 0;
}
#pragma vector = PORT1_VECTOR;
__interrupt void Port_1(void)
{ //BUTTON CLICK
    if(P1IES & BIT3){//if falling edge is detected of button
        P1IES &= ~BIT3;//sets to falling edge
        TACTL = TACLR;//clears the timer
        TA0CTL=TASSEL_1 + MC_2 + ID_3; //sets clock to: A clk sets mc to: continuous mode sets ID to: 8 divider
        P1OUT |= BIT6; //sets p1out to be on
    }else{
        P1OUT &= ~BIT6;//sets p1out to be off
        TA0CTL = MC_0; //turns clock off
        CCR0 = TA0R;//sets capture compare register equal to clock register
        TACTL = TACLR;//clears the timer
        TA0CTL=TASSEL_1 + MC_1 + ID_3; //sets clock to: A clk sets mc to: up mode sets ID to: 8 divider
        P1IES |=BIT3; //sets to rising edge
    }
    P1IFG &= ~BIT3; //clears flag


}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0(void) {
    //timer 0 toggle LED p1.6
    P1OUT ^= BIT0;

}
