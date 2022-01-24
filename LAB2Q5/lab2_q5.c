#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	_enable_interrupt();

	//Led Vermelho apagado
	P1SEL &= ~BIT0;
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

    //Configuração chave S1
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
    P2IE |= BIT1;
    P2IES |= BIT1;

	while (1);


}

#pragma vector=42
__interrupt void myInterrupt() {
 switch (P2IV) { // A leitura de P1IV limpa a P1IFG correspondente

 case 0x4: // P1.1
     P1OUT ^= BIT0; // Faz o LED vermelho alternar de estado
     break;

 default:
     break;
   }
}
