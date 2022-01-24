//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Lista de Árvore Binária - Questão 2

#include <iostream>
using namespace std;

struct node{
	int ano;
	int pag;
	string livro;
	node* esq; 
	node* dir
	;  	
};
node* NewNode(int ano, int pag, string livro){
	node* newNode = new node();
	newNode->ano = ano;
	newNode->pag= pag;
	newNode->livro = livro;
	newNode->esq = NULL;
	newNode->dir = NULL;
	return newNode;
}
//Função de inserção dos elementos
node* insert(node* root, int ano, int pag, string livro){
	cout << "Digite o ano que deseja adicionar o livro: ";
	cin >> ano;
	cout << "Digite o número de páginas do livro: ";
	cin >> pag;
	cout << "Digite o nome do livro que deseja adicionar: ";
	cin >> livro;
	if(root = NULL){
		root = NewNode(ano, pag, livro);
	}
	else if(ano < root->ano){		
		root->esq = insert(root->esq, ano, pag, livro);
	}
	else{
		root->dir = insert(root->dir, ano, pag, livro);
	}
	return root;	
}
//Função de busca do livro
node* search(node* root, int ano, string livro){
	cout << "Qual livro deseja encontrar?" << endl;
	cout << "Ano:" << endl;
	cin >> ano;
	cin.ignore();
	cout << "Titulo:" << endl;
	getline(cin,livro);
	if(root == NULL || root->ano == ano && root->livro == livro){
		return root;
	}
	if(root->ano < ano){
		return search(root->dir, ano, livro);
	}
	return search(root->esq, ano, livro);	
}
int main(){
	node* root = (2013, 0, 0);			
	int n,ano,pag;
	string livro;
	//Menu
	while(1){
		system("cls");
		do{
			cout << "Escolha: " << endl;
			cout << "1- Inserir livros." << endl;
			cout << "2- Buscar livro." << endl;
			cout << "3- Sair." << endl;
			cin >> n;		
		}while(n<0 || n>3);
		switch(n){
			case 1:{
				insert(root, ano, pag, livro);
				break;
			}
			case 2:{
				search(root, ano, livro);
				break;
			}
			default:
				return 0;
		}
		system("pause");
	};
	return 0;
}
