//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Lista de Árvore Binária - Questão 1

#include <iostream>
#include <locale.h>
#include <fstream>
#include <set>
using namespace std;

class Arvore {
	public:
	set<int> arvoreBinaria;
	set<int> :: iterator it;
	void InsereNotas (){//Função que insere elementos na árvore
		int notas,i,aux;
		cout << "Quantas notas desejar inserir?" << endl;
		cin >> notas;
		for (i=0; i<notas; i++){
			cin >> aux;
			arvoreBinaria.insert(aux);
		}
	}
	void OrdenaNotas(){//Função que mostra a árvore já ordenada
		for(it = arvoreBinaria.begin(); it!=arvoreBinaria.end(); it++){
				cout << *it << endl;
			}
	}
	
	void BuscaNota (){//Função que busca um elemento na árvore
		int aux;
		cout << "Qual nota deseja buscar?" << endl;
			cin >> aux;
			if (arvoreBinaria.find(aux)!=arvoreBinaria.end()){
				cout << "A nota " << aux << " está presente na árvore" << endl;
			}
			else{
				cout << "A nota " << aux << " não está presente na árvore" << endl;
			}
	}
	
	void ApagaNota (){//função que apaga elemento da árvore
		int aux;
		cout << "Qual nota deseja apagar?" << endl;
		cin >> aux;
		arvoreBinaria.erase(aux);
	}
	
	void MediaTurma (){//função calcula média da turma
		float media;
		int aux=0;
		for(it = arvoreBinaria.begin(); it!=arvoreBinaria.end(); it++){
			aux = *it + aux;
		}
		media = aux/arvoreBinaria.size();
		cout << "A média da turma foi " << media << endl;
	}
	
	void SalvaNotas (){//função que salva em um arquivo todas as notas da turma
		ofstream arquivo;
		arquivo.open("notas.txt",ios::app);
		for(it = arvoreBinaria.begin(); it!=arvoreBinaria.end(); it++){
				arquivo << *it << endl;
			}
			arquivo.close();
	}
	
	int menu (){//Menu
		int n, auxiliar;
		while(1){
			system("cls");
			do{
				cout << "Escolha uma opção: " << endl;
				cout << "1. Inserir notas" << endl;
				cout << "2. Ordenar as notas" << endl;
				cout << "3. Buscar uma nota" << endl;
				cout << "4. Apagar uma nota" << endl;
				cout << "5. Média da turma" << endl;
				cout << "6. Salvar as notas em um arquivo" << endl;
				cout << "7. Sair do programa" << endl;
				cin >> n;		
			}while(n<0 || n>7);
		
			switch(n){
				case 1:
					InsereNotas();
					break;
				case 2:
					OrdenaNotas();
					break;;
				case 3:
					BuscaNota();
					break;
				case 4:
					ApagaNota();
				case 5:
					MediaTurma();
					break;
				case 6:
					SalvaNotas();
					break;
				default: 
					return 0;
			}
			system("pause");
		};
	}	
};



int main (){
	setlocale (LC_ALL,"Portuguese");
	Arvore notas;
	notas.menu();
	return 0;
}

