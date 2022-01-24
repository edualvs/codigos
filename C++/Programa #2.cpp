// Luiz Eduardo 08/19
// Programa #2
#include <iostream>
#include <locale.h>
using namespace std;

int main ()
{
     setlocale(LC_ALL, "Portuguese");
     cout << "Olá usuário\n";
     cout << "Digite um número e aperte enter, por favor.\n";
     int n=0;
     cin >> n;
     if (n%2==0)
   	     cout << "Este número é par !";
     else
        cout << "Este número é impar !";
 
     return 0;	
}

