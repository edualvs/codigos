#include <msp430.h> 

#define T1HZ 16383

void io_config(void);
void ta0_config(void);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	io_config();
    ta0_config();

    while(1){
        while ((TA0CTL&TAIFG)==0); //Esperar TAIFG=1
        TA0CTL &= ~TAIFG; // TAIFG=0
        P4OUT ^= BIT7;
        }
    }



void io_config(){
    //Led Verde config
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}

void ta0_config(){
    TA0CTL = TASSEL_1 |//ACLK
            MC_1; //MODO UP
    TA0CCR0 = T1HZ;
}
