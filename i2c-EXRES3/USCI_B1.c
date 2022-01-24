//ER 9.1 - USCI_B1.c
// USCI_B1 programada com escravo com endereço = 42
// Escravo transmissor envia 0, 1, 2, ..., 255, 1, 2,...
// Escravo receptor guardar os últimos 10 bytes
// P4.1 = SDA e P4.2 = SCL

#include <msp430.h>
#include "USCI_B1.h"

void USCI_B1_config(void){

     UCB1CTL1 = UCSWRST; //Resetar USCI_B1
     UCB1CTL0 = UCMODE_3 | //Modo I2C
     UCSYNC; //Síncrono
     UCB1I2COA = 42; //Endereço do Escravo
     UCB1CTL1 = 0; //UCSWRST=0
     UCB1IE = UCTXIE | UCRXIE; //Hab interrp TX e RX

     P4SEL |= BIT2 | BIT1; //Função alternativa
     P4REN |= BIT2 | BIT1; //Hab resistor
     P4OUT |= BIT2 | BIT1; //Pullup

     for (b1=0; b1<MAX_B1; b1++) //Zerar vetor
         b1_vet[b1]=0;

     b1=0; //Zerar indexad
     b1_cont=0; //Zerar contador
     __enable_interrupt(); //GIE=1, hab int geral
}

// ISR da USCI_B1
#pragma vector = USCI_B1_VECTOR //Vetor 45
__interrupt void isr_USCI_B1(void){
     int n;
     n = __even_in_range(UCB1IV,0xC); //Consultar UCB1IV
     switch(n){
         case 0x0: break; case 0x2: break;
         case 0x4: break; case 0x6: break;
         case 0x8: break;
         case 0xA: USCI_B1_rx(); break; //Rotina RX
         case 0xC: USCI_B1_tx(); break; //Rotina TX
     }
}

// Rotina para receber um byte e guardar no vetor
void USCI_B1_rx(void){
     b1_vet[b1++] = UCB1RXBUF; //Guardar dado recebido
     if (b1>MAX_B1) b1=0; //Verificar limite do vetor
}

// Rotina para transmitir o contador e incrementá-lo
void USCI_B1_tx(void){
    UCB1TXBUF = b1_cont++; //Transmitir contador
}
