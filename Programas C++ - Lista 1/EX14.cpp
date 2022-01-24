//Luiz Eduardo Alves da Costa
//190112701
//Exercício 14

#include <iostream>
#include <locale.h>
#include <algorithm>

using namespace std;

int contavogais (string s){
	cout << "Digite uma frase: ";
	getline (cin,s);
	int cont,cont1,cont2,cont3,cont4; 
	cont = count (s.begin(),s.end(),'a');
	cont1 = count (s.begin(),s.end(),'e');
	cont2 = count (s.begin(),s.end(),'i');
	cont3 = count (s.begin(),s.end(),'o');
	cont4 = count (s.begin(),s.end(),'u');
	cout << "A vogal 'a' aparece " << cont << " vezes." << endl;
	cout << "A vogal 'e' aparece " << cont1 << " vezes." << endl;
	cout << "A vogal 'i' aparece " << cont2 << " vezes." << endl;
	cout << "A vogal 'o' aparece " << cont3 << " vezes." << endl;
	cout << "A vogal 'u' aparece " << cont4 << " vezes." << endl;
	cout << "Totalizando " << cont + cont1 + cont2 + cont3 + cont4 << " vezes que uma vogal aparece na frase!";
	
}


int main (){
	setlocale (LC_ALL,"Portuguese");
	string str;
	contavogais(str);
	return 0;
}
