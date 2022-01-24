#include <msp430.h> 

#define BR_100K    11  //SMCLK/100K = 11

void i2c_write_apds(char dado);
void i2c_config_apds(void);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	i2c_config_apds();
	i2c_write_apds(5);

	while(1);
	return 0;
}

// Função para enviar um  byte para o Sensor
// Você já deve ter esta função pronta
// Se necessário, seu nome pode ser alterado
void i2c_write_apds(char dado) {
    UCB0I2CSA = 0x39;        // (0x39)Endereço Escravo APDS
    UCB0CTL1 |= UCTR    |       //Mestre TX
                UCTXSTT;        //Gerar START
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = dado;                               //Escrever dado
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);       //Esperar STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG)        //NACK?
                while(1);                           //Escravo gerou NACK
    UCB0CTL1 |= UCTXSTP;                            //Gerar STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);       //Esperar STOP
}


// Configurar i2c
void i2c_config_apds(void){
    UCB1CTL1 |= UCSWRST;    // UCSI B0 em ressete
    UCB1CTL0 = UCSYNC |     //Síncrono
               UCMODE_3 |   //Modo I2C
               UCMST;       //Mestre
    UCB1BRW = BR_100K;      //100 kbps
    P4SEL |=  BIT2 | BIT1;  // Use dedicated module
    UCB1CTL1 = UCSSEL_2;    //SMCLK e remove ressete
}
