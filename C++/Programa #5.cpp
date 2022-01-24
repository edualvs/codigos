// Luiz Eduardo 08/19
// Programa #5
#include <iostream>
#include <locale.h>
using namespace std;

int main () {
     setlocale(LC_ALL, "Portuguese");
     cout << "Digite um número com seis algarismos\n";
     int n;
     cin >> n;
     if (n<=99999)
		{cout << "Que pena, você digitou um número com menos de seis algarismos.\n";
        return 0;}
     if (n>999999)
        {cout << "Que pena, você digitou um número com mais de seis algarisos.\n"; 
	    return 0;}
 	   cout << "O primeiro algarismo é " << n/100000 << "\n" 	;
	 int m=n/100000*10;
	   cout << "O segundo algarismo é " << n/10000 - m << "\n";
	 int l=n/10000*10;
	   cout << "O terceiro algarismo é " << n/1000 - l << "\n";
	 int o=n/1000*10;
	   cout << "O quarto algarismo é " << n/100 - o << "\n";
	 int p=n/100*10;
	   cout << "O quinto algarismo é " << n/10 - p << "\n";
	 int h=n/10*10;
	   cout << "O sexto algarismo é " << n/1 - h << "\n";
	
	    
     
     
     
     
     
     return 0;
 }
