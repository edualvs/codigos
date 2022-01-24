#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//Porta config P2.5
	P2SEL &= ~BIT5;
	P2DIR |= BIT5;
	P2OUT &= ~BIT5;

	//Config Timer A0
	TA0CTL |= TACLR;
	TA0CTL |= MC__UP;
	TA0CTL |= TASSEL__SMCLK;
	TA0CCR0 = 1048;
	TA0CTL &= ~TAIFG; // Limpar a flag

	while (1){
	    if (TA0CTL&TAIFG){
	        TA0CTL &= ~TAIFG;
	        P2OUT ^= BIT5;
	    }

	}

	return 0;
}
