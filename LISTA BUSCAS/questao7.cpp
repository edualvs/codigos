// Luiz Eduardo Alves da Costa
// 190112701
// Quest�o 7
#include <iostream>
#include <locale.h>
using namespace std;

int main (){
	setlocale (LC_ALL,"Portuguese");
	
	int n,i,menor,posmenor
	
	cout << "Digite o tamanho do vetor:";
	cin >> n;
	int X[n];
	
	//Lendo os valores do vetor
	cout << "Digite os elementos do vetor:" << endl;
	for(i=0;i<n;i++){
		cout << "[P"<< i+1<<"]->";
		cin >> X[i];
	}
	
	menor=X[0]; //setando o menor como o primeiro elemento do vetor
	posmenor=0; //setando a posi��o inicial 0
	
	//Procurando o menor e sua posi��o
	for(i=1;i<n;i++){
		if(X[i]<menor){
		menor=X[i];
		posmenor=i;
		}
	}
	
	//Printando o maior valor e sua posi��o
	cout << "Menor valor: " << menor << " Posi��o: " << posmenor+1 << endl; 
	return 0;
}
