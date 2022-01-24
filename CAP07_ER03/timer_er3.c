#include <msp430.h> 

#define T50ms  52428 //50ms com ACLK

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
    cont++;
    if ((cont&BIT0)==0){
        P4OUT ^= BIT7;
    }
    if(++dseg==20){
        dseg=0;
        P1OUT ^= BIT0;
        if(++seg==120){
            seg=0;
            if (++min == 120){
                min = 0;
                if (++hora == 48){
                    hora = 0;
                }
            }
        }
    }

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
    TA0CTL = TASSEL_2 | MC_1;//ACLK = 32.768 Hz - Modo 1 = up
    TA0CCR0 = T50ms;
    TA0CCTL0 = CCIE;//Habilitar interrupção CCIFG
}
