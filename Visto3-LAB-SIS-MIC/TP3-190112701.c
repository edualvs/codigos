//Luiz Eduardo Alves da Costa
//Matrícula 190112701
#include <msp430.h> 

#define TRUE    1
#define FALSE   0
#define FECHADA 0 //SW fechada
#define ABERTA 1 //SW aberta

// Caracteres especiais para o LCD
char barras[64]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,   //0
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F,   //1
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F,   //2
                  0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F,   //3
                  0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,   //4
                  0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,   //5
                  0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,   //6
                  0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};  //7

// Definição do endereço do PCF_8574
#define PCF_ADR1 0x3F //Possíveis endereços do lcd
#define PCF_ADR2 0x27 //Possíveis endereços do lcd

#define PCF_ADR  PCF_ADR2 //Endereço do lcd usado

#define BR_100K    11  //SMCLK/100K = 11
#define BR_50K     21  //SMCLK/50K  = 21
#define BR_10K    105  //SMCLK/10K  = 105

void lcd_str(char *vt);//Imprime string no lcd
void lcd_char(char x);//Imprime char no lcd
void lcd_inic(void);//Inicializa o lcd
void lcd_aux(char dado);//Auxilia a inicialização do lcd
void lcd_aux_cursor(char x);
void lcd_clear(void);//Limpa lcd
void lcd_cursor(char x);//Posiciona o cursor
void led_dec8(char x);// Imprimir número de 8 bits
void hex8(unsigned char c);// Transforma o byte e dar o seu valor em hexadecimal no lcd
void hex16(unsigned int x);// Pegar a palavra de 16 bits e dar os seus valores em hexadecimal no lcd
void lcd_float(float x);//Imprime float com três casas decimais
void pcf_write(char dado);//Escreve dado
void func1(void);//Modo 1
void func2(void);//Modo 2
void func3(void);//Modo 3
void func4(void);//Modo 4


void lcd_barras(void);
void pblcd_cmdo(char c);
void pblcd_char(char c);


void delay(long limite);//Delay
int sw_mon(void);//Monitorar chave do joystick

void adc_config(void);//Configura AD
void ta0_config(void);//Configurar Timer A0
void i2c_config(void);//Configurar comunicação I2C
void gpio_config(void);//Configura leds e chave sw do joystick

//Variáveis globais
volatile unsigned int media_x, media_y;//Médias
volatile float tensao_x,tensao_y,passo_x,passo_y;//Tensão e Passo(Para o modo 2 e 3)
char PCF;
int cursor = 0;
int n=0,i=0;//Variáveis de loops
char j=0;
volatile int barras_x,barras_y;//Variáveis Modo 2,3 e 4
volatile char posicao_x,posicao_y;
volatile int arr_x[3],arr_y[3],aux1_x,aux2_x,aux1_y,aux2_y;//Variáveis da interrupção do AD para calcular a posição no modo 4

void main(void)
{
    int cont=0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	adc_config();
	ta0_config();
	i2c_config();
	gpio_config();

	__enable_interrupt();       //Habilita interrupções
	lcd_inic();                 //Inicializar LCD

    while(TRUE){
        if(sw_mon() == TRUE){
            cont++;
            if(cont==4) cont=0;//4 modos
        }

        switch (cont) {
            case 0:
                func1();//Modo 1
                break;
            case 1:
                func2();//Modo 2
                break;

            case 2:
                func3();//Modo 3
                break;

            case 3:
                func4();//Modo 4
                break;

            default:
                break;
        }
    }
}

void func1(){
    //LINHA 1 = l1 COLUNA 1 = c1

    //Linha 1 (A0)
    lcd_cursor(0x00);       //Cursor: l1 c1
    lcd_str("A0:");         //Mostra "A0:"
    lcd_cursor(0x05);       //Cursor l1 c5
    lcd_float(tensao_x);    //Mostra tensão no eixo x
    lcd_cursor(0x09);       //Cursor l1 c9
    lcd_char('V');          //Mostra "V"
    lcd_cursor(0x0C);       //Cursor l1 c12
    hex16(media_x);         //Mostra média x em hexadecimal

    //Linha 2 (A1)
    lcd_cursor(0x40);       //Cursor: l2 c1
    lcd_str("A1:");         //Mostra "A1:"
    lcd_cursor(0x45);       //Cursor l2 c5
    lcd_float(tensao_y);    //Mostra tensão no eixo y
    lcd_cursor(0x49);       //Cursor l2 c9
    lcd_char('V');          //Mostra "V"
    lcd_cursor(0x4C);       //Cursor l2 c12
    hex16(media_y);         //Mostra média y em hexadecimal
}

