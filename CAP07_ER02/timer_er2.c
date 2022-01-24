//ER 7.7
// Controlar brilho do LED1 com PWM (TA0.1)
// Período de 20 ms, Ciclos de Carga 20%, 50% e 80%
// Usar cabo para ligar pino P1.2 (TA0.1) ao pino 2 do Jumper JP8
#include <msp430.h>
void config_ta01(void);
void config_p12(void);
#define TRUE 1
#define T20ms 20971 //período de 20 ms, (32768 x 0,02) - 1
#define PWM10 (0.1*T20ms) //10% de ciclo de carga
#define PWM40 (0.4*T20ms) //40% de ciclo de carga
#define PWM80 (0.8*T20ms) //80% de ciclo de carga
int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
 config_p12();
 config_ta01();

 while(TRUE){
 TA0CCR1 = PWM10; //10%
 __delay_cycles(2000000); //Espera 2 segundos
 TA0CCR1 = PWM40; //40%
 __delay_cycles(2000000); //Espera 2 segundos
 TA0CCR1 = PWM80; //80%
 __delay_cycles(2000000); //Espera 2 segundos
 }
 return 0;
}
// Configurar TA0.1
void config_ta01(void){
 TA0CTL = TASSEL_1 | MC_2; //TA0 com ACLK e modo 1
 TA0CCR0 = T20ms; //Limite para 20ms
 TA0CCTL1 = OUTMOD_6; //TA0.1, saída no Modo 6
}
// Configurar P1.2 (TA0.1)
void config_p12(void){
    P1DIR |= BIT2; //P1.2 como saída
    P1SEL |= BIT2; //P1.2 dedicado ao TA0.1
   }

