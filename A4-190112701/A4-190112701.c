//Luiz Eduardo Alves da Costa
//190112701
#include <msp430.h>

#define CR  0xD //Carriage Return
#define LF  0xA //Line Feed

void ser_spc(void);
void ser_config(void);
void ser_crlf(void);
void ser_letra_A(void);
void ser_letra_F(void);
void io_config(void);

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	ser_config();
	io_config();
	__delay_cycles(10);

	while (1){//((P2IN&BIT1) == 0 && (P1IN&BIT1) == 0)
	    if(((P2IN&BIT1) == 0 && (P1IN&BIT1) == 0)){//S1 - Fechada S2 - Fechada
            ser_crlf();
	        ser_letra_F();
	        __delay_cycles(1000);
	        ser_spc();
	        __delay_cycles(1000);
	        ser_letra_F();
	        __delay_cycles(1000);
	        while(((P2IN&BIT1) == 0 && (P1IN&BIT1) == 0));
	    }

	    if(((P2IN&BIT1) == 0 && (P1IN&BIT1) != 0)){//S1 - Fechada S2 - Aberta
            ser_crlf();
	        ser_letra_F();
            __delay_cycles(1000);
            ser_spc();
            __delay_cycles(1000);
            ser_letra_A();
            __delay_cycles(1000);
            while(((P2IN&BIT1) == 0 && (P1IN&BIT1) != 0));
	    }

	    if(((P2IN&BIT1) != 0 && (P1IN&BIT1) == 0)){//S1 - Aberta S2 - Fechada
            ser_crlf();
	        ser_letra_A();
            __delay_cycles(1000);
            ser_spc();
            __delay_cycles(1000);
            ser_letra_F();
            __delay_cycles(1000);
            while(((P2IN&BIT1) != 0 && (P1IN&BIT1) == 0));
	    }

	    if(((P2IN&BIT1) != 0 && (P1IN&BIT1) != 0)){//S1 - Aberta S2 - Aberta
            ser_crlf();
	        ser_letra_A();
            __delay_cycles(1000);
             ser_spc();
            __delay_cycles(1000);
            ser_letra_A();
            __delay_cycles(1000);
            while(((P2IN&BIT1) != 0 && (P1IN&BIT1) != 0));
	    }

	}

}

void ser_config(){
    UCA1CTL1 =  UCSSEL_2 | UCSWRST;     //UCSI em Reset e SmCLK
    UCA1CTL0 = UCSPB;                   //2 Stops


    UCA1BRW = 54;                //Divisor por 54
    UCA1MCTL= UCBRS_5 | UCBRF_0;


    P4DIR |=  BIT4;             //P4.4 saída
    P4DIR &= ~BIT5;             //P4.5 entrada
    P4SEL |= BIT5 | BIT4;       //Tx serial

    PMAPKEYID = 0X02D52;    //Liberar mapeamentp
    P4MAP4 = PM_UCA1TXD;    //TX=Sair por P4.4
    P4MAP5 = PM_UCA1RXD;    //RX=Receber por P4.5

    UCA1CTL1 &= ~ UCSWRST;      //UCSI sai de Reset
}

void io_config(){
    //Chave S1
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
    //Chave S2
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
}


void ser_spc(void){
    UCA1TXBUF = ' ';
    while ( (UCA1IFG & UCTXIFG) == 0);
    UCA1IFG &= ~UCTXIFG;
}

void ser_letra_A(void){
    UCA1TXBUF = 'A';
    while ( (UCA1IFG & UCTXIFG) == 0);
    UCA1IFG &= ~UCTXIFG;
}

void ser_letra_F(void){
    UCA1TXBUF = 'F';
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

