#include <msp430.h> 

#define T2HZ 8191
#define T1HZ 16383

void io_config(void);
void ta0_config(void);
void delay(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    io_config();
    ta0_config();
    _enable_interrupt();
    while(1)
    {
        while((TA0CCTL1&CCIFG)==0);
        TA0CCTL1 &= ~CCIFG;
        P4OUT ^= BIT7;
        while((TA0CCTL2&CCIFG)==0);
        TA0CCTL2 &= ~CCIFG;
        P4OUT ^= BIT7;
    }
}



void io_config(){
    //Led Verde config
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
    //Led Vermelho config
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
}

void ta0_config(){
    TA0CTL = TASSEL__ACLK |
             MC__UP; //MODO UP
    TA0CCR1 = T2HZ;
    TA0CCTL1 = CCIE;
    TA0CCR2 = T1HZ;
    TA0CCTL2 = CCIE;
}

void delay()
{
    volatile unsigned int x = 40000;
    while (x>0){
        x--;
    }
}
