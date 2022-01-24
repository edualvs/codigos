#include <msp430.h> 

void io_config (void);
void acende_led_vermelho (void);
void acende_led_verde (void);
void apaga_led_vermelho (void);
void apaga_led_verde (void);

int main(void){

    io_config();
while(1){
    if ((P2IN&BIT1) == 0)
        acende_led_vermelho();
    else
        apaga_led_vermelho();
    if ((P1IN&BIT1) == 0)
        acende_led_verde();
       else
        apaga_led_verde();
    }
}
void io_config(void) {
   P1DIR |= BIT0;
   P1OUT &= ~BIT0;

   P4DIR |= BIT7;
   P4OUT &= ~BIT7;

   P2DIR &= (~BIT1);
   P2REN |= BIT1;
   P2OUT |= BIT1;

   P1DIR &= (~BIT1);
   P1REN |= BIT1;
   P1OUT |= BIT1;
}

void acende_led_vermelho (void){
    P1OUT |= BIT0;
}
void apaga_led_vermelho (void){
    P1OUT &= ~BIT0;
}
void acende_led_verde (void){
    P4OUT |= BIT7;
}
void apaga_led_verde (void){
    P4OUT &= ~BIT7;
}
