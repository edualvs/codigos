//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Exercício 4

#include <iostream>
#include <locale.h>
#include <math.h>

using namespace std;


	struct Aluno {
		string mat;
		int prova[3];
		double media;
	};


int main (){
	setlocale (LC_ALL,"Portuguese");
	int n=0;
	double mediageral1=0.0,mediageral2=0.0,mediageral3=0.0,dp[3]={0.0,0.0,0.0},res=0.0,res2=0.0,res3=0.0,res4=0.0;
	cout << "Digite o número de alunos: ";
	cin >> n; 	
	cout << "\n\n";
	Aluno aluno[n];
	
	//Pegando os dados
	for (int i = 0; i < n; i++ ){
		cout << "Digite o número de matrícula do aluno " << i+1 << ":";
		cin >> aluno[i].mat;
			for (int j = 0; j < 3; j++){
				cout << "Digite a nota da prova " << j+1 << ":";
				cin >> aluno[i].prova[j];
			}
	}
	
	//Calculando as médias
	for(int i=0; i<n; i++){
		for (int j=0; j<3; j++){
		res=res+aluno[i].prova[j];
	 	}
	 	aluno[i].media=res/3;
	 	res=0;
	}
	
	//Calculando a média geral de cada prova
	
	for(int i=0; i<n; i++){
		res2=res2+aluno[i].prova[0];
	}
	mediageral1=res2/n;
	
	for(int i=0; i<n; i++){
		res3=res3+aluno[i].prova[1];
	}
	mediageral2=res3/n;
	for(int i=0; i<n; i++){
		res4=res4+aluno[i].prova[2];
	}
	mediageral3=res4/n;
	
	//Calculando o desvio padrão
	for (int i=0;i<n;i++){
		dp[0] = dp[0] + pow(aluno[i].prova[0]-mediageral1,2);
		dp[1] = dp[1] + pow(aluno[i].prova[1]-mediageral2,2);
		dp[2] = dp[2] + pow(aluno[i].prova[2]-mediageral3,2);	
	}
	dp[0]=sqrt(dp[0]/n);
	dp[1]=sqrt(dp[1]/n);
	dp[2]=sqrt(dp[2]/n);
	
		
	
	//for (int i=0;i<n;i++){
	//	aluno[i].dp = sqrt(pow((aluno[i].prova[1]-mediageral2),2)/n);
	//}
	//for (int i=0;i<n;i++){
	//	aluno[i].dp = sqrt(pow((aluno[i].prova[2]-mediageral3),2)/n);
	//} 
	
	system ("cls");
	
	//Mostrando os dados na tela
	for (int i=0; i<n; i++){
		cout << "\nNotas do aluno |" << i+1  << "| cuja matrícula é: |" << aluno[i].mat << "|\n";
		for (int j=0; j<3; j++){
			cout << "Prova |" << j+1 << "|: ";
			cout << "|" << aluno[i].prova[j] << "|";
			cout << endl;
		}
		cout << endl;
		cout << "A média do aluno |" << i+1 << "| foi |" << aluno[i].media << "|\n";
	}
	
	system ("pause");
	system ("cls");
	
	cout << "A média geral da Prova 1 foi: " << mediageral1 << endl;
	cout << "A média geral da Prova 2 foi: " << mediageral2 << endl;
	cout << "A média geral da Prova 3 foi: " << mediageral3 << endl;
	cout << "\n\n\n";
	for (int i=0;i<n;i++)
		cout << "O desvio padrão da prova "<< i+1 << " foi: "<< dp[i] << "\n";
		
	return 0;
}
