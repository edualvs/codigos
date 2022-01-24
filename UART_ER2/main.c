#include <msp430.h> 

#define CR  0xD //Carriage Return
#define LF  0xA //Line Feed

void uart_config(void);
void leds_config(void);
void led_vm_acesso(void);
void led_vd_acesso(void);
void led_vm_apagado(void);
void led_vd_apagado(void);

volatile char letra_rx, letra_tx;
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    leds_config();
    uart_config();

    __enable_interrupt();
    while (1){
        if(letra_tx == letra_rx){//Check
            led_vd_acesso(); led_vm_apagado(); //All clear
        }
        else{//Erro
            led_vm_acesso();
            led_vd_apagado();
        }
    }
}
#pragma vector = USCI_A0_VECTOR
__interrupt void usci_interrupt(){
    letra_tx = 'A';
    switch(UCA0IV){
        case 2:
            letra_rx=UCA0RXBUF;
        case 4:
            UCA0TXBUF = letra_tx;
            if(++letra_tx == 'Z'+ 1) letra_tx ='A';//Next letter
    }
    UCA0IV;
}

void uart_config(){
    UCA0CTL1 = UCSWRST;//rst = 1
    UCA0CTL0 = 0;//sem paridade, 8 bits, 1 stop, modo UART
    UCA0BRW = 3;//Divisor
    UCA0MCTL = UCBRS_3; //Modulador = 3 / UCOS = 0
    UCA0STAT =  UCLISTEN;//Loop Back
    UCA0CTL1 = UCSSEL_1;//rst=0 , aclk
    UCA0IE = UCRXIE; //Hab. Interrup recepção
}
void led_vm_acesso(void){   P1OUT |= BIT0;   }
void led_vd_acesso(void){   P4OUT |= BIT7;   }
void led_vm_apagado(void){  P1OUT &= ~BIT0;  }
void led_vd_apagado(void){  P4OUT &= ~BIT7;  }

void leds_config(){
    P1DIR |= BIT0;
    P4DIR |= BIT7;
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT7;
}
