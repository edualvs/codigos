// Luiz Eduardo Alves da Costa
// 190112701
// Questão 3
#include <iostream>
#include <locale.h>
using namespace std;

// Busca linear
int pesqseq (int val, int vet[],int tam){
	for (int i=0; i<tam; i++){
		if (val==vet[i])
			return i;
	}
	return -1;
}

int main (){
	setlocale (LC_ALL,"Portuguese");
	int tam,n,res,aux;
	
	// Pedindo ao usuário o tamanho do vetor
	cout << "Digite o tamanho do vetor: ";
	cin >> tam;
	int vet[tam];
	
	// Preenchendo o vetor
	cout << "\nDigite os valores do vetor:" << endl;
	for (int i=0; i<tam; i++){
		cin >> vet[i];
	}
	
	// Printando o vetor
	cout << "Vetor:\n";
	for (int x=0; x<tam; x++){
		cout << vet[x] << "\t";
	}
	
	// Utilizando a função pesqseq para encontrar o valor digitado pelo usuário
	cout << "\nDigite o valor deseja encontrar no vetor: ";
	cin >> n;
	res = pesqseq(n,vet,tam);
	if (res!=-1){
		cout << "O valor " << n << " está na posição " << res+1 <<" do vetor" << endl;
	}
	else
		cout << n << " não está no vetor!" << endl;	
	return 0;
}
