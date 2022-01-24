// Luiz Eduardo Alves da Costa
// 190112701
// Questão 10
#include <iostream>
#include <locale.h>
using namespace std;

// Busca binária posição
	int pesqbin (int vet[],int tam,int val){
    int begin = 0;
    int end = tam - 1;
    while (begin <= end) {
        int i = (begin + end) / 2;  

        if (vet[i] == val) { 
            return i;
        }

        if (vet[i] < val) {  
            begin = i + 1;
        } else {  
            end = i;
        }
    }
    return -1;
}

// Busca binária pesquisas
	int pesqbin1 (int vet[],int tam,int val){
    int begin = 0;
    int end = tam - 1;
	int cont;
    while (begin <= end) { 
    	cont++;
        int i = (begin + end) / 2;  

        if (vet[i] == val) { 
            return cont;
        }

        if (vet[i] < val) {  
            begin = i + 1;
        } else {  
            end = i;
        }
    }
    return -1;
}

int main (){
	setlocale (LC_ALL,"Portuguese");
		int vet[10],temp,pos,numpesq,val;

	cout << "Preencha o vetor com valores:" << endl;
	for (int i=0;i<10;i++){
		cout << "P[" << i << "]: ";
		cin >> vet[i];
	}
	
	cout << "Digite o valor que deseja procurar no vetor: ";
	cin >> val;
	pos=pesqbin(vet,10,val);
	numpesq=pesqbin1(vet,10,val);
	
	if(pos!=-1){
		cout << val <<" está na posição: " << pos+1 << endl;
		cout << numpesq << " pesquisas foram feitas." << endl;
	}
	else
		cout << val <<" não está no vetor!" << endl;	
	return 0;
}
