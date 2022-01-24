// Luiz Eduardo Alves da Costa
// 190112701
// Questão 9
#include <iostream>
#include <locale.h>
using namespace std;

int main (){
	setlocale (LC_ALL,"Portuguese");
	
	int vet[10],temp;

	cout << "Preencha o vetor com valores:" << endl;
	for (int i=0;i<10;i++){
		cout << "P[" << i << "]: ";
		cin >> vet[i];
	}
	
	//Ordenação do vetor (decrescente)
	for(int i=0;i<10;i++){		
		for(int j=i+1;j<10;j++){
			if(vet[i]<vet[j])
			{
				temp  =vet[i];
				vet[i]=vet[j];
				vet[j]=temp;
			}
		}
	}
	
	//Printando o vetor ordenado
	cout << "Vetor Ordenado:" << endl;
	for(int i=0;i<10;i++){
		cout << vet[i] << " | ";
	}
	
	return 0;
}
