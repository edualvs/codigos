//Luiz Eduardo Alves da Costa
//190112701
//Lista de ordenação - Questão 5 - Selection Sort

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main (){
	string nome, aux;
	vector <string> strings;
	int tam, i, j, min;
	cout << "Digite quantos nomes deseja digitar:" << endl;
	cin >> tam;
	//Lendo os valores do vetor de strings	
	for (i = 0; i < tam; i++){
		cin >> nome;
		strings.push_back(nome);
	}
	
	//Selection Sort
	for (i = 0; i < strings.size() - 1; i++){
		min = i;
			for (j = i+1; j < strings.size(); j++){
				//If que compara o tamanho de cada string do vetor
				if(strings[j].size() < strings[min].size()){
					min = j;
				}
			}
			aux = strings[i];
			strings[i] = strings[min];
			strings[min] = aux;
	}
	
	//Imprimindo o vetor de strings ordenado
	for (i = 0; i < strings.size(); i++){
		cout << strings[i] << endl;
	}
	return 0;
}
