//Luiz Eduardo Alves da Costa
//190112701
//Exercício 18

#include <iostream>
#include <stdlib.h>
#include <locale.h>

using namespace std;

int main (){
	setlocale (LC_ALL,"Portuguese");
	int *p;
	int quant,i;
	cout << "Digite a quantidade de números que deseja armazenar:";
	cin >> quant;
	p=(int *)(malloc(quant * sizeof(int)));
	
	//Caso dê algum erro na alocação de memória
	if (p == NULL){
		cout << "\nOcorreu um erro na alocação de memória";
		exit;
	}
	else {
		cout << "Digite os valores abaixo:" << endl;
		for (i=0;i<quant;i++){
			cout << "->";
			cin >> p[i];
		}
		system ("cls");
		cout << "Os números armazenados foram:" << endl; 
		for (i=0;i<quant;i++){
			cout << p[i] << " | ";
		}
		free(p);
	}
	return 0;
}
