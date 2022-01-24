//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Exercício 2

#include <iostream>
#include <locale.h>

using namespace std;

int main () {
	setlocale (LC_ALL,"Portuguese");
	int n=0;
	cout << "Digite um valor n, desde que, 0<n<=100!\n";
	cout << "->";
	cin >> n;
	int mat[n][n];
	
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
				mat[i][j];
				mat[i][j]=' ';
		}
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			if (i!=j)
				mat[i][j]=0;
			else
				mat[i][j]=1;
		}
		
	
		
	
	cout << "\n\n";
	
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			cout << mat[i][j] << "|";
		}
		cout << endl;	
	}
	return 0;
}
