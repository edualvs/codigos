// Luiz Eduardo 08/19
// Programa #1
#include <iostream>
#include <locale.h>
using namespace std;

int main()
{
	setlocale(LC_ALL,"Portuguese")	;
    cout << "Olá mundo!\n\a";
    cout << "Digite um número inteiro e aperte ENTER\n";
    int var;
    cin >> var;
    cout << "Resto da divisão do número por 2 é " << var%2;
    return 0;
}
