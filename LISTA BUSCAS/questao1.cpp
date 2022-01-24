// Luiz Eduardo Alves da Costa
// 190112701
// Questão 1
#include <iostream>
#include <locale.h>
#include <vector>
using namespace std;

int main (){
	setlocale (LC_ALL,"Portuguese");
	int tam;
	vector<int> vet;
	
	// Pedindo ao usuário o tamanho do vetor
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
	
	system ("cls");// Limpando a tela
	
	// Printando os elementos do vetor
	cout << "Elementos do vetor:" << endl;
	for (int i=0; i<tam; i++){
		cout << vet[i] << endl;
	}
	return 0;
}


