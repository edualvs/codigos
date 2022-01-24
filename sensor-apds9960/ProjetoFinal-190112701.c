//Luiz Eduardo Alves da Costa
//Matrícula: 190112701

#include <msp430.h> 

#define TRUE    1
#define FALSE   0

#define BR_100K    11  //SMCLK/100K = 11
#define PCF_ADR1 0x3F //Possíveis endereços do lcd
#define PCF_ADR2 0x27 //Possíveis endereços do lcd

#define PCF_ADR  PCF_ADR2 //Endereço do lcd usado

#define APDS9960_ENABLE         0x80
#define APDS9960_I2C_ADDR       0x39

/* Bit fields */
#define APDS9960_PON            0b00000001
#define APDS9960_AEN            0b00000010
#define APDS9960_PEN            0b00000100
#define APDS9960_WEN            0b00001000
#define APSD9960_AIEN           0b00010000
#define APDS9960_PIEN           0b00100000
#define APDS9960_GEN            0b01000000
#define APDS9960_GVALID         0b00000001


void i2c_write_lcd(char dado);
void i2c_write_apds(char addr_reg, char dado);
int i2c_read_apds(void);
void i2c_config(void);

volatile char l_clear,h_clear,l_red,h_red,l_green,h_green,l_blue,h_blue;
int i;
volatile int leitura;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	i2c_config();
	P1DIR |=  BIT2 | BIT3 | BIT4;//Configura Módulo Led RGB

    i2c_write_apds(APDS9960_ENABLE,65);
    //i2c_write_apds(0x9C,0);
    leitura = i2c_read_apds();

    while(1);


}


// Função para enviar um  byte para o Sensor
void i2c_write_apds(char addr_reg, char dado) {
    UCB0I2CSA = APDS9960_I2C_ADDR;        // (0x39)Endereço Escravo APDS
    UCB0CTL1 |= UCTR    |       //Mestre TX
                UCTXSTT;        //Gerar START

    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = addr_reg;                               //Escrever endereço registrador
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);       //Esperar STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG)        //NACK?
                while(1);                           //Escravo gerou NACK

    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = dado;                               //Escrever endereço registrador
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);       //Esperar STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG)        //NACK?
                while(1);                           //Escravo gerou NACK
    UCB0CTL1 |= UCTXSTP;                            //Gerar STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);       //Esperar STOP
}

// Ler a porta do sensor
int i2c_read_apds(void){
    int dado;
    UCB0I2CSA = APDS9960_I2C_ADDR;      //Endereço Escravo
    UCB0CTL1 &= ~UCTR;                  //Mestre RX
    UCB0CTL1 |= UCTXSTT;                //Gerar START
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);
    UCB0CTL1 |= UCTXSTP;                //Gerar STOP + NACK
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP)   ;   //Esperar STOP
    while ( (UCB0IFG & UCRXIFG) == 0);  //Esperar RX
    dado=UCB0RXBUF;
    return dado;
}

// Função para enviar um  byte para o PCF8574
// Você já deve ter esta função pronta
// Se necessário, seu nome pode ser alterado
void i2c_write_lcd(char dado) {
    UCB0I2CSA = PCF_ADR;        //Endereço Escravo LCD
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
void i2c_config(void){
    UCB0CTL1 |= UCSWRST;    // UCSI B0 em ressete
    UCB0CTL0 = UCSYNC |     //Síncrono
               UCMODE_3 |   //Modo I2C
               UCMST;       //Mestre
    UCB0BRW = BR_100K;      //100 kbps
    P3SEL |=  BIT1 | BIT0;  // Use dedicated module
    UCB0CTL1 = UCSSEL_2;    //SMCLK e remove ressete
}
