#include <msp430.h> 

#define F2Hz  8192 //2hz com ACLK
#define F3Hz  5461 //3hz com ACLK

void io_config(void);
void ta0_config (void);


unsigned int dseg,seg,min,hora;
int cont=0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    io_config();
    ta0_config();
    dseg=seg=min=hora=0;
    __enable_interrupt();
    while(1);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer_a0()
{
  if ((TA0CCR1 == TA0R))


}
void io_config(){
    //Led Vermelho config
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    //Led Verde config
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}

void ta0_config(){
    TA0CTL = TASSEL_1 | MC_2;//ACLK = 32.768 Hz - Modo 2 = continuous mode
    TA0CCTL1 = CCIE; //Hab int TA0CCTL1.CCIFG
    TA0CCTL2 = CCIE; //Hab int TA0CCTL2.CCIFG
    TA0CCR1 = F2Hz;
    TA0CCR2 = F3Hz;
    TA0CCTL0 = CCIE;//Habilitar interrupção CCIFG
}
