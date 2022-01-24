// Luiz Eduardo Alves da Costa
// 190112701
//9 - Crie um programa orientado a objetos que cadastre alunos da disciplina de
//AED para facilitar a vida do professor nos lançamentos e consultas. Nesse
//programa deve ser possível cadastrar cada aluno pelo nome, matricula, idade,
//semestre e curso que está fazendo.
#include <iostream>
#include <vector>
#include <locale.h>
#include <conio.h>

using namespace std;

class Cadastro{
	public:
		vector< vector<string> > lista;
		
		void aCadastro(){ //método do cadastro
		
		int qntalunos;
		
		cout << "Digite a quantidade de alunos que deseja cadastrar:" << endl;
		cin >> qntalunos;
		
		cin.ignore(); //Corrigindo o erro do getline/cin
		
		system ("cls"); //limpando a tela
		
		//Lendo as infos dos alunos
		for (int i=0; i<qntalunos; i++){
				vector<string> temp;
				cout << "Digite as informações do aluno ["<< i+1 <<"] na ordem indicada." << endl;	
					string nome,mat,idade,sem,curso;
					cout << "Nome: ";
					getline (cin,nome);
					cout << "Matrícula: ";
					getline (cin,mat);
					cout << "Idade: ";
					getline (cin,idade);
					cout << "Semestre: ";
					getline (cin,sem);
					cout << "Curso: ";
					getline (cin,curso);	
					temp.push_back(nome);		
					temp.push_back(mat);
					temp.push_back(idade);
					temp.push_back(sem);
					temp.push_back(curso);
					lista.push_back(temp);	
					system ("cls");			
		}	
		cout << "-----------------------------------------------------" << endl;
		cout << "Lista dos alunos cadastrados" << endl;
		cout << "-----------------------------------------------------" << endl;
		
		//Printando na tela todos os alunos cadastrados e sua infos
		for (int i=0;i<lista.size();i++){
			for(int j=0; j<5; j++){	
			cout << lista[i][j];
			cout << " | ";
			}
			cout << endl << "\n";
		}
	}
};

int main (){
	
	setlocale (LC_ALL, "Portuguese");
	
	Cadastro cadastro; // Instanciando o objeto
	cadastro.aCadastro(); // Chamando o método aCadastro
	return 0;
}
