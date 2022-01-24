#include <msp430.h> 

char PCF = 0;
int instruct = 0;
int cursor = 0;
int f = 0;


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    return 0;
}

// rs = 0, rw = 0, RS = 1, RW = 1;
void lcd_rs_rw(){
    PCF &= ~BIT0;
    PCF &= ~BIT1;
    writePCF(PCF);
}

void lcd_rs_RW(){
    PCF &= ~BIT0;
    PCF |= BIT1;
    writePCF(PCF);
}

void lcd_RS_rw(){
    PCF |= BIT0;
    PCF &= ~BIT1;
    writePCF(PCF);
}

void lcd_RS_RW(){
    PCF |= BIT0;
    PCF |= BIT1;
    writePCF(PCF);
}

void lcd_E_low(){
    PCF &= ~BIT2;
    writePCF(PCF);
}

void lcd_E_high(){
    PCF |= BIT2;
    writePCF(PCF);
}

void lcd_wr_nib(char nib){
    PCF &= 0xf;
    PCF |= (nib << 4);
    writePCF(PCF);
    lcd_E_high();
    delay(200);
    lcd_E_low();
}

void lcd_wr_byte(char byte){
    char LSB, MSB;

    LSB = byte & 0x0f;
    MSB = byte & 0xf0;
    MSB = MSB >> 4;
    lcd_wr_nib(MSB);
    delay(200);
    lcd_wr_nib(LSB);
    delay(200);
}

void lcd_clear(){ // Limpar lcd
    lcd_rs_rw();
    lcd_wr_byte(0x01);
    cursor = 0;
    lcd_RS_rw();
}

char lcd_rd_nib(void){
    lcd_E_low();
    char data;
    data = readPCF();
    lcd_E_high();
    data = readPCF();
    lcd_E_low();
    data = readPCF();
    return data;
}

char lcd_rd_byte(void){

    char d1, d2;
    d1 = lcd_rd_nib();
    d1 *= 0x10;
    d2 = lcd_rd_nib();
    d1 |= d2;
    return d1;
}

void send_instruction(int instr){ // Não Testado
    lcd_rs_rw();
    PCF |= instr;
    writePCF(PCF);
}

void lcd_00(){ // Zera o lcd inteiro
    PCF = 0;
    writePCF(PCF);
}

void lcdBacklightON(){ // Ligar BackLight
    PCF |= BIT3;
    writePCF(PCF);
}

void lcdBacklightOFF(){// Desligar Back Light
    PCF &= ~BIT3;
    writePCF(PCF);
}

void lcd_cursor(char linha, char coluna){ // faltando para fazer
    char x = 0;
    lcd_rs_rw();
    if(linha == 1) x = 0xC0 + coluna;
    else x = 0x80 + coluna;
    lcd_wr_byte(x);
    lcd_RS_rw();
}

char lcd_ocupado(){// Dizer se o lcd está livre ou não (Não está Funcionando)
    lcd_rs_RW();
    char x = lcd_rd_byte();
    x = x&BIT7;
    lcd_RS_rw();
    if(x == 1) return 1; // ocupado
    return 0; // Livre
}

void lcd_home(){ // Não funciona
    lcd_rs_rw();
    lcd_wr_byte(0x02);
    cursor = 0;
    lcd_RS_rw();
}


void send_char(){ // Enviar byte da tabela ascii
    lcd_RS_rw();
    writePCF(PCF |= 0x04);
    delay(200);
    writePCF(PCF |= 0x01);
    delay(200);
}

void lcd_str(char *s){ // enviar string
    while(*s){
        lcd_pular();
        lcd_wr_byte(*s);
        s++;
    }
}

void lcd_pular(){
    if(cursor == 16){
        lcd_cursor(1,0);
    }
    cursor++;
}

void dec8(unsigned char c){// Pegar o  byte e dar o seu valor em decimal no lcd
    c = 0x30 + c;
    lcd_wr_byte(c);

}
void dec16(unsigned int x){// Pegar a palavra de 16 bits e dar o seus valores em decimal no lcd
    int numero[5];
    int j;
    int l = 0;
    int i = 4;
    int k = 0;
    if(f == 1){
        k = 2;
        i = 2;
    }
    while(k < 5){
        j = pow(10,i);
        j = x / j;
        l = (l * 10);
        numero[k] = j - l;
        l = j;
        if(numero[k] != 0 || f == 1){
            dec8(numero[k]);
            f = 1;
        }
        k ++;
        i--;
    }
    if(f == 0) dec8(0);
    f = 0;
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
    lcd_wr_byte(MSB);
    lcd_wr_byte(LSB);
}
void hex16(unsigned int x){// Pegar a palavra de 16 bits e dar os seus valores em hexadecimal no lcd
    int y = x >> 8;
    x = x & 0x00FF;
    hex8(y);
    hex8(x);
}
void lcd_float(float i){// Pegar o valor recebido e exibir ele com precisão de 3 casas decimais
    int j = i;
    dec16(j);
    lcd_str(",");
    j = (i - j) * 1000;
    f = 1;
    dec16(j);
}

void lcdInic(){ // Inicia o lcd
    lcd_00();
    lcd_rs_rw();

    TA0R = 0;
    while((TA0CCTL0 & CCIFG) == 0);
    TA0CCTL0 &= ~CCIFG;
    lcd_wr_nib(0x3);

    timerA0(4100); //4,1 ms
    TA0R = 0;
    while((TA0CCTL0 & CCIFG) == 0);
    TA0CCTL0 &= ~CCIFG;
    lcd_wr_nib(0x3);

    timerA0(100); //100 us
    TA0R = 0;
    while((TA0CCTL0 & CCIFG) == 0);
    TA0CCTL0 &= ~CCIFG;
    lcd_wr_nib(0x3);

    delay(100);
    lcd_wr_nib(0x2);
    delay(100);
    lcd_wr_byte(0x2C);
    delay(100);
    lcd_wr_byte(0xC);
    delay(100);
    lcd_wr_byte(0x1);
    delay(100);
    lcd_wr_byte(0x6);
    delay(100);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void timerA0(int time){
    TA0CCR0 = time;
}
