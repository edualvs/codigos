// Luiz Eduardo 08/19
// Programa #3
#include <iostream>
#include <locale.h>
using namespace std;

int main ()
{
     setlocale(LC_ALL, "Portuguese");
     cout << "Digite um n�mero. ";
     int n,m=0;
     cin >> n;
     cout << "Digite outro n�mero";
     cin >> m;
     if (n>m)
         cout << "O primeiro n�mero que voc� digitou � o maior ! ";   
     else
	     cout << "O segundo n�mero que voc� digitou � o maior ! ";   
	return 0;
}
