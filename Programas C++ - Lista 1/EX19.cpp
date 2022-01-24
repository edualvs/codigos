//Luiz Eduardo Alves da Costa
//190112701
//Exercício 19

#include <iostream>
#include <stdlib.h>
#include <locale.h>

using namespace std;


int *multiplica_vetores (int a[], int b[]){
	int i;
	a=(int *)(malloc(10 * sizeof(int)));
	b=(int *)(malloc(10 * sizeof(int)));
	if (a == NULL){
		cout << "\nOcorreu um erro na alocação de memória";
		exit;
	}
	else if (b == NULL){
		cout << "\nOcorreu um erro na alocação de memória";
		exit;
	}
	else {
		cout << "Digite 10 valores para um vetor A:\n";
		for (i=0;i<10;i++){
			cout << "->";
			cin >> a[i];
		}
		cout << "Digite 10 valores para um vetor B:\n";
		for (i=0;i<10;i++){
			cout << "->";
			cin >> b[i];
		}
		system ("cls");
		int *c;
		c=(int *)(malloc(10 * sizeof(int)));
		for (i=0;i<10;i++){
			c[i]=a[i]*b[i];
		}
		cout << "O vetor resultado de A[i]*B[i] é: " << endl;
		for (i=0;i<10;i++){
			cout << "[" << c[i] << "]" << endl;
		}
	}
}

int main (){
	setlocale (LC_ALL, "Portuguese");
	int x[0],y[0];
	*multiplica_vetores(x,y);
	return 0;
}