void func2(){
    //LINHA 1 = l1 COLUNA 1 = c1

    //Linha 1 (A0)
    lcd_cursor(0x00);       //Cursor: l1 c1
    lcd_str("A0:");         //Mostra "A0:"
    lcd_cursor(0x05);       //Cursor l1 c5
    lcd_float(tensao_x);    //Mostra tensão no eixo x
    lcd_cursor(0x09);       //Cursor l1 c9
    lcd_char('V');          //Mostra "V"
    lcd_cursor(0x0C);       //Cursor l1 c12
    hex16(media_x);         //Mostra média x em hexadecimal

    //Linha 2 (Barra horizontal)
    lcd_cursor(0x40);                   //Cursor: l2 c1
    for(n=0; n<=barras_x; n++){         //Percorre espaço a preencher
        lcd_char(0xFF);                 //Preenche espaço
    }
    for(n=0; n<(16-barras_x);n++){      //Percorre espaço a deixar em branco
        lcd_char(0x20);                 //Espaço vazio
    }
}

void func3(){
    //LINHA 1 = l1 COLUNA 1 = c1

    //Linha 1 (A1)
    lcd_cursor(0x00);       //Cursor: l1 c1
    lcd_str("A1:");         //Mostra "A1:"
    lcd_cursor(0x05);       //Cursor l1 c5
    lcd_float(tensao_y);    //Mostra tensão no eixo y
    lcd_cursor(0x09);       //Cursor l1 c9
    lcd_char('V');          //Mostra "V"
    lcd_cursor(0x0C);       //Cursor l1 c12
    hex16(media_y);         //Mostra média y em hexadecimal

    //Linha 2 (Barra horizontal)
    lcd_cursor(0x40);                   //Cursor: l2 c1
    for(n=0; n<=barras_y; n++){         //Percorre espaço a preencher
        lcd_char(0xFF);                 //Preenche espaço
    }
    for(n=0; n<(16-barras_y);n++){      //Percorre espaço a deixar em branco
        lcd_char(0x20);                 //Espaço vazio
    }
}

void func4(){
    //LINHA 1 = l1 COLUNA 1 = c1

    lcd_clear();//Limpa lcd

    posicao_x = arr_x[2]/256;                 //Calcula posição de C(n-2)
    lcd_cursor(posicao_x);                          //Cursor l1 c(posição_x)
    lcd_char('-');                                  //Mostra "-"

    posicao_x = arr_x[1]/256;                 //Calcula posição de C(n-1)
    lcd_cursor(posicao_x);                          //Cursor l1 c(posição_x)
    lcd_char('=');                                  //Mostra "="

    posicao_x = arr_x[0]/256;                 //Calcula posição de C(n)
    lcd_cursor(posicao_x);                          //Cursor l1 c(posição_x)
    if(arr_x[0] > arr_x[1] && arr_x[0]>arr_x[2]){   //C(n) > C(n-2) E C(n) > C(n-1)
        lcd_char('>');                              //Mostra ">"
    }
    else if((arr_x[0] < arr_x[1]) && (arr_x[0] < arr_x[2])){    //C(n) < C(n-2) E C(n) < C(n-1)
        lcd_char('<');                              //Mostra "<"
    }
    else if (((arr_x[0] < arr_x[1]) && (arr_x[0] > arr_x[2])) || ((arr_x[0] > arr_x[1]) && (arr_x[0] < arr_x[2]))){ //C(n) entre C(n-2) e C(n-1)
        lcd_char('#');                              //Mostra "#"
    }

    posicao_y = arr_y[2]/256;                 //Calcula posição de C(n-2)
    lcd_cursor(posicao_y+0x40);                     //Cursor l2 c(posição_y)
    lcd_char('-');                                   //Mostra "-"

    posicao_y = arr_y[1]/256;                 //Calcula posição de C(n-1)
    lcd_cursor(posicao_y+0x40);                     //Cursor l2 c(posição_y)
    lcd_char('=');                                  //Mostra "="

    posicao_y = arr_y[0]/256;                 //Calcula posição de C(n)
    lcd_cursor(posicao_y+0x40);                     //Cursor l2 c(posição_y)
    if((arr_y[0] > arr_y[1]) && (arr_y[0]>arr_y[2])){   //C(n) > C(n-2) E C(n) > C(n-1)
        lcd_char('>');                              //Mostra ">"
    }
    else if((arr_y[0] < arr_y[1]) && (arr_y[0] < arr_y[2])){    //C(n) < C(n-2) E C(n) < C(n-1)
        lcd_char('<');                              //Mostra "<"
    }
    else if (((arr_y[0] < arr_y[1]) && (arr_y[0] > arr_y[2])) || ((arr_y[0] > arr_y[1]) && (arr_y[0] < arr_y[2]))){ //C(n) entre C(n-2) e C(n-1)
        lcd_char('#');                              //Mostra "#"
    }
}

