// Luiz Eduardo 08/19
// Programa #2
#include <iostream>
#include <locale.h>
using namespace std;

int main ()
{
     setlocale(LC_ALL, "Portuguese");
     cout << "Ol� usu�rio\n";
     cout << "Digite um n�mero e aperte enter, por favor.\n";
     int n=0;
     cin >> n;
     if (n%2==0)
   	     cout << "Este n�mero � par !";
     else
        cout << "Este n�mero � impar !";
 
     return 0;	
}

