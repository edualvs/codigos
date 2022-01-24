#include <msp430.h> 

#define dbc 30000
void debounce (int val);
void io_config(void);
void leds (int ct);

int main(void)
{
    int cont = 0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	io_config();
	
	while(1){
	    while ((P2IN & BIT1) == BIT1);
	    cont++;
	    leds(cont);
	    debounce(dbc);
	    while ((P2IN & BIT1) == 0);
	}


}

void io_config(void){
    P2DIR &= (~BIT1);
    P2REN |= BIT1;
    P2OUT |= BIT1;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}

void leds (int ct){
    switch (ct&3){
    case 0: P1OUT &= ~BIT0;  P4OUT &= ~BIT7; break;
    case 1: P1OUT &= ~BIT0;  P4OUT |= BIT7; break;
    case 2: P1OUT |= BIT0;  P4OUT &= ~BIT7; break;
    case 3: P1OUT |= BIT0; P4OUT |= BIT7; break;
    }
}

void debounce (int val){
    volatile int x;
    for (x=0;x<val;x++);
}


