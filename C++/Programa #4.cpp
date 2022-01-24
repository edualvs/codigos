// Luiz Eduardo 08/19
// Programa #4
#include <iostream>
#include <locale.h>
using namespace std;

int main () {
     setlocale(LC_ALL, "Portuguese");
     cout << "Digite a quilometragem rodada.\n";
     int n;
     cin >> n;
     float custo;
     if (n<=50)
         custo=n*1.75;
     if (n>50 && n<=150)
         custo=87.5+(n-50)*1.65;
     if (n>150)    
         custo=252.5+(n-150)*1.50;
         cout << "o custo total é " << custo;
}

