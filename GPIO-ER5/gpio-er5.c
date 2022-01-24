#include <msp430.h> 

void io_config (void);
void acende_led (void);
void apaga_led (void);

int main(void)
{
    io_config();
while(1){
    if ((P2IN&BIT1) == 0)
        acende_led();
    else
        apaga_led();
    }
}

void io_config(void) {
   P1DIR |= BIT0;
   P1OUT &= (~BIT0);

   P2DIR &= (~BIT1);
   P2REN |= BIT1;
   P2OUT |= BIT1;
}

void acende_led(void){
    P1OUT |= BIT0;
}

void apaga_led(void){
    P1OUT &= (~BIT0);
}