//#pragma vector = 54
#pragma vector = ADC12_VECTOR
__interrupt void adc_interrupt(void){
     volatile unsigned int *pt;
     unsigned int i,soma;
     P1OUT ^= BIT0;//Invertendo led vermelho a cada atualização do lcd
     pt = &ADC12MEM0;
     soma = 0;
     for (i=0; i<8; i++) soma +=pt[i];

     media_x = soma >> 3;
     soma = 0;

     for (i=8; i<16; i++) soma +=pt[i];
     media_y = soma >>3;

     tensao_x = (media_x*3.3)/4095;
     tensao_y = (media_y*3.3)/4095;

     passo_x = 3.3/16;
     passo_y = 3.3/16;
     barras_x = tensao_x/passo_x;
     barras_y = tensao_y/passo_y;

     aux1_x=arr_x[0];
     aux2_x=arr_x[1];
     arr_x[1]=aux1_x;
     arr_x[2]=aux2_x;
     arr_x[0]=media_x;

     aux1_y=arr_y[0];
     aux2_y=arr_y[1];
     arr_y[1]=aux1_y;
     arr_y[2]=aux2_y;
     arr_y[0]=media_y;

}

void adc_config(){
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
            pt[i]=ADC12SREF_0 | ADC12INCH_0; //A0

    for (i=8; i<16; i++)
            pt[i]=ADC12SREF_0 | ADC12INCH_1;//A1


    pt[15] |= ADC12EOS;//EOS em ADC12MCTL15

    P6SEL |= BIT1|BIT0; // Desligar digital de P6.1,0
    ADC12CTL0 |= ADC12ENC; //Habilitar ADC12
    ADC12IE |= ADC12IE15; //Hab interrupção MEM15
}

void ta0_config(){
    TA0CTL = TASSEL__ACLK | MC_1;
    TA0CCTL1 = OUTMOD_6; //Out = modo 6
    TA0CCR0 = 3276/16; //16 Hz (8 Hz por canal)
    TA0CCR1 = TA0CCR0/2; //Carga 50%
}


// Configurar UCSB0 e Pinos I2C
// P3.0 = SDA e P3.1=SCL
void i2c_config(void){
    UCB0CTL1 |= UCSWRST;    // UCSI B0 em ressete
    UCB0CTL0 = UCSYNC |     //Síncrono
               UCMODE_3 |   //Modo I2C
               UCMST;       //Mestre
    UCB0BRW = BR_100K;      //100 kbps
    P3SEL |=  BIT1 | BIT0;  // Use dedicated module
    UCB0CTL1 = UCSSEL_2;    //SMCLK e remove ressete
}

void lcd_clear(){
    for (i=0; i<16; i++){
        lcd_cursor(0x00+i);
        lcd_char(0x20);    //Espaço
        lcd_cursor(0x40+i);
        lcd_char(0x20);  //Espaço
    }
}

