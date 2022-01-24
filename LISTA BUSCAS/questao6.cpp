// Luiz Eduardo Alves da Costa
// 190112701
// Questão 6
#include <iostream>
#include <locale.h>
using namespace std;

// Busca linear
int pesqseq (int val, int vet[],int tam){
	 int cont;
	for (int i=0; i<tam; i++){
		cont++;
		if (val==vet[i])
			return cont;
	}
	return -1;
}

// Busca binária
	int pesqbin (int vet[],int tam,int val){
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

// Busca com Sentinela
int pesqseqsent (int val, int vet[],int tam){
	int i,sentinela,cont;
	sentinela=val;
	vet[tam+1] = sentinela;
		for (i=0; vet[i]!=sentinela ;i++ ){
		cont++;
		}
			if((i!=tam+1) && (vet[i] == val))
				return cont;
		return -1;
	}

int main (){
	setlocale (LC_ALL,"Portuguese");
	int tam,res,res1,res2,n;
	
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
	
	// Passando o return de cada função para as variáveis res
	res = pesqseq(n,vet,tam);
	res1 = pesqbin(vet,tam,n);
	res2 = pesqseqsent(n,vet,tam);
	
	
	cout << "A pesquisa senquencial pesquisou " << res << " vezes até encontrar o valor " << n << endl;
	cout << "A pesquisa binária pesquisou " << res1 << " vezes até encontrar o valor " << n << endl;
	cout << "A pesquisa senquencial com sentinela pesquisou " << res2 << " vezes até encontrar o valor " << n << endl;
	
	
	return 0;
}
