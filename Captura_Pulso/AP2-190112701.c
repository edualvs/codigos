//Luiz Eduardo Alves da Costa
//Matrícula: 190112701

#include <msp430.h> 


volatile unsigned int startTime;
volatile unsigned int endTime;
long double deltaTime;
long double distance;
long double freq;

void io_config(void);
void ta1_config(void);
void ta2_config(void);
void acendeLeds (long double deltaTime);
void buzzer(long double distance);

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	io_config();
	ta1_config();
	ta2_config();
    __enable_interrupt(); //Ativando interrupção global

    while (1){
        P1OUT |= BIT5;                  //Trigger nível alto
        __delay_cycles(20);          // Deixa o trigger em nível alto por 20us
        P1OUT &= ~BIT5;                 //Trigger nível baixo
        __delay_cycles(100000);         // 10 medições por segundo
        acendeLeds(deltaTime);
    }

}

//---ISRs----------------------//
#pragma vector = TIMER1_A1_VECTOR
__interrupt void captura_Echo(void){
    switch (TA1IV){
        case 2:
            if (TA1CCTL1 & CCI){    // Borda de subida

                startTime = TA1CCR1;

            }else {                 //Borda de descida
                endTime = TA1CCR1;
                if (endTime > startTime){
                    deltaTime = endTime - startTime;
                }else {
                    deltaTime = (endTime - startTime) + 65535;
                }

            }
            break;
    }
    TA1CCTL1 &= ~CCIFG;
}

void io_config(void){
    // Configuração do ECHO
    P2DIR &= ~BIT0;  //Echo é uma entrada
    P2SEL |= BIT0;   // Echo é um input do sinal de captura

    //Configuração do Trigger
    P1DIR |= BIT5;  //Trigger é uma saída
    P1OUT &= ~BIT5; // Trigger em nível baixo

    //Led Vermelho Config
    P1DIR |= BIT0;  //Led Vermelho é uma saída
    P1OUT &= ~BIT0; //Led Vermelho apagado

    //Led Verde Config
    P4DIR |= BIT7;  //Led Verde é uma saída
    P4OUT &= ~BIT7; //Led Verde apagado

    //Porta do buzzer P2.5
    P2DIR |= BIT5;
    P2SEL |= BIT5;
    P2OUT &= ~BIT5;
}

void ta1_config(void){
    //Configuração do Timer para a medida de duração do pulso do ECHO
    TA1CTL |= TACLR;                 //Limpando o timer
    TA1CTL |= TASSEL__SMCLK;         //SMCLOCK
    TA1CTL |= MC__CONTINUOUS;        //Modo Continuous

    TA1CCTL1 |= CM_3; //Captura borda de subida e descida
    TA1CCTL1 |= SCS; //Modo Síncrono
    TA1CCTL1 |= CCIS_0; //Input da captura no Timer A
    TA1CCTL1 |= CAP; //Captura On
    TA1CCTL1 |= CCIE; //Ativando interrupção
    TA1CCTL1 &= ~CCIFG; //Limpar a flag
}

void ta2_config(void){
    //Config Timer A0
    //TA2CTL |= TACLR; //Limpa o Timer
    TA2CTL |= TASSEL__SMCLK; //SmCLK
    TA2CTL |= MC__UP;  //Modo UP
    TA2CCTL2 |= OUTMOD_6; //Gerador da onda quadrada
}

void acendeLeds (long double deltaTime){
    distance = (unsigned long)(deltaTime / 0.00583090379);//Calculando a distância (0.00583090379 = 1/(343/2)

    if ((distance/10000) < 10.0){ //  altura < 10 cm
        P1OUT |= BIT0;
        P4OUT |= BIT7;
        buzzer(distance/10000);//Função para ligar o buzzer
    }

    else if((distance/10000 >= 10.0) && (distance/10000 < 30.0)){ // 10cm <=  altura < 30 cm
        P1OUT |= BIT0;
        P4OUT &= ~BIT7;
        buzzer(distance/10000);//Função para ligar o buzzer
    }

    else if((distance/10000 >= 30.0) && (distance/10000 < 50.0)){// 30cm <=  altura < 50 cm
        P1OUT &= ~BIT0;
        P4OUT |= BIT7;
        buzzer(distance/10000);//Função para ligar o buzzer
    }

    else{ // altura > 50 cm
        P1OUT &= ~BIT0;
        P4OUT &= ~BIT7;
        buzzer(distance/10000);//Função para ligar o buzzer
    }
}

void buzzer (long double distance){//Função que faz o buzzer apitar
    if (distance <= 50){//Range de acionamento do buzzer
        freq = 5000+(-100)*distance;//Frequência
        TA2CCR0 = 1048576/freq; // SmClk/frequência
        TA2CCR2=TA2CCR0/2;
    }else{
        TA2CCR0 = 0;
        TA2CCR2=TA2CCR0/2;
    }
}
