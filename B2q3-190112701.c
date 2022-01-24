// 190112701 - Luiz Eduardo Alves da Costa

// B2q3 - Esqueleto

// LCD: P3.0 = SDA e P3.1 = SCL

#include <msp430.h> 

#define TRUE    1
#define FALSE   0
#define ABERTA    1
#define FECHADA   0

#define TACLK 32768
#define PCF_ADR1 0x3F //Possíveis endereços do lcd
#define PCF_ADR2 0x27 //Possíveis endereços do lcd

#define PCF_ADR  PCF_ADR2 //Endereço do lcd usado

#define BR_100K    11  //SMCLK/100K = 11
#define BR_50K     21  //SMCLK/50K  = 21
#define BR_10K    105  //SMCLK/10K  = 105
// Caracteres especiais para o LCD
char barras[64]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,   //0
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F,   //1
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F,   //2
                  0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F,   //3
                  0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,   //4
                  0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,   //5
                  0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,   //6
                  0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};  //7

void lcd_barras(void);
void lcd_char(char x);//Imprimi um char no lcd
void lcd_str(char *vt);
void lcd_cmdo(char x);
void i2c_write(char dado); // <<==== atualizar esta função

void adc_config_modo0(void);
void adc_config_modo1(void);
void ta0_config_modo0(void);
void ta0_config_modo1(void);
void gpio_config(void);
void i2c_config(void);
int sw_mon(void);//Monitora chave P6.4
void lcd_apaga_cursor(void);
void delay(long limite);//Usada para inicializar o lcd
void lcd_inic(char dado);//Inicializar o lcd
void lcd_aux(char dado);//Auxiliar a função de inicializar o lcd
char i2c_test(char dado);//Conferir endereço do lcd
void lcd_clear(void);//Limpar o lcd


//Funções do cursor do lcd
void lcd_aux_cursor(char x);
void lcd_cursor(char x);

volatile int medx,medy;     //Valores das médias
volatile int adc[2];
volatile int barra0_x,barra0_y,barra1_x,barra1_y;//Passo (Para o calcular as barras)
volatile int modo;//modo
char PCF = 0;

void main(void){
    int cont=0,n=0,aux=0;
    char adr,caracter;
    char *vet0,*vet1;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    gpio_config();
    i2c_config();

    if (i2c_test(0x27) == TRUE) adr=0x27;
    else if (i2c_test(0x3F) == TRUE) adr=0x3F;
    else{
        P4OUT |= BIT7; //Led verde sinaliza problema
        while(TRUE);
    }

    lcd_inic(adr);//Inicializa o lcd com o endereço correto
    lcd_barras();//Configurando os caracteres especiais!
    //lcd_apaga_cursor();
    __enable_interrupt();
    while(TRUE){
        if(sw_mon() == TRUE){
            lcd_clear(); //Limpa lcd
            cont++;
            if(cont==2) cont=0;//2 modos
        }

        switch (cont) {
            case 0:
                modo = 0;
                adc_config_modo0();
                ta0_config_modo0();

                caracter = barra0_y;

                if (barra0_y < 8){
                    lcd_cursor(0x40);
                    for(n=0;n<=barra0_x;n++){
                        lcd_char(caracter);
                    }
                    for(n=0;n<15-barra0_x;n++){
                        lcd_char(0x20);
                    }
                    lcd_cursor(0x00);
                    for(n=0;n<barra0_x;n++){
                        lcd_char(0x20);
                    }
                }
                else{
                    caracter = barra0_y - 8;
                    lcd_cursor(0x40);
                    for(n=0;n<=barra0_x;n++){
                        lcd_char(7);
                    }

                    lcd_cursor(0x00);
                    for(n=0;n<=barra0_x;n++){
                        lcd_char(caracter);
                    }
                    for(n=0;n<15-barra0_x;n++){
                        lcd_char(0x20);
                    }
                }

                break;

            case 1:
                modo=1;
                adc_config_modo1();
                ta0_config_modo1();

                caracter = barra1_y;

                if (barra1_y < 8){
                    lcd_cursor(0x40);
                    for(n=0;n<=barra1_x;n++){
                        lcd_char(caracter);
                    }
                    for(n=0;n<15-barra1_x;n++){
                        lcd_char(0x20);
                    }
                    lcd_cursor(0x00);
                    for(n=0;n<barra1_x;n++){
                        lcd_char(0x20);
                    }
                }
                else{
                    caracter = barra1_y - 8;
                    lcd_cursor(0x40);
                    for(n=0;n<=barra1_x;n++){
                        lcd_char(7);
                    }

                    lcd_cursor(0x00);
                    for(n=0;n<=barra1_x;n++){
                        lcd_char(caracter);
                    }
                    for(n=0;n<15-barra1_x;n++){
                        lcd_char(0x20);
                    }
                }
                break;

            default:
                break;
        }
    }
}

