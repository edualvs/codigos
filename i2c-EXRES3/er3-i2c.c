#include <msp430.h>
#include <USCI_B1.h>

void config_USCI_B0(void);
void leds_config(void);
void teste_nack(void);

# define BR10K 105 //com SMCLK

void main(void)
{
    char n = 0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	USCI_B1_config(); //USCI_B1 como mestre
	config_USCI_B0(); //USCI_B1 como mestre
	leds_config();

	UCB0I2CSA = 42;//Endereço escravo
	UCB0CTL1 |= UCTR | UCTXSTT;//START = 1 E MESTRE TRANSMISSOr

    while((UCB0IFG & UCTXIFG) == 0);//Esperar UCTXIFG = 1
    UCB0TXBUF = n++;//Dado = n
    while ((UCB0CTL1 & UCTXSTT) == UCTXSTT);//Esperar UCTXSTT = 0
    teste_nack();

	while (n<10){
	    while((UCB0IFG & UCTXIFG) == 0);//Esperar UCTXIFG = 1
        UCB0TXBUF = n++;//Dado = n
        teste_nack();
	}

	while((UCB0IFG & UCTXIFG) == 0);//Esperar TXIFG = 1

	UCB0CTL1 |= UCTXSTP;//STOP = 1
	while( (UCB0CTL1 & UCTXSTP) == UCTXSTP);//ESPERAR STOP = 0

	P4OUT |= BIT7;//ACENDO LED VERDE
    while(1);

}

void config_USCI_B0(void){
    UCB0CTL1 = UCSWRST; //Ressetar USCI_B1
     UCB0CTL0 = UCMST | //Modo Mestre
     UCMODE_3 | //I2C
     UCSYNC; //Síncrono
     UCB0BRW = BR10K; //10 kbps
     UCB0CTL1 = UCSSEL_3; //SMCLK e UCSWRST=0
     P3SEL |= BIT1 | BIT0; //Funções alternativas
     P3REN |= BIT1 | BIT0;
     P3OUT |= BIT1 | BIT0;
}

void leds_config(){
    P1DIR |= BIT0; P1OUT &= ~BIT0;
     P4DIR |= BIT7; P4OUT &= ~BIT7;

}

void teste_nack(){
    if ((UCB0IFG & UCNACKIFG) == UCNACKIFG){
     P1OUT |= BIT0; //Vermelho=falha
     UCB0CTL1 |= UCTXSTP; //Gerar STOP
     while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP); //Esperar STOP
     while(1); //Travar
     }
}
