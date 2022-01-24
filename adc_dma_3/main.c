// adc_dma_exemplo 3
// Primeiro exemplo com ADC + DMA
// Interrupção do DMA
// Envia pela porta serial

// Usar ADC12SC disp por TA0.1

#include <msp430.h> 

#define ADC12MEM0ADDR   (__SFR_FARPTR) 0x0720
#define ADC12MEM8ADDR   (__SFR_FARPTR) ADC12MEM0ADDR+16

#define ACLK    32768
#define TRUE    1
#define FALSE   0
#define CR      0xD //Carriage Return
#define LF      0xA //Line Feed


void adc_config(void);
void ta0_config(void);
void dma_config(void);
void ser_config(void);
void ser_dec16(int x);
void ser_char(char x);


volatile int vet_adc[4];    //Receber conversões do ADC via DMA
volatile int ax,ay,flag;

int main(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    ta0_config();
    adc_config();
    dma_config();
    ser_config();

    __enable_interrupt();

    flag=FALSE;
    while(1){
        while(flag==FALSE);
        flag=FALSE;
        ser_dec16(ax);
        ser_char(' ');
        ser_dec16(ay);
        ser_char(CR);
        ser_char(LF);
    }

    return 0;
}

//#pragma vector = 50
#pragma vector = DMA_VECTOR
__interrupt void dma_isr(void){
    ax=(vet_adc[0]+vet_adc[2])>>1;
    ay=(vet_adc[1]+vet_adc[3])>>1;
    //DMA0SA = ADC12MEM8ADDR;
    //DMA0DA = vet_adc;
    //DMA0SZ = 4;
    DMAIV;
    DMA0CTL |= DMAEN;
    flag=TRUE;
}


void dma_config(void){
    DMACTL0 = DMA0TSEL_24;     //ADC dispara DMA
    DMA0CTL = DMAIE | DMAEN | DMADT_2 | DMADSTINCR_3 | DMASRCINCR_3;    //INterrupt e Rajada sem repetição
    DMA0SA = ADC12MEM8ADDR;
    DMA0DA = vet_adc;
    DMA0SZ = 4;
}

// Ao usar DMA, não habilitar interrupção do ADC
void adc_config(void){
    ADC12CTL0  &= ~ADC12ENC;        //Desabilitar para configurar
    ADC12CTL0 = ADC12ON;            //Ligar ADC ADC12EN=0;
    ADC12CTL1 = ADC12CSTARTADD_8 |  //Start=8
                ADC12SHS_1       |  //Disp com TA0.1
                ADC12DIV_0       |  //Div=0 clock do ADC
                ADC12SSEL_3      |  //SMCLK
                ADC12CONSEQ_3;      //Seq canais com repetição
    ADC12CTL2  = ADC12RES_2;                  //12 bits
    ADC12MCTL8  = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL9  = ADC12INCH_3 | ADC12SREF_0;  //Entrada A3 (P6.3)
    ADC12MCTL10 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL11 = ADC12INCH_3 | ADC12SREF_0;  //Entrada A3 (P6.3)
    ADC12MCTL11 |= ADC12EOS;                  //EOS=1, fim de sequência
    ADC12CTL0  |= ADC12ENC;                   //Habilitar ADC
    P6SEL |= BIT3|BIT2;
}

void ta0_config(void){
    TA0CTL = TASSEL_1 | MC_1;   // ACLK
    TA0CCR0 = ACLK/8;           // 8 conversões por segundo
    TA0CCTL1 = OUTMOD_6;
    TA0CCR1 = TA0CCR0/2;        //Carga = 50%
    P1DIR |= BIT2;
    P1SEL |= BIT2;
}

void ser_config(void){
    UCA1CTL1 =  UCSSEL_2 | UCSWRST;     //UCSI em Reset
    UCA1CTL0 = UCSPB;                   //2 Stops

    //Baudrate 9.600
    UCA1BRW = 6;                //Divisor por 3
    UCA1MCTL=UCBRF_13 | UCBRS_0 | UCOS16;
    // 115200
    //UCA1BRW = 9;                //Divisor por 9
    //UCA1MCTL=UCBRF_0 | UCBRS_1;

    P4DIR |=  BIT4;             //P4.4 saída
    P4DIR &= ~BIT5;             //P4.5 entrada
    P4SEL |= BIT5 | BIT4;       //Tx serial
    PMAPKEYID = 0X02D52;    //Liberar mapeamentp
    P4MAP4 = PM_UCA1TXD;    //TX=Sair por P4.4
    P4MAP5 = PM_UCA1RXD;    //RX=Receber por P4.5

    UCA1CTL1 &= ~ UCSWRST;      //UCSI sai de Reset
}

void ser_dec16(int x){
    char z;

    z=x/10000;    //separar dez milhar
    ser_char(0x30+z);

    x=x-10000*z;
    z=x/1000;     //separar milhar
    ser_char(0x30+z);

    x=x-1000*z;
    z=x/100;    //separar centena
    ser_char(0x30+z);

    x=x-100*z;
    z=x/10;     //separar dezena
    ser_char(0x30+z);

    x=x-10*z;
    ser_char(0x30+x);
}

void ser_char(char x){
    UCA1TXBUF = x;
    while ( (UCA1IFG & UCTXIFG) == 0);
    UCA1IFG &= ~UCTXIFG;
}