// Atender à interrupção do ADC
#pragma vector = ADC12_VECTOR    //54
__interrupt void adc_isr(void){
     volatile unsigned int *pt;
     volatile unsigned int i,soma;

     if(modo == 0){
          adc[0] = ADC12MEM0;
          adc[1] = ADC12MEM1;

          adc[1] = 4095 - adc[1];//Inverter o eixo y

          barra0_x = adc[0]*15/4095;
          barra0_y = adc[1]*15/4095;
     }
     else{
         pt = &ADC12MEM0;
         soma = 0;
         for (i=0; i<8; i++) soma +=pt[i];
         medx = soma >> 3;

         soma = 0;

         for (i=8; i<16; i++) soma +=pt[i];
         medy = soma >> 3;

         medy = 4095 - medy;//Inverter o eixo y

         barra1_x = medx*15/4095;
         barra1_y = medy*15/4095;
     }

}

// Configurar ADC modo 0
void adc_config_modo0(void){
    ADC12CTL0 &= ~ADC12ENC; //Desabilitar
    ADC12CTL0 = ADC12ON ;
    ADC12CTL1 = ADC12CONSEQ_3 | //Sequência de Canais Repetido
                ADC12SSEL_3 | //SMCLK
                ADC12SHS_1 | //Timer A0.1
                ADC12CSTARTADD_0; //MEM0
    ADC12CTL2 = ADC12RES_2; //12 bits

    ADC12MCTL0 = ADC12SREF_0 | ADC12INCH_2; //A2 - Config MEM0
    ADC12MCTL1 = ADC12EOS| ADC12SREF_0 | ADC12INCH_3; //A3 - MEM1=última

    P6SEL |= BIT2|BIT3; // Desligar digital de P6.2,3
    ADC12CTL0 |= ADC12ENC; //Habilitar ADC12
    ADC12IE |= ADC12IE1; //Hab interrupção MEM1
}

// Configurar ADC modo 1
void adc_config_modo1(void){
    volatile unsigned char *pt;
    unsigned char i;
    ADC12CTL0 &= ~ADC12ENC; //Desabilitar
    ADC12CTL0 = ADC12ON ;
    ADC12CTL1 = ADC12CONSEQ_3 | //Sequência de Canais Repetido
                ADC12SSEL_3 | //SMCLK
                ADC12SHS_1 | //Timer A0.1
                ADC12CSTARTADD_0; //MEM0
    ADC12CTL2 = ADC12RES_2; //12 bits

    //Leituras alternadas
    pt=&ADC12MCTL0;
    for (i=0; i<8; i++)
            pt[i]=ADC12SREF_0 | ADC12INCH_2; //A2

    for (i=8; i<16; i++)
            pt[i]=ADC12SREF_0 | ADC12INCH_3;//A3


    pt[15] |= ADC12EOS;//EOS em ADC12MCTL15

    P6SEL |= BIT2|BIT3; // Desligar digital de P6.2,3
    ADC12CTL0 |= ADC12ENC; //Habilitar ADC12
    ADC12IE |= ADC12IE15; //Hab interrupção MEM15
}

// Configurar TA0.1 modo 0
void ta0_config_modo0(void){
    TA0CTL = TASSEL__ACLK | MC_1;
    TA0CCTL1 = OUTMOD_6; //Out = modo 6
    TA0CCR0 = TACLK/20; //20 conversões por segundo
    TA0CCR1 = TA0CCR0/2; //Carga 50%
    P1DIR |= BIT2;  //Sair TA0.1
    P1SEL |= BIT2;
}

// Configurar TA0.1 modo 1
void ta0_config_modo1(void){
    TA0CTL = TASSEL__ACLK | MC_1;
    TA0CCTL1 = OUTMOD_6; //Out = modo 6
    TA0CCR0 = TACLK/160; //160 conversões por segundo
    TA0CCR1 = TA0CCR0/2; //Carga 50%
    P1DIR |= BIT2;  //Sair TA0.1
    P1SEL |= BIT2;
}

