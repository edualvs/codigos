//Luiz Eduardo Alves da Costa
//190112701
//Exercício 15

#include <iostream>
#include <algorithm>

using namespace std;
int contaconsoantes (string s){
	cout << "Digite uma frase: ";
	getline (cin,s);	
	int cont,cont1,cont2,cont3,cont4,cont5; 
	cont = count (s.begin(),s.end(),'a');
	cont1 = count (s.begin(),s.end(),'e');
	cont2 = count (s.begin(),s.end(),'i');
	cont3 = count (s.begin(),s.end(),'o');
	cont4 = count (s.begin(),s.end(),'u');
	cont5 = count (s.begin(),s.end(),' ');
	int conttotal=cont+cont1+cont2+cont3+cont4+cont5;
	int contcons=s.length()-conttotal;
	cout << "A quantidade de consoantes nessa frase é igual a " << contcons << endl;
}



int main (){
	setlocale (LC_ALL,"Portuguese");
	string str;
	contaconsoantes(str);
	return 0;
}
