//Luiz Eduardo Alves da Costa
//190112701
//Exercício 12

#include <iostream>
#include <locale.h>
#include <math.h>
using namespace std;

void soma(int num){
	int numfalso;
	float res=0;
	num=numfalso;
	if (num=0)
		res=1;
	else {
	for (int i=0;i<num;i++){
			res=res+1/pow(2,numfalso-1);
			numfalso--;
		}
	}
	cout << "\n\n" << res;
}

int main () {
	setlocale (LC_ALL,"Portuguese");
	int n;
	cout << "Digite um número inteiro qualquer:";	
	cin >> n;
	soma(n);
	return 0;
}
