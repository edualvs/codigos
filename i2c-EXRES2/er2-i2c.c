#include <msp430.h> 
#include <USCI_B1.h>

void i2c_config(void);
void leds_config(void);
void led_vm_acesso(void);
void led_vd_acesso(void);

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	i2c_config();
	USCI_B1_config();
	leds_config();
	UCB0I2CSA = 42;//Endereço do escravo

	UCB0CTL1 = UCTR | UCTXSTT;
	while((UCB0IFG&UCTXIFG) == 0);
	UCB0CTL1 |= UCTXSTP;
	while((UCB0CTL1&UCTXSTP) != UCTXSTP);
	
	if((UCB0IFG & UCNACKIFG) == 0) led_vd_acesso();
	else led_vm_acesso();
	while(1);
}

void i2c_config(void){
    UCB0CTL1 |= UCSWRST; //Reset=1

    UCB0CTL0 =  UCSYNC | //Modo Síncrono
                UCMODE_3 | //I2C
                UCMST; //Mestre

    UCB0BRW = 105; //10 kbps
    UCB0CTL1 = UCSSEL__SMCLK; // SMCLK

    P3SEL |= BIT1 | BIT0;
    P3REN |= BIT1|BIT0;
    P3OUT |= BIT1|BIT0;
}

void led_vm_acesso(void){   P1OUT |= BIT0;   }
void led_vd_acesso(void){   P4OUT |= BIT7;   }

void leds_config(){
    P1DIR |= BIT0;
    P4DIR |= BIT7;
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT7;
}
