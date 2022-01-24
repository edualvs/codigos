//Luiz Eduardo Alves da Costa
//190112701
//Exercício 13

#include <iostream>
#include <locale.h>
#include <algorithm>

using namespace std;

int procuraeconta (string s,char c){
	int cont=0;
	cout << "Digite uma sequência X de caracteres: ";
	getline (cin,s);
	cout << "Digite um caractere: ";
	cin >>c;
	cont=count(s.begin(),s.end(),c);
	cout << "A quantidade de vezes que '" << c << "' aparece na string |" << s << "| é igual " << cont; 
}

int main (){
	setlocale (LC_ALL,"Portuguese");
	string str;
	char ch;
	procuraeconta (str,ch);
	return 0;
}

