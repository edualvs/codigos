// Luiz Eduardo 08/19
// Programa #3
#include <iostream>
#include <locale.h>
using namespace std;

int main ()
{
     setlocale(LC_ALL, "Portuguese");
     cout << "Digite um número. ";
     int n,m=0;
     cin >> n;
     cout << "Digite outro número";
     cin >> m;
     if (n>m)
         cout << "O primeiro número que você digitou é o maior ! ";   
     else
	     cout << "O segundo número que você digitou é o maior ! ";   
	return 0;
}
