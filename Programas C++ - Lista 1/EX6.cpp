//Luiz Eduardo Alves da Costa
//Matr�cula: 190112701
//Exerc�cio 6
#include <iostream>
using namespace std;
void soma(int n1,int n2){
	cout << "O resultado de " << n1 << " + " << n2 << " = " << n1+n2 <<"\n";
}
void soma2(int *n1,int *n2){
	cout << "O resultado de " << *n1 << " + " << *n2 << " = " << *n1+*n2 << "\n";
}
int main (){
	int x,y;
	cout << "Digite dois numeros para serem somados:\n" << "->";
	cin >> x;
	cout << "->";
	cin >> y;
	soma(x,y);
	soma2(&x,&y);		
	return 0;
}
