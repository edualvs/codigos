//Luiz Eduardo Alves da Costa
//190112701
//Exercício 11

#include <iostream>
#include <locale.h>
using namespace std;

void opera(int n1,char op, int n2){
	if(op='+'){
		cout << "A soma de " << n1 << " e " << n2 << " é igual a " << n1+n2;
	}
	else if(op='-'){
		cout << "A subtração de " << n1 << " e " << n2 << " é igual a " << n1-n2;
	}
	else if(op='*'){
		cout << "A mutiplicação de " << n1 << " por " << n2 << " é igual a " << n1*n2;
	}
	else if(op='/'){
		cout << "A divisão de " << n1 << " por " << n2 << " é igual a " << n1/n2;
	}
	else if(op='%'){
		cout << "O resta da divisão de " << n1 << " por " << n2 << " é igual a " << n1%n2;
	}
	
}

int main (){
	setlocale (LC_ALL,"Portuguese");
	cout << "Escreva dois números e a operação a ser realizada com os mesmos.\nPara soma '+'\nPara subtração '-'\nPara multiplicação '*'\nPara divisão '/'\nPara resto '%'\n ";
	int num1,num2;
	char operando;
	cout << "Primeiro número->";
	cin >> num1;
	cout << "Segundo número->";
	cin >> num2;
	cout << "Operando->";
	cin >> operando;
	opera(num1,operando,num2);
	return 0;
}