// Função para imprimir uma letra
void lcd_aux_cursor(char x){
    char MSB,LSB;
    MSB= x & 0xf0;
    LSB= x << 4;

    pcf_write(MSB | 0x8);
    pcf_write(MSB | 0xc);
    pcf_write(MSB | 0x8);
    pcf_write(LSB | 0x8);
    pcf_write(LSB | 0xc);
    pcf_write(LSB | 0x8);
}

void lcd_cursor(char x){ // Locomover o cursor
    lcd_aux_cursor(0x80 | (x & 0x7f));
}

// Gerar caracteres especiais
void lcd_barras(void){
    int i;
    pblcd_cmdo(0x40);
    for (i=0; i<64; i++)    pblcd_char(barras[i]);
    pblcd_cmdo(0x80);
}

void pblcd_char(char c){
    char nib;
    nib=c&0xF0;
    pcf_write(nib|0x9);
    pcf_write(nib|0xD);
    pcf_write(nib|0x9);
    nib=(c<<4)&0xF0;
    pcf_write(nib|0x9);
    pcf_write(nib|0xD);
    pcf_write(nib|0x9);
}

void pblcd_cmdo(char c){
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

// Imprimir número de 8 bits
void lcd_dec8(char x){
    char z;

    z=x/100;    //separar centena
    lcd_char(0x30+z);

    x=x-100*z;
    z=x/10;     //separar dezena
    lcd_char(0x30+z);

    x=x-10*z;
    lcd_char(0x30+x);
}

void lcd_float(float x){// Pegar o valor recebido e exibir ele com precisão de 3 casas decimais
    char z;
    x=x*1000;

    z=x/1000;    //separar unidade de milhar
    lcd_char(0x30+z);

    lcd_char(',');//Char ",'

    x=x-1000*z;

    z=x/100;    //separar centena
    lcd_char(0x30+z);

    x=x-100*z;

    z=x/10;     //separar dezena
    lcd_char(0x30+z);

    x=x-10*z;

    lcd_char(0x30+x);
}

void hex8(unsigned char c){// Pegar o byte e dar o seu valor em hexadecimal no lcd
    char MSB, LSB;

    MSB = c & 0xF0;
    MSB = MSB >> 4;
    LSB = c << 4;
    LSB = LSB >> 4;
    if(MSB > 0x09) MSB = 0x37 + MSB;
    else MSB = 0x30 + MSB;
    if(LSB > 0x09) LSB = 0x37 + LSB;
    else LSB = 0x30 + LSB;
    lcd_char(MSB);
    lcd_char(LSB);
}

void hex16(unsigned int x){// Pegar a palavra de 16 bits e dar os seus valores em hexadecimal no lcd
    int y = x >> 8;
    x = x & 0x00FF;
    hex8(y);
    hex8(x);
}

// Função para escrever uma string no lcd
void lcd_str(char *vt){
    unsigned int i=0;
    while( vt[i] != '\0'){
        lcd_char(vt[i++]);
    }
}

// Função para imprimir uma letra
void lcd_char(char x){
    char msn,lsn;
    msn = x & 0xF0;
    lsn = x << 4;

    pcf_write(msn | 0x9);
    pcf_write(msn | 0xD);
    pcf_write(msn | 0x9);
    pcf_write(lsn | 0x9);
    pcf_write(lsn | 0xD);
    pcf_write(lsn | 0x9);
}

// Incializar LCD modo 4 bits
void lcd_inic(void){

    // Preparar I2C para operar
    UCB0I2CSA = PCF_ADR;    //Endereço Escravo
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

// Escrever dado na porta
void pcf_write(char dado){
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

void delay(long limite){
    volatile long cont=0;
    while (cont++ < limite);
}

// Configurar leds
void gpio_config(void){
    P1DIR |=  BIT0;      //Led vermelho
    P1OUT &= ~BIT0;      //Vermelho Apagado
    P4DIR |=  BIT7;      //Led verde
    P4OUT &= ~BIT7;      //Verde Apagado

    P6DIR &= ~BIT2;      //P6.2 = SW
    P6REN |= BIT2;
    P6OUT |= BIT2;
}

// Monitorar SW (P6.2), retorna TRUE se foi acionada
int sw_mon(void){
     static int psw=ABERTA; //Guardar passado de Sw
     if ( (P6IN&BIT2) == 0){ //Qual estado atual de Sw?
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
