// Luiz Eduardo 08/19
// Programa #1
#include <iostream>
#include <locale.h>
using namespace std;

int main()
{
	setlocale(LC_ALL,"Portuguese")	;
    cout << "Ol� mundo!\n\a";
    cout << "Digite um n�mero inteiro e aperte ENTER\n";
    int var;
    cin >> var;
    cout << "Resto da divis�o do n�mero por 2 � " << var%2;
    return 0;
}
