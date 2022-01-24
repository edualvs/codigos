#include <msp430.h> 

#define T100ms  3276 //100ms com ACLK

void io_config(void);
void ta0_config (void);

int main(void)
{
    unsigned int dseg,seg,min,hora;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	io_config();
	ta0_config();
	dseg=seg=min=hora=0;
	while(1){
	    while ((TA0CTL&TAIFG)==0); //Esperar TAIFG=1
        TA0CTL &= ~TAIFG; // TAIFG=0
        P4OUT ^= BIT7;
        if(++dseg==10){
            dseg=0;
            P1OUT ^= BIT0;
            if(++seg==60){
                seg=0;
                if (++min == 60){
                    min = 0;
                    if (++hora == 24){
                        hora = 0;
                    }
                }
            }
        }
    }
	return 0;
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
    TA0CTL = TASSEL_1 | MC_1;//ACLK = 32.768 Hz - Modo 1 = up
    TA0CCR0 = T100ms;
}
