// 190112701 - Luiz Eduardo Alves da Costa

// B2q1 - Esqueleto

#include <msp430.h> 

#define ADC12MEM0ADDR   (__SFR_FARPTR) 0x0720
#define SMCLK 1048576
#define TRUE    1
#define FALSE   0
#define ABERTA 1
#define FECHADA 0
#define CR      0xD //Carriage Return
#define LF      0xA //Line Feed

void dma_config(void);
void adc_config(void);
void ser_config(void);

void ta0_config1(void);//Modo 1
void ta0_config2(void);//Modo 2
void ta0_config3(void);//Modo 3
void ta0_config4(void);//Modo 4

void gpio_config(void);

void ser_dec16(int x);
void ser_char(char x);

int sw_mon(void);//Monitora chave P6.4
void delay(long limite);//Usada para na função sw_mon

volatile unsigned int mediax;     //médias do canal x
volatile unsigned int mediay;     //médias do canal y
volatile unsigned int somax;
volatile unsigned int somay;
volatile int vet_adc[128];  //receber 128 conversões de um período
volatile int n=0,flag,i,j;
volatile char mensagem_x[32] = "                                ";
volatile char mensagem_y[32] = "                                ";
volatile int posx,posy;
volatile char timer;

void main (void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    int contador;

    ser_config();
    adc_config();
    dma_config();
    gpio_config();
    ta0_config1();
    __enable_interrupt();

    flag==FALSE;
    while(TRUE){
        while(flag==FALSE);
        flag=FALSE;

        posx = mediax/32;
        posy = mediay/32;

        mensagem_x[16]='|';
        mensagem_y[16]='|';
        mensagem_x[posx]='*';
        mensagem_y[posy]='*';

        ser_char('#');
        for (i=0;i<32;i++){
            ser_char(mensagem_x[i]);
        }
        ser_char('#');
        for (i=0;i<32;i++){
             ser_char(mensagem_y[i]);
         }
        ser_char('#');

        ser_char(CR);
        ser_char(LF);

        for(i=0;i<32;i++){//Reiniciar a mensagem
            mensagem_x[i]=' ';
            mensagem_y[i]=' ';
        }
    }
}

// Atender à interrupção do DMA
#pragma vector = DMA_VECTOR // vector = 50
__interrupt void dma_isr(void){
    DMA0DA = &vet_adc[n];
        for(i=0;i<16;i+=2){
            somax += vet_adc[n+i];
            somay += vet_adc[n+i+1];
        }

    n = n + 16;
    if(n == 128) n=0;

    for (i=0;i<16;i=i+2){
        somax += vet_adc[n+i];
        somay += vet_adc[n+i+1];
    }
    mediax = somax >> 4;//Média x das conversões ads
    mediay = somay >> 4;//Média y das conversões ads


    DMAIV;
    DMA0CTL |= DMAEN;
    flag=TRUE;


}

void dma_config(void){
    DMACTL0 = DMA0TSEL_24;     //ADC dispara DMA
    DMA0CTL = DMAIE | DMAEN | DMADT_2 | DMADSTINCR_3 | DMASRCINCR_3;    //INterrupt e Rajada sem repetição
    DMA0SA = ADC12MEM0ADDR;
    DMA0SZ = 16;
    DMA0DA = &vet_adc[n];
}

void adc_config(void){

    ADC12CTL0 &= ~ADC12ENC; //Desabilitar
    ADC12CTL0 = ADC12ON ;
    ADC12CTL1 = ADC12CONSEQ_3 | //Sequência de Canais Repetido
                ADC12SSEL_3 | //SMCLK
                ADC12DIV_0  | //Div=0 clock do ADC
                ADC12SHS_1 | //Timer A0.1
                ADC12CSTARTADD_0; //MEM0
    ADC12CTL2 = ADC12RES_2; //12 bits

    ADC12MCTL0  = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL1  = ADC12INCH_3 | ADC12SREF_0;  //Entrada A3 (P6.3)
    ADC12MCTL2 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL3 = ADC12INCH_3 | ADC12SREF_0;  //Entrada A3 (P6.3)
    ADC12MCTL4  = ADC12INCH_2 | ADC12SREF_0;  //Entrada A3 (P6.2)
    ADC12MCTL5 = ADC12INCH_3 | ADC12SREF_0;  //Entrada A2 (P6.3)
    ADC12MCTL6 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A3 (P6.2)
    ADC12MCTL7  = ADC12INCH_3 | ADC12SREF_0;  //Entrada A3 (P6.3)
    ADC12MCTL8 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL9 = ADC12INCH_3 | ADC12SREF_0;  //Entrada A3 (P6.3)
    ADC12MCTL10  = ADC12INCH_2 | ADC12SREF_0;  //Entrada A3 (P6.2)
    ADC12MCTL11 = ADC12INCH_3 | ADC12SREF_0;  //Entrada A2 (P6.3)
    ADC12MCTL12 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A3 (P6.2)
    ADC12MCTL13  = ADC12INCH_3 | ADC12SREF_0;  //Entrada A2 (P6.3)
    ADC12MCTL14  = ADC12INCH_2 | ADC12SREF_0;  //Entrada A3 (P6.2)
    ADC12MCTL15 = ADC12INCH_3 | ADC12SREF_0;  //Entrada A2 (P6.3)

    ADC12MCTL15 |= ADC12EOS;                  //EOS=1, fim de sequência

    P6SEL |= BIT2|BIT3; // Desligar digital de P6.2,3
    ADC12CTL0 |= ADC12ENC; //Habilitar ADC12
}

