// Luiz Eduardo Alves da Costa
// 190112701
#include <iostream>
#include <vector>
#include <locale.h>
#include <conio.h>
#include <fstream>

using namespace std;

int main (){
	setlocale(LC_ALL, "Portuguese");
	
	char tecla=0;
	int pos=0, chave=0;
	ifstream arquivo;
	string destino;
	vector<string> codigo;
	vector<string>::iterator linha;
	string linha1, seq="abcdefghijklmnopqrstuvwxyz~`@#$%^&*()-+{}|\\”’:;.,?/=!ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	
	cout << "1 - Criptografar Arquivo\n";
	cout << "2 - Decriptografar Arquivo\n";
	cout << "3 - Sair\n";
	
	tecla=getch();
	system ("cls");
	//Menu
	switch ((int)tecla) {
	//Criptografar	
	case 49: {
		cout << "Digite a chave a ser usada\n";  
		cout << "Ela dever ser um número de 0 a 50\n";     
		cin >> chave;
		system ("cls");
		cout << "Digite o nome do arquivo\n";
		cout << "Exemplo: exemplo.txt\n";
		cin.ignore();
		getline(cin,destino);
		system ("cls");
		ifstream arquivo(destino.c_str());
	while (!arquivo.eof()) {	
		getline(arquivo, linha1);
		for (int j= 0; j < linha1.size(); j++) {
			for (int i= 0; i < seq.size(); i++) {
				if(linha1[j] == seq[i]) {
					pos= i+chave;
					if (pos > seq.size()-1)
						pos= pos-seq.size();
					linha1[j]=seq[pos];
					break;	
				}
			}
		}
		codigo.push_back(linha1);
	} 
	arquivo.close ();
	break;
	}
	//Descriptografar
	case 50:{
		cout << "Digite a chave a ser usada\n";  
		cout << "Ela dever ser um número de 0 a 50\n";     
		cin >> chave;
		system ("cls");
		cout << "Digite o nome do arquivo\n";
		cout << "Exemplo: exemplo.txt\n";
		cin.ignore();
		getline(cin,destino);
		system ("cls");
		ifstream arquivo(destino.c_str());
	while (!arquivo.eof()) {	
		getline(arquivo, linha1);
		for (int j= 0; j < linha1.size(); j++) {
			for (int i= 0; i < seq.size(); i++) {
				if(linha1[j] == seq[i]) {
					pos= i-chave;
					if (pos < 0)
						pos= pos-seq.size();
					linha1[j]=seq[pos];
					break;	
				}
			}
		}
		codigo.push_back(linha1);
	} 
	arquivo.close ();
	break;
	}
	//Sair
	case 51: {
		break;
	}
	default: {
		main();
		break;
	}		

}
		ofstream arq(destino.c_str());
		
		//Salvar no arquivo
    	for (linha=codigo.begin(); linha < codigo.end(); linha++) {
		if (linha == codigo.end()-1) {
			arq << *linha;
			cout << *linha;
		}
		else {
			arq << *linha << endl;
			cout << *linha << endl;
			}
		}
	arq.close();
	
	return 0;
}
