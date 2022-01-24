#include <msp430.h> 


void io_config(void);
void delay(void);
void leds(int ct);

volatile int s1_flag = 0;
volatile int s2_flag = 0;
int cont=0;

unsigned char rand() {
 static unsigned char num = 5;
 num = (num * 17) % 7;
 return num;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    io_config();


    do{
        P1IFG = 0;
    }while(P1IFG != 0);

    do{
        P2IFG = 0;
    }while(P2IFG != 0);

    _enable_interrupt();
    s1_flag = 0;
    s2_flag = 0;
    rand();
    while(1){
       if (s2_flag){
            if(cont == rand()){
                P4OUT |= BIT7;
                rand();
                cont = 0;
            }else{
                P1OUT |= BIT0;
                cont = 0;
            }
        }

        P1OUT &= ~BIT0;
        P1OUT &= ~BIT7;
    }
}

#pragma vector = PORT1_VECTOR
__interrupt void P1ISR()
{
    switch(_even_in_range(P1IV,0x10))
    {
    case 0x00:
            break;
    case 0x02:
            break;
    case 0x04:
            s2_flag = 1;
            break;
    case 0x06:
            break;
    case 0x08:
            break;
    case 0x0A:
            break;
    case 0x0C:
            break;
    case 0x0E:
            break;
    case 0x10:
            break;

    }
}

#pragma vector = PORT2_VECTOR
__interrupt void P2ISR()
{
    switch(_even_in_range(P2IV,0x10))
    {
    case 0x00:
            break;
    case 0x02:
            break;
    case 0x04:
            s1_flag = 1;
            cont++;
            break;
    case 0x06:
            break;
    case 0x08:
            break;
    case 0x0A:
            break;
    case 0x0C:
            break;
    case 0x0E:
            break;
    case 0x10:
            break;

    }
}

void leds (int ct){
    switch (ct&3){
    case 0: P1OUT &= ~BIT0;  P4OUT &= ~BIT7; break;
    case 1: P1OUT &= ~BIT0;  P4OUT |= BIT7; break;
    case 2: P1OUT |= BIT0;  P4OUT &= ~BIT7; break;
    case 3: P1OUT |= BIT0; P4OUT |= BIT7; break;
    }
}


void io_config() {
   //Configuração chave S1
   P2DIR &= ~BIT1;
   P2REN |= BIT1;
   P2OUT |= BIT1;
   P2IE |= BIT1;
   P2IES &= ~BIT1;

   //Configuração chave S2
   P1DIR &= ~BIT1;
   P1REN |= BIT1;
   P1OUT |= BIT1;
   P1IE |= BIT1;
   P1IES &= ~BIT1;

   //Led Vermelho apagado
   P1SEL &= ~BIT0;
   P1DIR |= BIT0;
   P1OUT &= ~BIT0;

   //Led Verde apagado
   P4SEL &= ~BIT7;
   P4DIR |= BIT7;
   P4OUT &= ~BIT7;
}

void delay()
{
    volatile unsigned int x = 40000;
    while (x>0){
        x--;
    }
}
