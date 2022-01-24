#include <msp430.h> 
#define dbc 30000
void io_config (void);
void inverte_led (void);
void debounce (int val);

int main(void)
{

    io_config();
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
while(1){
    if ((P2IN&BIT1) == BIT1);
    if((P2IN&BIT1) == 0){
        inverte_led();
    }
    debounce(dbc);
    }
}
void io_config(void) {
   P1DIR |= BIT0;
   P1OUT &= (~BIT0);

   P2DIR &= (~BIT1);
   P2REN |= BIT1;
   P2OUT |= BIT1;
}

void inverte_led(void){
        P1OUT ^= BIT0;
}

void debounce (int val){
    volatile int x;
    for (x=0;x<val;x++);
}
