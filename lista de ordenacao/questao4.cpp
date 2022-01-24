//Luiz Eduardo Alves da Costa
//190112701
//Lista de ordena��o - Quest�o 4 - Bubble Sort

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>

//Algoritmo do bubble sort
void bubbleSort (float *vet, int N){
	int i, continua, fim = N;
	float aux;
	do{
		continua = 0;
		for (i=0; i < fim-1; i++){
			if (vet[i] > vet[i+1]){
				aux = vet[i];
				vet[i] = vet[i+1];
				vet[i+1] = aux;
				continua = i;
			}
		}
	}while (continua != 0);
}

using namespace std;


int main (){
	float vetor[100],temp;
	srand(time(NULL));//Gerador de n�mero aleat�rio ao longo do tempo
	for (int i=0;i<100;i++){
		temp = (float)rand()/(RAND_MAX+1)+1+(rand()%2);//Especificando o intervalo do meu n�mero aleat�rio
		vetor[i]=temp;
	}
	
	bubbleSort(vetor,100);//Chamando a fun��o de ordena��o
	
	for (int i=0;i<100;i++){
		cout << fixed;//Escrevendo o valor do float em nota��o de ponto fixo
		cout << setprecision(2);//Setar a precis�o com 2 casas decimais(fun��o da biblioteca iomanip)
		cout << vetor[i] << endl;//Imprimindo o vetor ordenado
	}
	return 0;
}
