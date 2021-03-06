// ER8.1 USCI_A0
//
// Comunica??o serial com loop back (UCLISTEN = 1)
// Usar polling
// USCI_A0 Transmite e recebe letras de A at? Z
// 9.600 bauds (ACLK), 8 bits, sem paridade, 1 stop
#include <msp430.h>
#define TRUE 1
#define FALSE 0
void USCI_A0_config(void);
void led_VM(void);
void led_vm(void);
void led_VD(void);
void led_vd(void);
void leds_config(void);
int main(void){
 char letra_tx,letra_rx;
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 leds_config();
 USCI_A0_config();
 letra_tx='A';
 while(TRUE){ //La?o principal
 while ( (UCA0IFG&UCTXIFG)==0); //Esperar TXIFG=1
 UCA0TXBUF=letra_tx;
 while ( (UCA0IFG&UCRXIFG)==0); //Esperar RXIFG=1
 letra_rx=UCA0RXBUF;
 if (letra_tx == letra_rx){ //Verificar
 led_VD(); led_vm(); //OK
 }
 else{
 led_vd(); led_VM(); //Erro
 }
 if (++letra_tx == 'Z'+1) letra_tx='A'; //Pr?xima letra
 }
 return 0;
}
// Configurar USCI_A0
void USCI_A0_config(void){
 UCA0CTL1 = UCSWRST; //RST=1 para USCI_A0
 UCA0CTL0 = 0; //sem paridade, 8 bits, 1 stop, modo UART
 UCA0STAT = UCLISTEN; //Loop Back
 UCA0BRW = 3; // Divisor
 UCA0MCTL = UCBRS_3; //Modulador = 3 e UCOS=0
 UCA0CTL1 = UCSSEL_1; //RST=0 e Selecionar ACLK
}
// Controle dos leds
void led_VM(void){ P1OUT |= BIT0; } //led Vermelho aceso
void led_vm(void){ P1OUT &= ~BIT0; } //led Vermelho apagado
void led_VD(void){ P4OUT |= BIT7; } //led Verde aceso
void led_vd(void){ P4OUT &= ~BIT7; } //led Verde apagado
// Configurar Leds
void leds_config(void){
 P1DIR |= BIT0; P1OUT &= ~BIT0; //Led vermelho
 P4DIR |= BIT7; P4OUT &= ~BIT7; //Led verde
}
