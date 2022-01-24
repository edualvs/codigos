#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//Configuração chave S1
	   P2DIR &= ~BIT1;
	   P2REN |= BIT1;
	   P2OUT |= BIT1;
	   P2IE |= BIT1;
	   P2IES &= ~BIT1;

    //Configuração chave S2
	   P1DIR &= ~BIT1;
	   P1REN |= BIT1;
	   P1OUT |= BIT1;
	   P1IE |= BIT1;
	   P1IES &= ~BIT1;

    //Led Vermelho apagado
	   P1SEL &= ~BIT0;
	   P1DIR |= BIT0;
	   P1OUT &= ~BIT0;

    //Led Verde apagado
	   P4SEL &= ~BIT7;
	   P4DIR |= BIT7;
	   P4OUT &= ~BIT7;

	   int cont1=0;
	   int cont2=0;
	_enable_interrupt();
	while (1)
	{
	    if (P1IFG != 0)
	    {
	        cont1--;
	        switch
	    }

	    if (P2IFG != 0)
	    {
	        cont2++;
	    }
	}
	return 0;
}
