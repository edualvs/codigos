#include <msp430.h> 

void adc_config(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    volatile int adc[4];
    adc_config();

    while (1){
        ADC12CTL0 |= ADC12SC;//Disparar conversão
        ADC12CTL0 &= ~ADC12SC;//Zerar
        while((ADC12IFG&ADC12IFG0) == 0);//IFG = 0? (NÃO CONVERTEU AINDA)


        ADC12CTL0 |= ADC12SC;//Disparar conversão
        ADC12CTL0 &= ~ADC12SC;//Zerar
        while((ADC12IFG&ADC12IFG1) == 0);//IFG = 0? (NÃO CONVERTEU AINDA)


        ADC12CTL0 |= ADC12SC;//Disparar conversão
        ADC12CTL0 &= ~ADC12SC;//Zerar
        while((ADC12IFG&ADC12IFG2) == 0);//IFG = 0? (NÃO CONVERTEU AINDA)


        ADC12CTL0 |= ADC12SC;//Disparar conversão
        ADC12CTL0 &= ~ADC12SC;//Zerar
        while((ADC12IFG&ADC12IFG3) == 0);//IFG = 0? (NÃO CONVERTEU AINDA)


        adc[0] = ADC12MEM0;
        adc[1] = ADC12MEM1;
        adc[2] = ADC12MEM2;
        adc[3] = ADC12MEM3;
    }
    return 0;
}

void adc_config(void){
    ADC12CTL0 &= ~ADC12ENC;//Desabilita a conversão do ADC

    ADC12CTL0 |= ADC12ON;//Liga o ADC

    ADC12CTL1 = ADC12CONSEQ_1 | //Canal simples
                 ADC12SHS_0 | //ADC12SC
                 ADC12CSTARTADD_0 | //MEM0
                 ADC12SSEL_3; //SMCLK

    ADC12CTL2 = ADC12RES_2; //12 bits

    ADC12MCTL0 = ADC12INCH_0 | ADC12SREF_0;  //AVCC e AVSS - MEM0
    ADC12MCTL1 = ADC12INCH_1 | ADC12SREF_0;  //AVCC e AVSS - MEM1
    ADC12MCTL2 = ADC12INCH_2 | ADC12SREF_0;  //AVCC e AVSS - MEM2
    ADC12MCTL3 = ADC12INCH_3 | ADC12SREF_0 | ADC12EOS;  //AVCC e AVSS - MEM3

    P6SEL |= (BIT0|BIT1|BIT2|BIT3); //Desligar digital de P6.0, P6.1, P6.2, P6.3

    ADC12CTL0 |= ADC12ENC;//Liga a conversão AD
}
