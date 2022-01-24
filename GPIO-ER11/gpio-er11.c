#include <msp430.h> 

#define dbc 30000
#define TRUE 1
#define FALSE 0
#define ABERTA 1
#define FECHADA 0


void debounce (int val);
void io_config(void);
void leds(int ct);
int mon_s1(void);
int mon_s2(void);

int main(void)
{
    int cont = 0;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	io_config();
	while(1){
        if(mon_s1() == TRUE) cont++;
        if(mon_s2() == TRUE) cont--;
        leds(cont);
	}

}

int mon_s1(void){
    static int ps1=ABERTA;
    if ((P2IN & BIT1) == 0){
        if (ps1 == ABERTA){
            debounce(dbc);
            ps1=FECHADA;
            return TRUE;
        }
    }
    else{
        if(ps1 == FECHADA){
            debounce(dbc);
            ps1=ABERTA;
            return FALSE;
        }
    }
    return FALSE;
}

int mon_s2(void){
    static int ps1=ABERTA;
        if ((P1IN & BIT1) == 0){
            if (ps1 == ABERTA){
                debounce(dbc);
                ps1=FECHADA;
                return TRUE;
            }
        }
        else{
            if(ps1 == FECHADA){
                debounce(dbc);
                ps1=ABERTA;
                return FALSE;
            }
        }
        return FALSE;
}

void io_config(void) {
    P2DIR &= (~BIT1);
    P2REN |= BIT1;
    P2OUT |= BIT1;

    P1DIR &= (~BIT1);
    P1REN |= BIT1;
    P1OUT |= BIT1;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}

void leds (int ct){
    switch (ct&3){
    case 0: P1OUT &= ~BIT0;  P4OUT &= ~BIT7; break;
    case 1: P1OUT &= ~BIT0;  P4OUT |= BIT7; break;
    case 2: P1OUT |= BIT0;  P4OUT &= ~BIT7; break;
    case 3: P1OUT |= BIT0; P4OUT |= BIT7; break;
    }
}

void debounce (int val){
    volatile int x;
    for (x=0;x<val;x++);
}


