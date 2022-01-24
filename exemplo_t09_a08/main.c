#include <msp430.h> 

#define dbc 20000
#define TRUE 1
#define FALSE 0
#define ABERTA 1
#define FECHADA 0

#define T_PWM 10480
#define PASSO_10 1048

int mon_s1(void);//Função que monitora a chave s1
int mon_s2(void);//Função que monitora a chave s2
void debounce (int val);//Debounce
void ta0_config(void);
void io_config(void);
void ta2_config(void);

volatile int freq;  //Frequência do PWM em Hz
volatile int cc;    //Ciclo de carga do PWM(%)

int main(void)
{
    volatile unsigned int cap1,cap2,cap3;//Variáveis para armazenar as capturas
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	io_config();
	ta0_config();
	ta2_config();
	while(1){
	    if (mon_s1() == TRUE){
	        if (TA0CCR1 < TA0CCR0)
	            TA0CCR1 += PASSO_10;
	    }
	    if (mon_s2() == TRUE) {
	        if (TA0CCR1 > 0)
	            TA0CCR1 -= PASSO_10;
	    }


        //Flanco de subida
        TA2CCTL1 &= ~CM_3; //Zerar o campo CM
        TA2CCTL1 |= CM_1; //Flanco de subida
        TA2CCTL1 &= ~CCIFG; //Apagar flag
        while ((TA2CCTL1&CCIFG)==0); //Esperar CCIFG
        cap1 = TA2CCR1; //Guardando captura

        //Flanco de descida
        TA2CCTL1 &= ~CM_3; //Zerar o campo CM
        TA2CCTL1 |= CM_2; //Flanco de descida
        TA2CCTL1 &= ~CCIFG; //Apagar flag
        while ((TA2CCTL1&CCIFG)==0); //Esperar CCIFG
        cap2 = TA2CCR1; //Guardando captura

        //Flanco de subida
        TA2CCTL1 &= ~CM_3; //Zerar o campo CM
        TA2CCTL1 |= CM_1; //Flanco de subida
        TA2CCTL1 &= ~CCIFG; //Apagar flag
        while ((TA2CCTL1&CCIFG)==0); //Esperar CCIFG
        cap3 = TA2CCR1; //Guardando captura

        //Calculando a frequência
        if(cap3<cap1)   freq = 1/((long) cap3 - cap1 + 65536L);
        else            freq = 1/(cap3-cap1);

        //Calculando o ciclo de carga
        if (cap2<cap1)   cc = (long)cap2 - cap1 + 65536L;
        else             cc = cap2 - cap1;

        //Transformando para porcentagem
        cc = 100*((float)cc*freq) + 0.5;

	}
	return 0;
}

// Configurar TA2 para captura por CCR1
void ta2_config(void){
    TA2CTL = TASSEL_2 | MC_2; // SMCLK, MODO 2
    TA2CCTL1 =CCIS_0 | SCS | CAP; // Entrada P2.4 / Modo Síncrono / Modo Captura


    P2DIR &= ~BIT4; //P2.4 como entrada
    P2REN |= BIT4; //Habilitar resistor
    P2OUT |= BIT4; //Para pullup
    P2SEL |= BIT4; //Dedicado para captura (TA2.1)

}

void ta0_config()
{
    TA0CTL = TASSEL_2 | MC_1;
    TA0CCTL1 = OUTMOD_6;
    TA0CCR0 = T_PWM;
    TA0CCR1 = 5*PASSO_10;
    P1DIR |= BIT2;
    P1SEL |= BIT2;

}

void io_config()
{
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;

    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
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


void debounce (int val){
    volatile int x;
    for (x=0;x<val;x++);
}

