// Luiz Eduardo Alves da Costa
// 190112701
// Questão 2
#include <iostream>
#include <locale.h>
#include <vector>
using namespace std;

int main (){
	setlocale (LC_ALL,"Portuguese");
	int tam,temp;
	vector<int> vet;
	// Pedindo ao usúario o tamanho do vetor
	cout << "Qual o tamanho do vetor? ";
	cin >> tam;
	
	system ("cls"); // Limpando a tela
	
	// Preenchendo o vetor
	cout << "Digite os elementos do vetor!" << endl;
	for (int i=0; i<tam; i++){
		int num;
		cin >> num;
		vet.push_back(num);
	}
	
	system ("cls"); // Limpando a tela
	
	// Mostrando na tela os elementos do vetor sem ordenar
	cout << "Elementos do vetor sem ordenar:" << endl;
	for (int i=0; i<tam; i++){
		cout << vet[i] << " | ";
	}
	
	system ("pause"); // Dando um pause no programa para visualização do vetor em ordenar
	system ("cls"); // Limpando a tela
	
	// Ordenando os elementos do vetor em ordem crescente
	cout << "Elementos do vetor ordenados:" << endl;
	for(int i=0;i<vet.size();i++){		
		for(int j=i+1;j<vet.size();j++){
			if(vet[i]>vet[j])
			{
				temp  =vet[i];
				vet[i]=vet[j];
				vet[j]=temp;
			}
		}
	}
	
	// Printando na tela o vetor ordenado
	for (int i=0; i<tam; i++){
		cout << vet[i] << " | ";
	}
	
	return 0;
}
