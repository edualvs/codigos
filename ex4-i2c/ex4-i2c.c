#include <msp430.h> 

void config_USCI_B0(void);
void leds_config(void);
void teste_nack(void);

#define BR10K 105 //com SMCLK

int main(void)
{
    int i=0;
    volatile char vetor[10];
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	config_USCI_B0();
	USCI_B1_config();
	leds_config();

	UCB0I2CSA = 42;//Slave address

	UCB0CTL1 |= UCTXSTT;//START = 1 E MESTRE TRANSMISSOr
	
	 while ((UCB0CTL1 & UCTXSTT) == UCTXSTT);//Esperar UCTXSTT = 0
	 teste_nack();

	 while (i<9){
	     while((UCB0IFG & UCRXIFG) == 0);//Esperar RXIFG = 1
	     vetor[i++]=UCB0RXBUF;
	 }

	 UCB0CTL1 |= UCTXSTP;
	 while( (UCB0CTL1 & UCTXSTP) == UCTXSTP);//ESPERAR STOP = 0
	 while((UCB0IFG & UCRXIFG) == 0);//Esperar RXIFG = 1
	 vetor[i]=UCB0RXBUF;
	 P4OUT |= BIT7;
	 while(1);
	return 0;
}
void config_USCI_B0(void){
    UCB0CTL1 = UCSWRST; //Ressetar USCI_B1

    UCB0CTL0 = UCSYNC | UCMODE_3 | UCMST; // Síncrono, mestre, i2c
    UCB0BRW = BR10K; //10 kbps

    UCB0CTL1 = UCSSEL_3; //SMCLK e UCSWRST=0
    P3SEL |= BIT1 | BIT0; //Funções alternativas
    P3REN |= BIT1 | BIT0;
    P3OUT |= BIT1 | BIT0;
}

void teste_nack(){
    if ((UCB0IFG & UCNACKIFG) == UCNACKIFG){
     P1OUT |= BIT0; //Vermelho=falha
     UCB0CTL1 |= UCTXSTP; //Gerar STOP
     while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP); //Esperar STOP
     while(1); //Travar
     }
}

void leds_config(){
    P1DIR |= BIT0; P1OUT &= ~BIT0;
    P4DIR |= BIT7; P4OUT &= ~BIT7;
}
