// ER 9.1 - USCI_B1.h
// USCI_B1_Header
// Defini��es para USCI_B1
#ifndef USCI_B1_H_
#define USCI_B1_H_
#define MAX_B1 10 //Tamanho do vetor para receber dados

// Prot�tipo das fun��es
void USCI_B1_config(void);
void USCI_B1_rx(void);
void USCI_B1_tx(void);

// Vari�veis globais
volatile char b1_vet[MAX_B1]; //Vetor para receber dados
volatile char b1; //Indexador para o vetor
volatile char b1_cont; //Contador para transmitir
#endif /* USCI_B1_H_ */
