//Luiz Eduardo Alves da Costa
//190112701

#include <msp430.h> 

#define CR  0xD //Carriage Return
#define LF  0xA //Line Feed

//Protótipos da funções
void ser_spc(void);
void ser_crlf(void);
void ser_nibble(volatile char nibble);
void adc_config(void);
void ta0_config(void);
void uart_config(void);

//Variáveis globais
volatile char media_x, media_y;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	adc_config();
	ta0_config();
	uart_config();

	__enable_interrupt();
	while(1){
	    ADC12CTL0 |= ADC12SC;//Disparar conversão
	    ADC12CTL0 &= ~ADC12SC;//Zerar
	    ser_nibble(media_x >> 8);
        ser_spc();
        ser_nibble(media_y >> 8);
        ser_crlf();
	}
}

//#pragma vector = 54
#pragma vector = ADC12_VECTOR
__interrupt void adc_int(void){
     volatile unsigned int *pt;
     unsigned int i,soma;
     pt = &ADC12MEM0;

     soma = 0;
     for (i=0; i<4; i++) soma +=pt[i];
     media_x = soma >> 2;

     soma = 0;
     for (i=4; i<8; i++) soma +=pt[i];
     media_y = soma >>2;
}

void adc_config(void){
    volatile unsigned char *pt;
    unsigned char i;
    ADC12CTL0 &= ~ADC12ENC;//Desabilita a conversão do ADC

    ADC12CTL0 |= ADC12ON;//Liga o ADC

    ADC12CTL1 = ADC12CONSEQ_3 | //Seq. Canal repetido
                 ADC12DIV_0 | //Dividir por 1
                 ADC12SHS_1 | //TA0.1
                 ADC12CSTARTADD_0 | //MEM0
                 ADC12SSEL_3; //SMCLK

    ADC12CTL2 = ADC12RES_2; //12 bits

    pt=&ADC12MCTL0;
    for (i=0; i<4; i++)
    pt[i]=ADC12SREF_0 | ADC12INCH_1; //ADC12MCTL0 até ADC12MCTL3
    for (i=4; i<8; i++)
    pt[i]=ADC12SREF_0 | ADC12INCH_2; //ADC12MCTL4 até ADC12MCTL7
    pt[8] |= ADC12EOS; //EOS em ADC12MCTL8

    P6SEL |= (BIT2|BIT3); //Desligar digital de P6.2, P6.3

    ADC12CTL0 |= ADC12ENC;//Liga a conversão AD

    ADC12IE |= ADC12IE8;
}

void uart_config(void){
    UCA0CTL1 = UCSWRST; //RST=1 para USCI_A0
    UCA0CTL0 = UCSPB; //No parid., 8 bits, 2 stop, UART
    UCA0BRW = 54; //Divisor
    UCA0MCTL = UCBRS_5;
    P3SEL |= BIT4 | BIT3; //Disponib. TXD e RXD
    UCA0CTL1 = UCSSEL_2; //RST=0, SMCLK
}

void ta0_config(void){
     TA0CTL = TASSEL_1 | MC_1;
     TA0CCTL1 = OUTMOD_6; //Out = modo 6
     TA0CCR0 = 32767/32; //64 Hz (32 Hz por canal)
     TA0CCR1 = TA0CCR0/2; //Carga 50%
     P1DIR |= BIT2;
     P1SEL|= BIT2;
}

void ser_spc(void){
    UCA1TXBUF = ' ';
    while ( (UCA1IFG & UCTXIFG) == 0);
    UCA1IFG &= ~UCTXIFG;
}

void ser_crlf(void){//Pula linha
    UCA1TXBUF = CR;
    while ( (UCA1IFG & UCTXIFG) == 0);
    UCA1IFG &= ~UCTXIFG;
    UCA1TXBUF = LF;
    while ( (UCA1IFG & UCTXIFG) == 0);
    UCA1IFG &= ~UCTXIFG;
}

void ser_nibble(volatile char nibble){
    UCA1TXBUF = nibble;
    while ( (UCA1IFG & UCTXIFG) == 0);
    UCA1IFG &= ~UCTXIFG;
}
