// Luiz Eduardo 08/19
// Tarefa de casa 1 #3
#include <iostream>
#include <locale.h>
#include <math.h>
using namespace std;

int main () 
    {
	 setlocale(LC_ALL, "Portuguese");
	 cout << "Digite a sua data de nascimento e data do dia de hoje.\n";
	 int dia1,mes1,ano1,dia2,mes2,ano2,a,b,c,idade;
     cout << "Dia de nascimento: ";
	 cin >> dia1;
	 cout << "Mês de nascimento: ";
	 cin >> mes1;
	 cout << "Ano de nascimento: ";
	 cin >> ano1;
	 cout << "Dia atual: ";
	 cin >> dia2;
	 cout << "Mês atual: ";
	 cin >> mes2;
	 cout << "Ano atual: ";
	 cin >>ano2;
	  
	 a=(dia2-dia1);
	 b=(mes2-mes1)*30;
	 c=(ano2-ano1)*365;
	 
	idade=a+b+c;
	 cout << "Sua idade em dias é " << idade;	
	 return 0;
	 }
	 
	 
