#include <msp430.h> 

void io_config (void);
void tempo (volatile int i);

int main(void)
{
    volatile int i=10000;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	io_config();
	while (1){
	    P1OUT ^= BIT0;
	    P4OUT ^= BIT7;
	    tempo(i);
	}
}

void io_config(void) {
   P1DIR |= BIT0;
   P4DIR |= BIT7;
}

void tempo(volatile int i){
    while (i!=0){
        i--;
    }
}



