// Luiz Eduardo Alves da Costa
// 190112701
// Quest�o 8
#include <iostream>
#include <locale.h>
using namespace std;

int main (){
	setlocale (LC_ALL,"Portuguese");
	
	int n,i,maior,posmaior;
	
	
	cout << "Digite o tamanho do vetor:";
	cin >> n;
	int X[n];
	
	//Lendo os valores do vetor
	cout << "Digite os elementos do vetor:" << endl;
	for(i=0;i<n;i++){
		cout << "[P"<< i+1<<"]->";
		cin >> X[i];
	}
	
	
	maior=X[0]; //setando o maior como o primeiro elemento do vetor
	posmaior=0; //setando a posi��o inicial 0
	
	//Procurando o maior e sua posi��o
	for(i=1;i<n;i++){
		if(X[i]>maior){
		maior=X[i];
		posmaior=i;
		}
	}
	
	//Printando o maior valor e sua posi��o
	cout << "Maior valor: " << maior << " Posi��o: " << posmaior+1 << endl; 
	return 0;
}
