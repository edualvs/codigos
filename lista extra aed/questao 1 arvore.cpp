#include <iostream>
#include <set>
using namespace std;

void Add (set<string> &a)
{
	string nome;
	cout << "Digite o nome que deseja adicionar a familia:" << endl;
	cin.ignore();
	getline (cin,nome);
	a.insert(nome);
}
void Exclui (set<string> &a)
{
	string nome;
	cout << "Digite o nome que deseja excluir da familia:" << endl;
	cin.ignore();
	getline (cin,nome);
	
}

int main (){
	set<string> familia;
	int n;
	while(1)
	{
		system("cls");
		do
		{
			cout << "Escolha uma opção: " << endl;
			cout << "1. Adicionar novo membro da familia" << endl;
			cout << "2. Excluir membro" << endl;
			cout << "3. Mudar o nome do membro" << endl;
			cout << "4. Procurar por um membro" << endl;
			cout << "5. Sair do programa" << endl;
			cin >> n;		
		}
		while(n<0 || n>5);
	
		switch(n)
		{
			case 1:
				break;
				Add(familia);
			case 2:
				break;;
				
			case 3:
				break;
				
			case 4:
				break;
				
			default: 
				return 0;
		}
		system("pause");
	};

	return 0;
}
