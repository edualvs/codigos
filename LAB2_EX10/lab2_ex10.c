#include <msp430.h> 

#define T1HZ 16383

void io_config(void);
void ta0_config(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    io_config();
    ta0_config();
    __enable_interrupt();
    while(1);
    }

#pragma vector = 53
__interrupt void ta0_ccifg0(void){
    P4OUT ^= BIT7;
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
    TA0CCTL0 = CCIE;

}
