//Luiz Eduardo Alves da Costa
//190112701
//Lista de ordenação - Questão 1 - Insertion Sort
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Insertion Sort
void insertionSort (vector<string> &strings){
	string aux;
	int i , j;
	for (i = 0; i < strings.size();i++){
		j = i;
		while(j > 0 && strings[j-1] > strings[j]){
			aux = strings[j-1];
			strings[j-1] = strings[j];
			strings[j] = aux;
			j--;
		}
	}
}
int main (){
	string nome;
	vector <string> strings;
	int tam,i;
	cout << "Quantos nomes serao digitados?" << endl;
	cin >> tam;
	//Lendo os valores do vetor de string
	for (i=0; i < tam; i++){
		cin >> nome;
		strings.push_back(nome);
	}
	//Chamando a função de ordenação
	insertionSort (strings);
	
	cout << "Nomes em ordem alfabetica: " << endl;
	
	//Imprimindo o vetor de string ordenado
	for (i=0; i < strings.size(); i++){
		cout << strings[i] << "\t";
	}
	return 0;
}
