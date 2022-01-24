#include <msp430.h> 


volatile int tStart;
volatile int tEnd;
volatile int tTime;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	TA0CTL = TASSEL__ACLK |
	         ID__8 |
	         MC__CONTINUOUS;
	//CAPTURA DO FLANCO DE DESCIDA
	TA0CCTL1 = CM_2 |
	           CCIS_0 |
	           SCS |
	           CAP;

    //Configuração chave S1
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;

	//CAPTURA DO FLANCO DE SUBIDA
    TA0CCTL1 = CM_1 |
               CCIS_0 |
               SCS |
               CAP;

    //Configuração chave S2
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;

    tStart=0;
    tEnd=0;
    tTime=0;
    while ((TA0CCTL1 & CCIFG) == 0);
    tStart = TA0CCR1;
    while ((TA0CCTL2 & CCIFG) == 0);
    tEnd = TA0CCR2;

    if (tEnd > tStart)
    {
        tTime = tEnd - tStart;
    }else
    {
        tTime = (tEnd - tStart) + 0xFFFF;
    }
	return 0;
}
