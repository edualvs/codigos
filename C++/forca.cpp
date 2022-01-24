#include <iostream>
#include <locale.h>
using namespace std;

int main() {
	setlocale(LC_ALL,"Portuguese");
	cout << "** Jogo da Forca **" << endl;
	cout << "Digite uma palavra a ser adivinhada\n";
	string palavra="";
	cin >> palavra;
	int tamanho=palavra.size();
	system("cls");
	int i;
    string adivinha="";
    for (i=1;i<=tamanho;i++)
	     adivinha=adivinha+'*';
	/*int i=1;
	while (i<=tamanho) {
	    adivinha=adivinha+'*';
	    i++;
	    */
    cout << adivinha;	
	string erradas="";
	int tentativas=0;
	while (true) {		
		cout << "\nDigite uma letra\n";
		char letra;
		cin >> letra;
		tentativas++;
		i=0;
		bool acertou=false;
		while (i<tamanho) {
			if (letra == palavra[i]) {
			   adivinha[i]=letra;
			   system("cls");
			   cout << adivinha;
			   erradas=erradas+letra+'-';
		       cout << "\nLetras já jogadas\n";
		       cout << erradas;
			   acertou=true;
			   if (palavra==adivinha) {
			   	cout << "Parabéns ! Você acertou a palavra";
			   	cout << "Você tentou " << tentativas;
			   	return 0;
			   }
		    }
		    i++;
		}
		if (acertou==false) {			
		   cout << "\nEsta letra não existe na palavra\n";
		   erradas=erradas+letra+'-';
		   cout << "\nLetras já jogadas\n";
		   cout << erradas;
	    }
	}
	return 0;	
}
