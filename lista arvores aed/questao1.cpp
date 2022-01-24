//Luiz Eduardo Alves da Costa
//Matr�cula: 190112701
//Lista de �rvore Bin�ria - Quest�o 1

#include <iostream>
#include <locale.h>
#include <fstream>
#include <set>
using namespace std;

class Arvore {
	public:
	set<int> arvoreBinaria;
	set<int> :: iterator it;
	void InsereNotas (){//Fun��o que insere elementos na �rvore
		int notas,i,aux;
		cout << "Quantas notas desejar inserir?" << endl;
		cin >> notas;
		for (i=0; i<notas; i++){
			cin >> aux;
			arvoreBinaria.insert(aux);
		}
	}
	void OrdenaNotas(){//Fun��o que mostra a �rvore j� ordenada
		for(it = arvoreBinaria.begin(); it!=arvoreBinaria.end(); it++){
				cout << *it << endl;
			}
	}
	
	void BuscaNota (){//Fun��o que busca um elemento na �rvore
		int aux;
		cout << "Qual nota deseja buscar?" << endl;
			cin >> aux;
			if (arvoreBinaria.find(aux)!=arvoreBinaria.end()){
				cout << "A nota " << aux << " est� presente na �rvore" << endl;
			}
			else{
				cout << "A nota " << aux << " n�o est� presente na �rvore" << endl;
			}
	}
	
	void ApagaNota (){//fun��o que apaga elemento da �rvore
		int aux;
		cout << "Qual nota deseja apagar?" << endl;
		cin >> aux;
		arvoreBinaria.erase(aux);
	}
	
	void MediaTurma (){//fun��o calcula m�dia da turma
		float media;
		int aux=0;
		for(it = arvoreBinaria.begin(); it!=arvoreBinaria.end(); it++){
			aux = *it + aux;
		}
		media = aux/arvoreBinaria.size();
		cout << "A m�dia da turma foi " << media << endl;
	}
	
	void SalvaNotas (){//fun��o que salva em um arquivo todas as notas da turma
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
				cout << "Escolha uma op��o: " << endl;
				cout << "1. Inserir notas" << endl;
				cout << "2. Ordenar as notas" << endl;
				cout << "3. Buscar uma nota" << endl;
				cout << "4. Apagar uma nota" << endl;
				cout << "5. M�dia da turma" << endl;
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

