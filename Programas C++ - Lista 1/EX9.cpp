//Luiz Eduardo Alves da Costa
//190112701
//Exercício 9

#include<iostream>
#define TAM 10
//atencao: note que declarar int *vetor equivale declarar int vetor[]
void copia_vetor(int *vetor, int *vetor2)
{
int vetor_aux[TAM], i;
for(i=0; i < TAM; i++)
	vetor_aux[i] = vetor[i];
	vetor2=vetor_aux;
}

void imprime_vetor(int *vetor)
{
int i;
for(i=0; i < TAM; i++)
std::cout << vetor[i] << " ";
std::cout << "\n";
}
int main()
{
int vet[TAM], vet2[TAM],i;
for(i=0; i<TAM; i++)
std::cin >> vet[i];
copia_vetor(vet, vet2);
imprime_vetor(vet);
std::cout << "C´opia:";
imprime_vetor(vet2);
}
/* O problema no programa esta na função copia_vetor, basta apagar a linha 13, e incluir for(i=0;i<TAM;i++){			Desse jeito, o problema se resolve.
																							vetor2[i]=vetor_aux[i];	
																						}
