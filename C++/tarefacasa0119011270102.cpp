// Luiz Eduardo 08/19
// Tarefa de casa 1 #2
#include <iostream>
#include <locale.h>
#include <math.h>
using namespace std;

int main () {
	 setlocale(LC_ALL, "Portuguese");
	 cout << "Digite um n�mero com seis algarismos.\n";
	 int x,x1,x2,x3,x4,x5,x6;
	 cin >> x;
	 x1=(x/100000);
	 x2=(x/10000)-(x/100000)*10;
	 x3=(x/1000)-(x/10000)*10;
	 x4=(x/100)-(x/1000)*10;
	 x5=(x/10)-(x/100)*10;
	 x6=x-((x/10)*10);
	 
	 if (x1==x6 && x2==x5 && x3==x4){
	    cout << "Este n�mero � um pal�ndromo!\n";
	    return 0;}
	 
	    cout << "Este n�mero n�o � um pal�ndromo!\n";
     return 0;
}
