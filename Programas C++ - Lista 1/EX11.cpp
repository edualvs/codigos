//Luiz Eduardo Alves da Costa
//190112701
//Exerc�cio 11

#include <iostream>
#include <locale.h>
using namespace std;

void opera(int n1,char op, int n2){
	if(op='+'){
		cout << "A soma de " << n1 << " e " << n2 << " � igual a " << n1+n2;
	}
	else if(op='-'){
		cout << "A subtra��o de " << n1 << " e " << n2 << " � igual a " << n1-n2;
	}
	else if(op='*'){
		cout << "A mutiplica��o de " << n1 << " por " << n2 << " � igual a " << n1*n2;
	}
	else if(op='/'){
		cout << "A divis�o de " << n1 << " por " << n2 << " � igual a " << n1/n2;
	}
	else if(op='%'){
		cout << "O resta da divis�o de " << n1 << " por " << n2 << " � igual a " << n1%n2;
	}
	
}

int main (){
	setlocale (LC_ALL,"Portuguese");
	cout << "Escreva dois n�meros e a opera��o a ser realizada com os mesmos.\nPara soma '+'\nPara subtra��o '-'\nPara multiplica��o '*'\nPara divis�o '/'\nPara resto '%'\n ";
	int num1,num2;
	char operando;
	cout << "Primeiro n�mero->";
	cin >> num1;
	cout << "Segundo n�mero->";
	cin >> num2;
	cout << "Operando->";
	cin >> operando;
	opera(num1,operando,num2);
	return 0;
}
