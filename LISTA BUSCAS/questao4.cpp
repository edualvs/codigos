// Luiz Eduardo Alves da Costa
// 190112701
// Quest�o 4
#include <iostream>
#include <locale.h>
using namespace std;

	// Busca bin�ria
	int pesqbin (int vet[],int tam,int val){
    int begin = 0;
    int end = tam - 1;

    while (begin <= end) {  

        int i = (begin + end) / 2;  

        if (vet[i] == val) { 
            return i;
        }

        if (vet[i] < val) {  
            begin = i + 1;
        } else {  
            end = i;
        }
    }
    return -1;
}
	
int main (){
	setlocale (LC_ALL,"Portuguese");
	int tam,aux,num;
	
	// Pedindo para o usu�rio o tamanho do vetor
	cout << "Digite o tamanho do vetor:";
	cin >> tam;
	
	int vet[tam];
	
	// Preenchendo o vetor
	for (int i=0;i<tam;i++){
		cout << "Digite o n�mero que deseja colocar na posi��o " << i <<": ";
		cin >> vet[i];
	}
	cout << endl;
	
	
	// Ordenando em ordem crescente o vetor
	for(int i=0;i<tam;i++){		
		for(int j=i+1;j<tam;j++){
			if(vet[i]>vet[j])
			{
				aux = vet[i];
				vet[i] = vet[j];
				vet[j] = aux;
			}
		}
	}
	
	//Pedindo o n�mero a ser procurado
	cout << "Digite o n�mero que deseja procurar no vetor:";
	cin >> num;
	
	//Passando o return da fun��o pesqbin para a vari�vel res
	int res = pesqbin(vet,tam,num);
	
	//Condicional para imprimir se o n�mero procurado est� no vetor
	if (res != -1 ){
		cout << "O n�mero "<< num <<" foi encontrado na posi��o " << res << "!" << endl;
	}
	else
	cout << "O n�mero n�o existe no vetor!" << endl;
		
	return 0;
}
