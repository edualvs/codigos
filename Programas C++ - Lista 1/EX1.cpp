//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Exercício 1

#include <iostream>
#include <locale.h>

using namespace std;
int main () {
	setlocale (LC_ALL , "Portuguese");
	cout << "Escreva os valores de uma matriz 5x5\n";

	int mat[5][5];
	
	for (int i=0;i<5;i++){
		for (int j=0;j<5;j++){
			cout << "[" << i << "][" << j << "]->";
			cin >> mat[i][j];
		}
	}
	cout << endl;
	for (int i=0;i<5;i++){
		for (int j=0;j<5; j++){ 
			cout << mat[i][j] << "|";
		}
	cout << endl;
	}
	
	int cont=0;	
	
	for (int i=1;i<5;i++){
		if (mat[0][i]==0)		
			for (int j=2;j<5;j++){
				if (mat[1][j]==0)
					for (int m=3;m<5;m++){
						if (mat[2][m]==0)
							for (int l=4;l<5;l++){
								if (mat[3][l]==0)
									cont++;				
				}				
			}			
		}		
	}
	
	if (cont>0)
		cout << "\nEssa matriz é uma matriz triangular inferior\n";
	else 
		cout << "\nEssa não é uma matriz triangular inferior!\n";	
	
	return 0;
}


