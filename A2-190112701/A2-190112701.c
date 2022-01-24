// 190112701 e Luiz Eduardo Alves da Costa
// Prova A2
#include <msp430.h>
//Variáveis Globais
#define dbc 20000
#define TRUE 1
#define FALSE 0
#define ABERTA 1
#define FECHADA 0

//Protótipo das funções usadas no programa
void debounce (int val);//Debounce
void leds (int ct);//Switch com os casos de acionamento dos leds
void io_config(void);//Configuração dos leds e das chaves
int monitora_s1(void);//Função que monitora a chave s1
int monitora_s2(void);//Função que monitora a chave s2




int main(void){
    int cont=0; //contador

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    io_config();

    while(1){
       if (monitora_s1() == TRUE){
           cont++;
           }
       if (monitora_s2() == TRUE){
           leds(cont);
           cont=0;
           }
       }


}


int monitora_s1(void){
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

int monitora_s2(void){
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
    switch (ct){
    case 1: P1OUT |= BIT0; break;
    case 2: P1OUT &= ~BIT0; break;
    case 3: P4OUT |= BIT7; break;
    case 4: P4OUT &= ~BIT7;; break;
    default: break;
    }
}

void debounce (int val){
    volatile int x;
    for (x=0;x<val;x++);
}
