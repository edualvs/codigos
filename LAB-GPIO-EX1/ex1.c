#include <msp430.h> 

void io_config(void);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	io_config();
	while (1){
	    if ((P2IN & BIT1) == 0){
	        P4OUT |= BIT7;
	    }
	    else
	        P4OUT &= ~BIT7;
	}
}

void io_config(void){
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
}
