#include <msp430.h> 

#define PASSO10 2100
#define PASSO25 5250
#define POT100 21000

void ta0_config(void);
void tb0_config(void);
void io_config(void);
void p47_map(void);

volatile int cont1;
volatile int cont2;
volatile int fase;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	ta0_config();//Configura timer A
	tb0_config();//Configura timer B
	io_config();//Configura chaves
	p47_map();//Mapeia porta 4.7

    fase = 0;//Inverte o sentido do PWM LENTO
	__enable_interrupt();//Habilita interrupções globais
	while (1){
	    if (((P2IN&BIT1) == 0 && (P1IN&BIT1) == 0) || ((P2IN&BIT1) != 0 && (P1IN&BIT1) != 0)){//Se as duas chaves abertas ou duas chaves fechadas
	        TA0CCTL0 &= ~CCIE;
	        TA0CCR3 = 0;
	        TB0CCTL0 &= ~CCIE;
	        TB0CCR1 = 0;
	    }
	    if ((P2IN&BIT1) == 0){//Chave S1 apertada
	        TA0CCTL0 |= CCIE;
	    }

	    if ((P1IN&BIT1) == 0){//Chave S2 apertada
	                TB0CCTL0 |= CCIE;
	            }
	}
}

//---------ISR TIMER A INICIO -------------------//

#pragma vector = TIMER0_A0_VECTOR
__interrupt void isr_ta0_0 (){
    if(++cont1 == 5){//100ms = 0,1s
        cont1 = 0;
        if (TA0CCR3 == POT100){
        TA0CCR3 = 0;
            if (fase == 1){//100% a 0% o PWM LENTO
                if(TB0CCR1 == POT100){
                    fase = 0;
                    TB0CCR1 -= PASSO25;
                }
                else{
                    TB0CCR1 += PASSO25;
                }
            }
            else{//0% a 100% o PWM LENTO
                if(TB0CCR1 == 0){
                    fase = 1;
                    TB0CCR1 = PASSO25;
                }
                else{
                    TB0CCR1 -= PASSO25;
                }
            }
        }

    else{
        TA0CCR3 += PASSO10;
        }
    }
}

//---------ISR TIMER A FINAL -------------------//

//---------ISR TIMER B INICIO -------------------//

#pragma vector = 59
__interrupt void isr_tb0_0 (){
    if(++cont2 == 5){//100ms = 0,1s
            cont2 = 0;
            if (TB0CCR1 == POT100){
            TB0CCR1 = 0;
                if (fase == 1){//100% a 0% o PWM LENTO
                    if(TA0CCR3 == POT100){
                        fase = 0;
                        TA0CCR3 -= PASSO25;
                    }else{
                        TB0CCR1 += PASSO25;
                    }
                }
                else{//0% a 100% o PWM LENTO
                    if(TA0CCR3 == 0){
                        fase = 1;
                        TA0CCR3 = PASSO25;
                    }else{
                        TA0CCR3 -= PASSO25;
                    }
                }
            }

        else{
            TB0CCR1 += PASSO10;
        }
    }
}

//---------ISR TIMER B FINAL -------------------//

void ta0_config(void){
    TA0CTL |= TACLR;//Limpa o clk
    TA0CTL |= TASSEL__SMCLK//smclk
           | MC__UP;//
    TA0CCTL3 |= OUTMOD_6; //Gerador da onda quadrada
    TA0CCR0 = POT100;
    TA0CCR3 = 0;
}


void tb0_config(void){
    TB0CTL |= TBCLR;//Limpa o clk
    TB0CTL |= TBSSEL__SMCLK//smclk
           | MC__UP;//
    TB0CCTL1 |= OUTMOD_6; //Gerador da onda quadrada
    TB0CCR0 = POT100;
    TB0CCR1 = 0;
}

void io_config(void){
    //Config P1.4
    P1DIR |= BIT4;
    P1SEL |= BIT4;

    //Config chave S1
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;

    //Configuração chave S2
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
}

// Mapear TB0.1 em P4.7
void p47_map(void){
     P4DIR |= BIT7; //P4.7 como saída
     P4SEL |= BIT7; //P4.7 recebe saída alternativa
     PMAPKEYID = 0X02D52; //Liberar mapeamento
     P4MAP7 = PM_TB0CCR1A; //P4.7 = TB0.1
}
