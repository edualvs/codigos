#include <msp430.h> 

void adc_config(void);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	volatile int adc;
    adc_config();

    while (1){
        ADC12CTL0 |= ADC12SC;//Disparar conversão
        ADC12CTL0 &= ~ADC12SC;//Zerar
        while((ADC12IFG&ADC12IFG5) == 0);//IFG = 0? (NÃO CONVERTEU AINDA)
        adc = ADC12MEM5;
    }
	return 0;
}

void adc_config(void){
    ADC12CTL0 &= ~ADC12ENC;//Desabilita a conversão do ADC

    ADC12CTL0 |= ADC12ON;//Liga o ADC

    ADC12CTL1 = ADC12CONSEQ_0 | //Canal simples
                 ADC12SHS_0 | //ADC12SC
                 ADC12CSTARTADD_5 | //MEM5
                 ADC12SSEL_3; //SMCLK

    ADC12CTL2 = ADC12RES_2; //12 bits

    ADC12MCTL0 |= ADC12INCH1 | //A1
                  ADC12SREF_0;  //AVCC e AVSS

    P6SEL |= BIT1; //Desligar digital de P6.1

    ADC12CTL0 |= ADC12ENC;//Liga a conversão AD
}
