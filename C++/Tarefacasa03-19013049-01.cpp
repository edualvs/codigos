#include <iostream>
#include <locale.h>
#include <fstream>
#include <conio.h>
#include <vector>
using namespace std;
//Criptador e Desencriptador
//Guilherme Leal de Medeiros - 190136049

ifstream arquivo;
int chave=0;
string destino;

void inicio() {
	
	//Entrada da chave 
	while (chave <= 0 || chave > 50) {
		cout << "--------------------------------------\n";
		cout << "     Digite a chave a ser usada\n";
		cout << "         [número de 1 a 50]\n";
		cout << "--------------------------------------\n";
		cin >> chave;	
		if (cin.fail()) {
				cin.clear();
	      		chave= 0;
	      		cin.ignore();
			}
		system ("cls");
	}
	//Seleção do arquivo
	cout << "--------------------------------------------------------------------------\n";
	cout << "             Digite o nome do arquivo a ser usado\n";
	cout << "--------------------------------------------------------------------------\n";
	cout << "            O arquivo deve estar na mesma pasta do programa\n";
	cout << "     Não esqueça de colocar a terminação do arquivo. Ex: secreto.txt\n";
	cout << "--------------------------------------------------------------------------\n";
	cout << "\n -->";
	cin.ignore();
	getline(cin,destino);
	system ("cls");
}

int codificar(int x) {
	int posicao=0, pos=0;
	vector<string> texto;
	vector<string>::iterator linha;
	string linhan, sequencia="abcdefghijklmnopqrstuvwxyz~`@#$%^&*()-+{}|\\”’:;.,?/=!ABCDEFGHIJKLMNOPQRSTUVWXYZ";;
	
	ifstream arquivo(destino.c_str());

	if (arquivo.is_open() == false) {
		cout << "\n\n-------------------------------------------\n";
		cout << "  Erro - Não foi possível abrir o arquivo\n";
		cout << "-------------------------------------------\n";
		return 0;
	}
	
	//Codificação do texto
	while (!arquivo.eof()) {	
		getline(arquivo, linhan);
		for (int j= 0; j < linhan.size(); j++) {
			for (int i= 0; i < sequencia.size(); i++) {
				if(linhan[j] == sequencia[i]) {
					if (x == 1) {
						posicao= i+chave;
						if (posicao > sequencia.size()-1)
							posicao= posicao-sequencia.size();
					}
					else if (x == 2) {
						posicao= i-chave;
						if (posicao < 0)
							posicao= posicao-sequencia.size();
					} 
				linhan[j]=sequencia[posicao];
				break;
				}
			}
		}
		texto.push_back(linhan);	
	} 
	arquivo.close();
	break;
}
	
	ofstream codificar(destino.c_str());
	
	//Salvar no arquivo
    for (linha=texto.begin(); linha < texto.end(); linha++) {
		if (linha == texto.end()-1) {
			codificar << *linha;
			cout << *linha;
		}
		else {
			codificar << *linha << endl;
			cout << *linha << endl;
		}
	}
   codificar.close();
   
   return 1;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	system("title Criptografador de Arquivos");
	char tecla=0;

	//Escolha da opção
		cout << "\n  ---------------------------------\n";
		cout << "      1 | Criptografar arquivo\n";
		cout << "      2 | Descriptografar arquivo\n";
		cout << "      3 | Sair\n";
		cout << "  ---------------------------------\n\n";
		cout << " Escolha a opção que deseja executar [1/2/3]:\n\n";
		tecla=getch();
		system ("cls");
	
	switch ((int)tecla) {
		
		case 49: {
			inicio();
			if (codificar(1)==1) {
			cout << "\n\n---------------------------------------\n";
			cout << "     Seu arquivo foi criptografado \n";
			cout << "---------------------------------------\n\n";
			}
			break;
		}

		case 50: {
			inicio();
			if (codificar(2)==1) {
			cout << "\n\n---------------------------------------\n";
			cout << "    Seu arquivo foi descriptografada \n";
			cout << "---------------------------------------\n\n";
			}
			break;
		}

		case 51: {
			break;
		}
		
		default: {
			main();
			break;
		}	
	}
	
	return 0;
}
