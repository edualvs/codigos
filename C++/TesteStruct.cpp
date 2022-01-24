#include <iostream>
#include <vector>
using namespace std;

struct Pessoa {
	   string nome;
	   int cpf;
	   string endereco;	
	};

int main() {	
	Pessoa pessoa;
	vector<Pessoa> pessoas;
    vector<Pessoa>::iterator it;
	cout << "******  Cadastro *******\n";
	cout << "Digite o nome da pessoa\n";
	cin >> pessoa.nome;
	cout << "Digite o CPF\n";
	cin >> pessoa.cpf;
	cout << "Digite o endereco\n";
	cin >> pessoa.endereco;
	pessoas.push_back(pessoa);
	pessoa.nome=pessoa.nome+"*";
	pessoas.push_back(pessoa);
	it=pessoas.begin();
	cout << "Dados digitados\n";
	cout << it->nome << " " << it->cpf << " " << it->endereco << "\n";
	it++;
    cout << it->nome << " " << it->cpf << " " << it->endereco;
	return 0;
}
