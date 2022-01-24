#include <msp430.h> 

#define T50ms  1637 //50ms com ACLK
#define TRUE 1

void leds_config(void);
void ta0_config(void);

int main(void)
{
    int cont=0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	leds_config();
	ta0_config();
	while (TRUE){
	    while ((TA0CTL&TAIFG)==0); //Esperar TAIFG=1
	    TA0CTL &= ~TAIFG; // TAIFG=0
	    P1OUT ^= BIT0;
	    cont++;
	    if ((cont&BIT0)==0){
	        P4OUT ^= BIT7;
	    }
	}
}


void leds_config(){
    P1DIR |= BIT0; //LED VERMELHO = P1.0 = SAÍDA
    P1OUT &= ~BIT0;//LED VERMELHO DESLIGADO
    P4DIR |= BIT7;//LED VERDE = P1.0 = SAÍDA
    P4OUT &= ~BIT7;//LED VERDE DESLIGADO
}

void ta0_config(){
    TA0CTL = TASSEL_1 | //ACLK = 32.768 Hz
                MC_1; //Modo 1 = up
    TA0CCR0 = T50ms; //Zerar a cada 1638 contagens
}
