//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Exercício 3

#include <iostream>
#include <locale.h>

using namespace std;

int main () {
	setlocale (LC_ALL,"Portuguese");
	int lin=0,col=0;
	cout << "Digite um tamanho LxC de uma matriz!\nSendo que, 0 < L,C <=100\nLinha ->";
	cin >> lin;
	cout << "Coluna ->";
	cin >> col;
	int mat[lin][col],maior=0,menor=0;
	system ("cls");
	cout << "Agora digite os elementos da matriz!\n";
	
	for (int i=0;i<lin;i++)
		for (int j=0;j<col;j++){
			cout << "Posição [" << i << "][" << j << "]->"; 
			cin >> mat[i][j];
		}
	system ("cls");
	
	cout << "A matriz resultante é essa:\n\n";
	
	for (int i=0;i<lin;i++){
		for (int j=0;j<col;j++){
			cout << mat[i][j] << "|";
		}
	cout << endl;
	}
	system ("pause");
	
	maior=mat[0][0];
	menor=mat[0][0];
	
	for (int i=0;i<lin;i++)
		for (int j=0;j<col;j++){
			if (mat[i][j]>maior)
				maior=mat[i][j];
		}
		
	for (int i=0;i<lin;i++)
		for (int j=0;j<col;j++){
			if (mat[i][j]<menor)
				menor=mat[i][j];
		}
	
	system ("cls");
	
	cout << "O maior valor dessa matriz é:" << maior;
	cout << "\nO menor valor dessa matriz é:" << menor;	
		
	
	return 0;
}

