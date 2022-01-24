// Luiz Eduardo Alves da Costa
// 190112701
// Questão 1
#include <iostream>
#include <list>
#include <locale.h>

using namespace std;

int main (){
	setlocale (LC_ALL, "Portuguese");
	int tam1,tam2,elem1,elem2;
	bool check1=true,check2=true;
	list<int> lista1,lista2;
	list<int>::iterator it1,it2,it3,it4;
	
	//Perguntando o tamanho da lista 1
	cout << "Digite o tamanho da lista 1: ";
	cin >> tam1;
	
	//Perguntando o tamanho da lista 2
	cout << "Digite o tamanho da lista 2: ";
	cin >> tam2;
	
	//Limpando a Tela
	system ("cls");
	
	//Preenchendo a lista 1
	cout << "Digite os elementos da lista 1:" << endl;
	for (int i=0;i<tam1;i++){
		cout << "->";
		cin >> elem1;
		lista1.push_back(elem1);
	}
	
	//Limpando a Tela
	system ("cls");
	
	//Preenchendo a lista 2
	cout << "Digite os elementos da lista 2:" << endl;
	for (int i=0;i<tam2;i++){
		cout << "->";
		cin >> elem2;
		lista2.push_back(elem2);
	}
	
	//Verificando ou ordenando a lista 1
	it1=lista1.begin();
	it2=lista1.begin();
	advance(it2,1);
	
	
	while(1) {
		if (it2==lista1.end())
			break;
			
		if(*it1>=*it2){
			check1 = false;
			break;
		}	
		it1++;
		it2++;
	}
 	if (check1 == true){
       cout << "A lista 1 esta ordenada!" << endl;
    }
    else if (check1 == false){
    	cout << "A lista 1 não está ordenada" << endl;
		lista1.sort();
	}
	
	//Verificando ou ordenando a lista 2
	it3=lista2.begin();
	it4=lista2.begin();
	advance(it4,1);
	
		while(1) {
			if (it4==lista2.end())
				break;
			if(*it3>=*it4){
				check2 = false;
				break;
			}
			it3++;
			it4++;
		}
	 	if (check2 == true){
	       cout << "A lista 2 está ordenada!" << endl;
	    }
		    else if (check2 == false){
		    	cout << "A lista 2 não está ordenada" << endl;
				lista2.sort();
			}
			
		//Mesclando as listas
		while (!lista2.empty()){
			lista1.push_back(lista2.front());
			lista2.pop_front();
		}	
			lista1.sort();
			//Limpando a tela
			system ("cls");
		//Printando a lista mesclada
		cout << "Listas 1 e 2 mescladas:" << endl;
		while(!lista1.empty()){
				cout << lista1.front() << endl;
				lista1.pop_front();
			}
	return 0;
}

