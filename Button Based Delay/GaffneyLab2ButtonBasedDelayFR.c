#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //unlocks the gpio pins

	P1DIR |= BIT0; //sets direction
	P1DIR &= ~BIT1; //sets direction to input

	P2DIR |= BIT0; //set direction to gpio
	
	P1REN |= BIT1; //enables the pull up-down resistor
	P1OUT |= BIT1; //enables pull down resistor

	P1IE |= BIT1; //enables the interupt for p1.1
	P1IES |= BIT1; //enables rising edge for p1.1
	P1IFG &= ~BIT1; //clears the flag

	TB0CTL=TBSSEL_1 + MC_1 + ID_3; //TASSEL_1 sets it to SMCLK ID_3 sets it to 8 divider, MC_1 sets it to up, TACLR
	TB0CCR0 = 200; //sets the CCR
	TB0CCTL0 |= CCIE; //ENABLES INTERUPT


	_BIS_SR(LPM0_bits + GIE);//enable global interupts and low power mode enable
	return 0;
}
#pragma vector = PORT1_VECTOR;
    __interrupt void Port_1(void)
    {
        if(P1IES & BIT1){//if falling edge is detected of button
            P1OUT &= ~BIT0;//turn of p1.0 LED
            P1IES &= ~BIT1;//sets to falling edge
            TBCTL = TBCLR;//clears the timer
            TB0CTL=TBSSEL_1 + MC_2 + ID_3; //sets clock to: A clk sets mc to: continuous mode sets ID to: 8 divider
            P2OUT |= BIT0; //sets p2out to be on

        }else{
            P2OUT &= ~BIT0;//sets p1out to be off
            TB0CTL = MC_0; //turns clock off
            TB0CCR0 = TB0R;//sets capture compare register equal to clock register
            TBCTL = TBCLR;//clears the timer
            TB0CTL=TBSSEL_1 + MC_1 + ID_3; //sets clock to: A clk sets mc to: up mode sets ID to: 8 divider
            P1IES |=BIT1; //sets to rising edge
        }
        P1IFG &= ~BIT1; //clears the flag
    }
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0(void) {
    //timer 0 toggle LED p1.6
    P1OUT ^= BIT0;//toggles P1.0 to be on or off

}
