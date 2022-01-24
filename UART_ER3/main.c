#include <msp430.h> 

void uart_config(void);
void leds_config(void);
void led_vm_acesso(void);
void led_vd_acesso(void);
void led_vm_apagado(void);
void led_vd_apagado(void);
void pin_config(void);

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    pin_config();
    leds_config();
    uart_config();
    char letra_rx, letra_tx;
    letra_tx = 'A';
    while (1){
        while((UCA0IFG & UCTXIFG) == 0);
        UCA0TXBUF = letra_tx;
        while((UCA0IFG & UCRXIFG) == 0);
        letra_rx=UCA0RXBUF;
        if(letra_tx == letra_rx){//Check
            led_vd_acesso(); led_vm_apagado(); //All clear
        }
        else{//Erro
            led_vm_acesso();
            led_vd_apagado();
        }
        if(++letra_tx == 'Z'+ 1) letra_tx ='A';//Next letter

    }
}

void uart_config(){
    UCA0CTL1 = UCSWRST;//rst = 1
    UCA0CTL0 = 0;//sem paridade, 8 bits, 1 stop, modo UART
    UCA0BRW = 3;//Divisor
    UCA0MCTL = UCBRS_3; //Modulador = 3 / UCOS = 0
    UCA0CTL1 = UCSSEL_1;//rst=0 , aclk
}
void led_vm_acesso(void){   P1OUT |= BIT0;   }
void led_vd_acesso(void){   P4OUT |= BIT7;   }
void led_vm_apagado(void){  P1OUT &= ~BIT0;  }
void led_vd_apagado(void){  P4OUT &= ~BIT7;  }

// Configurar pinos P3.3 (TXD) e P3.4 (RXD)
void pin_config(void){
    P4DIR |=  BIT4;             //P4.4 saída
    P4DIR &= ~BIT5;             //P4.5 entrada
    P4SEL |= BIT5 | BIT4;       //Tx serial

    PMAPKEYID = 0X02D52;    //Liberar mapeamentp
    P4MAP4 = PM_UCA1TXD;    //TX=Sair por P4.4
    P4MAP5 = PM_UCA1RXD;    //RX=Receber por P4.5
}

void leds_config(){
    P1DIR |= BIT0;
    P4DIR |= BIT7;
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT7;
}