// Configurar i2c
void i2c_config(void){
    UCB0CTL1 |= UCSWRST;    // UCSI B0 em ressete
    UCB0CTL0 = UCSYNC |     //Síncrono
               UCMODE_3 |   //Modo I2C
               UCMST;       //Mestre
    UCB0BRW = BR_100K;      //100 kbps
    P3SEL |=  BIT1 | BIT0;  // Use dedicated module
    UCB0CTL1 = UCSSEL_2;    //SMCLK e remove ressete
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

//////////////////////////////////////////////////////
////// Abaixo estão as funções necessárias       /////
//////         para criar as barras              /////
//////  Você deve fornecer a função i2c_write()  /////
//////////////////////////////////////////////////////

// Gerar caracteres especiais
void lcd_barras(void){
    int i;
    lcd_cmdo(0x40);
    for (i=0; i<64; i++)    lcd_char(barras[i]);
    lcd_cmdo(0x80);
}

void lcd_char(char c){
    char msn,lsn;
    msn = c & 0xF0;
    lsn = c << 4;

    i2c_write(msn | 0x9);
    i2c_write(msn | 0xD);
    i2c_write(msn | 0x9);
    i2c_write(lsn | 0x9);
    i2c_write(lsn | 0xD);
    i2c_write(lsn | 0x9);
}

void lcd_cmdo(char c){
    char nib;
    nib=c&0xF0;
    i2c_write(nib|0x8);
    i2c_write(nib|0xC);
    i2c_write(nib|0x8);
    nib=(c<<4)&0xF0;
    i2c_write(nib|0x8);
    i2c_write(nib|0xC);
    i2c_write(nib|0x8);
}

// Função para enviar um  byte para o PCF8574
// Você já deve ter esta função pronta
// Se necessário, seu nome pode ser alterado
void i2c_write(char dado) {
    UCB0I2CSA = PCF_ADR;        //Endereço Escravo
    UCB0CTL1 |= UCTR    |       //Mestre TX
                UCTXSTT;        //Gerar START
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = dado;                               //Escrever dado
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);       //Esperar STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG)        //NACK?
                while(1);                           //Escravo gerou NACK
    UCB0CTL1 |= UCTXSTP;                            //Gerar STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);       //Esperar STOP
}

//////////////////////////////////////////////////////
////// Deste ponto em  diante não será corrigido /////
//////    Coloque abaixo suas demais funções     /////
//////////////////////////////////////////////////////

// Incializar LCD modo 4 bits
void lcd_inic(char adr){

    // Preparar I2C para operar
    UCB0I2CSA = adr;    //Endereço Escravo
    UCB0CTL1 |= UCTR    |   //Mestre TX
                UCTXSTT;    //Gerar START
    while ( (UCB0IFG & UCTXIFG) == 0);          //Esperar TXIFG=1
    UCB0TXBUF = 0;                              //Saída PCF = 0;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);   //Esperar STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG)    //NACK?
                while(1);

    // Começar inicialização
    lcd_aux(0);     //RS=RW=0, BL=1
    delay(20000);
    lcd_aux(3);     //3
    delay(10000);
    lcd_aux(3);     //3
    delay(10000);
    lcd_aux(3);     //3
    delay(10000);
    lcd_aux(2);     //2

    // Entrou em modo 4 bits
    lcd_aux(2);     lcd_aux(8);     //0x28
    lcd_aux(0);     lcd_aux(8);     //0x08
    lcd_aux(0);     lcd_aux(1);     //0x01
    lcd_aux(0);     lcd_aux(6);     //0x06
    lcd_aux(0);     lcd_aux(0xF);   //0x0F

    while ( (UCB0IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
    UCB0CTL1 |= UCTXSTP;                           //Gerar STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP)   ;   //Esperar STOP
    delay(50);
}

// Auxiliar inicialização do LCD (RS=RW=0)
// *** Só serve para a inicialização ***
void lcd_aux(char dado){
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT3;            //PCF7:4 = dado;
    delay(50);
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT3 | BIT2;     //E=1
    delay(50);
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT3;            //E=0;
}


// Função para escrever uma string no lcd
void lcd_str(char *vt){
    unsigned int i=0;
    while( vt[i] != '\0'){
        lcd_char(vt[i++]);
    }
}


void lcd_clear(){
    int i;
    for (i=0; i<16; i++){
        lcd_cursor(0x00+i);
        lcd_char(0x20);    //Espaço
        lcd_cursor(0x40+i);
        lcd_char(0x20);  //Espaço
    }
}

void lcd_apaga_cursor(){
    PCF &= ~BIT0;
    PCF &= ~BIT1;
    i2c_write(PCF);
    i2c_write(0x0C);
    PCF |= BIT0;
    PCF &= ~BIT1;
    i2c_write(PCF);
}

// Função para imprimir uma letra
void lcd_aux_cursor(char x){
    char MSB,LSB;
    MSB= x & 0xf0;
    LSB= x << 4;

    i2c_write(MSB | 0x8);
    i2c_write(MSB | 0xc);
    i2c_write(MSB | 0x8);
    i2c_write(LSB | 0x8);
    i2c_write(LSB | 0xc);
    i2c_write(LSB | 0x8);
}

void lcd_cursor(char x){ // Locomover o cursor
    lcd_aux_cursor(0x80 | (x & 0x7f));
}

char i2c_test(char adr){
    UCB0I2CSA = adr;                     //Endereço a ser testado
    UCB0CTL1 |= UCTR;                   //Mestre TX --> escravo RX
    UCB0CTL1 |= UCTXSTT;                //Gerar START
    while ( (UCB0IFG & UCTXIFG) == 0);      //TXIFG indica que já iniciou START
    UCB0CTL1 |= UCTXSTP;                    //Gerar STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);   //Esperar STOP
    if((UCB0IFG & UCNACKIFG) == 0) return TRUE;     //Chegou ACK
    else                           return FALSE;    //Chegou NACK
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
