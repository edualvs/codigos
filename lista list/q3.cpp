// Luiz Eduardo Alves da Costa
// 190112701
// Questão 3
#include <iostream>
#include <list>
#include <string>
#include <locale.h>
using namespace std;

class ListaAviao {
	public:
	list <string> lista;
	ListaAviao(){};
	ListaAviao(string aviao){
		this->lista.push_back(aviao);
	}
	void ListaNum();
	void AutorizaDecolagem ();
	void AdicionaNaFila(string &aviao);
	void MostraFila ();
	void AtributosAviao ();
};
int main (){
	setlocale(LC_ALL,"Portuguese");
	int n;
	ListaAviao Lst;
	while(1){
	do{
	cout << "Escolha uma opção:" << endl;
	cout << "1. Mostrar o número de aviões na fila" << endl;
	cout << "2. Autorizar uma decolagem" << endl;
	cout << "3. Adicionar um avião a fila" << endl;
	cout << "4. Exibir a Lista de aviões na fila" << endl;
	cout << "5. Mostrar os atributos do primeiro avião" << endl;
	cin >> n;
	}
	while(n<0 || n>5);
	string aviao;
	int posicao;
	switch(n){
		case 1:
			Lst.ListaNum();
			break;
		case 2:
			Lst.AutorizaDecolagem();
			break;
		case 3:
			cin >> aviao;
			Lst.AdicionaNaFila(aviao);
			break;
		case 4:
			Lst.MostraFila();
			break;
		default:
			Lst.AtributosAviao();
			break;
	}
system("pause");
system("cls");
}
	return 0;
}

void ListaAviao::ListaNum (){
		cout << "Existem " << lista.size() << " aviões na fila." << endl;
	}


void ListaAviao::AutorizaDecolagem (){
	int n;
	cout << "Digite 1 para autorizar a decolagem ou 0 para não autorizar:" << endl;
	cin >> n;
	if (n==1){
		cout << "Decolagem autorizada!" << endl;
		cout << "O avião " << lista.front() << " decolou!" <<  endl;
		lista.pop_front();
	}
		else if (n==0){
			cout << "Decolagem não autorizada!" << endl;
		}
			else {
				cout << "Entrada inválida!" << endl;
			}
}

void ListaAviao::AdicionaNaFila(string &aviao){
	lista.push_back(aviao);
}

void ListaAviao::MostraFila (){
	list<string>::iterator it;
	for(it=lista.begin();it!=lista.end();it++){
		cout << *it << "\t";
	}
}

void ListaAviao::AtributosAviao(){
	
}

