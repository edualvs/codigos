// ER 7.9
// TB0 para gerar PWM e controlar brilho dos leds
// Passo automático de 1% a cada 100 mseg
//
// TB0.2 --> P7.4 --> Cabo --> Vermelho (Led 1)
// TB0.1 --> mapeamento P4.7 --> Verde (Led 2)

#include <msp430.h>

#define TRUE 1
#define FALSE 0
#define PASSO 210 //0,0002 * 1.048.576 --> 200 useg
#define POT100 (100*PASSO) //Potência = 100%

void config_tb0(void); //Config TB0
void config_pinos(void); //Config Leds
volatile int cont; //Contar interruções
volatile int fase; //Sentido do incremento de 1% (TB0CCR1)

 // fase=0  (led2) TB0CCR1 += PASSO
 // fase=1  (led1) TB0CCR1 -= PASSO
int main(void){
     WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer
     config_pinos(); //Config pinnos
     config_tb0(); //Config TB0
     __enable_interrupt(); //Habilitação geral (GIE=1)
     while (TRUE); //Laço infinito
     return 0;
}
// Configurar TB0
void config_tb0(void){
     TB0CTL = TBSSEL_2 | MC_1; //TB0 com SMCLK e Modo Up
     TB0CCR0 = POT100; //Período PWM
     TB0CCTL0 = CCIE; // Interrup TB0CCR0 CCIFG (vetor 59)
     TB0CCTL1 = CLLD_1 | OUTMOD_6; //Saída Modo 6
     TB0CCTL2 = CLLD_1 | OUTMOD_6; //Saída Modo 6
     TB0CCR1 = POT100; //Led2 = 100%
     TB0CCR2 = 0; //Led1 = 0%
     fase=0; //Descer potência TB0CCR1 (led2)
   }
void config_pinos(void){
     P7DIR |= BIT4; //TB0.2 = P7.4
     P7SEL |= BIT4; //Ligar cabo para Led Vermelho
     P4DIR |= BIT7;
     P4SEL |= BIT7;
      PMAPKEYID = 0X02D52; //Escrever chave
      P4MAP7 = PM_TB0CCR1A; //TB0.1 mapeado para P4.7
 }
 //Rotina para tratar interrupção TB0CCTL0.CCIFG
 //#pragma vector = TIMER_B0_VECTOR
 #pragma vector = 59
 __interrupt void isr_tb0_ccifg0(void){
      if (++cont == 5){ //Contar 10 mseg
          cont=0;
          if (fase == 1){ //Sobe led1 (CCR2) e desce led2 (CCR1)
          if (TB0CCR1 == POT100){ //Led2=100%?
              fase=0; //Mudar sentido
              TB0CCR1 -= PASSO;
              TB0CCR2 = PASSO;
          }
          else{
              TB0CCR1 += PASSO;
              TB0CCR2 -= PASSO;
          }
  }
  else{ //Desce led1 e sobe led2
      if (TB0CCR1 == 0){ //Led2=0%?
          fase=1; //Mudar sentido
          TB0CCR1 = PASSO;
          TB0CCR2 -= PASSO;
          }
      else{
          TB0CCR1 -= PASSO;
          TB0CCR2 += PASSO;
          }
      }
    }
 }
