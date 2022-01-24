//Luiz Eduardo Alves da Costa
//190112701
//Lista de ordenação - Questão 3 - Merge Sort
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Pessoa{
	int Matricula;
	char Nome[30];
	float Nota;
};

int main (){
	Pessoa pessoa;
	int N,i=0;
	vector <Pessoa> dados;
	
	cout << "Quantas pessoas deseja cadastrar?" << endl;
	cin >> N;
	
	while (i<N){
		cout << "Matricula " << i + 1 << ":" << endl;
		cin >> pessoa.Matricula;
		cout << "Nome " << i + 1 << ":" << endl;
		cin >> pessoa.Nome;
		cout << "Nota " << i + 1 << ":" << endl;
		cin >> pessoa.Nota; 
		dados.push_back(pessoa);
		i = i + 1;
	}

	cout << endl;
	return 0;
}
