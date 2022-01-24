// Luiz Eduardo 08/19
// Tarefa de casa 1 #1
#include <iostream>
#include <locale.h>
using namespace std;

int main () 
    {
	 setlocale(LC_ALL, "Portuguese");
     cout << "Digite uma sequência de oito números inteiros\n";
     int x,y,z,w,a,b,c,d;
     cin >> x;
     cin >> y;
     cin >> z;
     cin >> w;
     cin >> a;
     cin >> b;
     cin >> c;
     cin >> d;
     if (x+z<y)
        cout << "O 2° número é maior que a soma dos seus vizinhos\n";
     if (y+w<z)
        cout << "O 3° número é maior que a soma dos seus vizinhos\n";
     if (z+a<w)
        cout << "O 4° número é maior que a soma dos seus vizinhos\n";
     if (w+b<a)
        cout << "O 5° número é maior que a soma dos seus vizinhos\n";
     if (a+c<b)
        cout << "O 6° número é maior que a soma dos seus vizinhos\n";
     if (b+d<c)
        cout << "O 7° número é maior que a soma dos seus vizinhos\n";
     return 0;    
	}   
     