void ser_config(void){
    UCA1CTL1 =  UCSSEL_2 | UCSWRST;     //UCSI em Reset
    UCA1CTL0 = UCSPB;                   //2 Stops
    UCA1BRW = 9;                // 115200
    UCA1MCTL=UCBRF_0 | UCBRS_1;
    P4DIR |=  BIT4;             //P4.4 saída
    P4DIR &= ~BIT5;             //P4.5 entrada
    P4SEL |= BIT5 | BIT4;       //Tx serial
    PMAPKEYID = 0X02D52;    //Liberar mapeamento
    P4MAP4 = PM_UCA1TXD;    //TX=Sair por P4.4
    P4MAP5 = PM_UCA1RXD;    //RX=Receber por P4.5
    UCA1CTL1 &= ~ UCSWRST;      //UCSI sai de Reset
}

void ta0_config1(void){
    TA0CTL = TASSEL__SMCLK | MC_1;
    TA0CCTL1 = OUTMOD_6; //Out = modo 6
    TA0CCR0 = SMCLK/1280; //T=100ms
    TA0CCR1 = TA0CCR0/2; //Carga 50%

    P1DIR |= BIT2;  //Sair TA0.1
    P1SEL |= BIT2;
}

void ta0_config2(void){
    TA0CTL = TASSEL__SMCLK | MC_1;
    TA0CCTL1 = OUTMOD_6; //Out = modo 6
    TA0CCR0 = SMCLK/320; //T=400ms
    TA0CCR1 = TA0CCR0/2; //Carga 50%

    P1DIR |= BIT2;  //Sair TA0.1
    P1SEL |= BIT2;
}

void ta0_config3(void){
    TA0CTL = TASSEL__SMCLK | MC_1;
    TA0CCTL1 = OUTMOD_6; //Out = modo 6
    TA0CCR0 = SMCLK/160; //T=800ms
    TA0CCR1 = TA0CCR0/2; //Carga 50%

    P1DIR |= BIT2;  //Sair TA0.1
    P1SEL |= BIT2;
}

void ta0_config4(void){
    TA0CTL = TASSEL__SMCLK | MC_1;
    TA0CCTL1 = OUTMOD_6; //Out = modo 6
    TA0CCR0 = SMCLK/128; //T=1s
    TA0CCR1 = TA0CCR0/2; //Carga 50%

    P1DIR |= BIT2;  //Sair TA0.1
    P1SEL |= BIT2;
}

// Configurar leds e chaves, inclusive SW
void gpio_config(void){
    P1DIR |=  BIT0;      //Led vermelho
    P1OUT &= ~BIT0;      //Vermelho Apagado
    P4DIR |=  BIT7;      //Led verde
    P4OUT &= ~BIT7;      //Verde Apagado

    P6DIR &= ~BIT4;      //P6.4 = SW
    P6REN |= BIT4;
    P6OUT |= BIT4;
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

// Monitorar SW (P6.4), retorna TRUE se foi acionada
int sw_mon(void){
     static int psw=ABERTA; //Guardar passado de Sw
     if ( (P6IN&BIT4) == 0){ //Qual estado atual de Sw?
     if (psw==ABERTA){ //Qual o passado de Sw?
         delay(1000);
         psw=FECHADA;
     return TRUE;
     }
  }
     else{
      if (psw==FECHADA){ //Qual o passado de Sw?
          delay(1000);
          psw=ABERTA;
      return FALSE;
      }
  }
  return FALSE;
 }

void delay(long limite){
    volatile long cont=0;
    while (cont++ < limite);
}
