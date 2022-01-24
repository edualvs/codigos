//Luiz Eduardo Alves da Costa
//Matrícula: 190112701

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define N 4 //depois trocar para um valor alto (ex: 1000 ou mais)
#define N_PROC 4 //variar entre 1, 2, 4 e 8 processoss para plotar o gráfico

//imprime a matriz caso ela tenha tamanho menor que 5x5
void print_matriz(float *X)
{
	if (N < 5)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				printf("%.2f ", X[i*N + j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	pid_t pid;
	int i, j, k;
	struct timespec tstart={0,0}, tend={0,0};

	float *A;
	float *B;
	float *C;

	key_t key1 = ftok("./process.c", 1);
	key_t key2 = ftok("./process.c", 2);
	key_t key3 = ftok("./process.c", 3);

    //TO-DO:
	//criar as regioes de memoria compartilhada aqui...	
    int shmid1, shmid2, shmid3;

    shmid1 = shmget(key1, (N*N)*sizeof(float), 0644|IPC_CREAT);
	
    A = shmat(shmid1, (void*)0, 0); //Acopla-se a região de memória key1
    if(A == (float *)(-1))
        fprintf(stderr,"erro, nao foi possivel associar (shmat)\n");

    shmid2 = shmget(key2, (N*N)*sizeof(float), 0644|IPC_CREAT);
	
    B = shmat(shmid2, (void*)0, 0); //pai associa-se a regiao compartilhada
    if(B == (float *)(-1))
        fprintf(stderr,"erro, nao foi possivel associar (shmat)\n");

    shmid3 = shmget(key3, (N*N)*sizeof(float), 0644|IPC_CREAT);
	
    C = shmat(shmid3, (void*)0, 0); //pai associa-se a regiao compartilhada
    if(C == (float *)(-1))
        fprintf(stderr,"erro, nao foi possivel associar (shmat)\n");


	//inicializacao das matrizes
	int count = 1;
	for (i = 0; i < N * N; i++)
	{
		A[i] = count;
		B[i] = count;
		C[i] = 0;
		count++;
	}

	print_matriz(A);
	print_matriz(B);
	
	//(TO-DO: aqui precisa criar os processos e indicar 
	//como será a divisão dos dados entre eles)	
	pid = fork();
	if(pid != 0){
		for (i=0; i<N_PROC-1; i++){
        pid = fork();//Cria os processos
		}	
	}
    

	//Função para calcular o tempo de execução do programa
    clock_gettime(CLOCK_MONOTONIC, &tstart); //Pega o Tempo inicial
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			int sum = 0;
			for (k = 0; k < N; k++)
				sum = sum + A[i * N + k] * B[k * N + j];
			
			C[i * N + j] = sum;
		}
	}
	
	print_matriz(C);

	clock_gettime(CLOCK_MONOTONIC, &tend);	//Pega o Tempo final
    

    printf("time: %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 		//Calcula o tempo de execução do programa (T_start e T_end)
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

	//TO-DO: destruir as regiões de memória compartilhada
	shmdt(A); 								//Destrói Região de Memória A(shmid1(key1))
    shmctl(shmid1, IPC_RMID, NULL);

    shmdt(B);								//Destrói Região de Memória B(shmid2(key2))
    shmctl(shmid2, IPC_RMID, NULL);

    shmdt(C);								//Destrói Região de Memória C(shmid3(key3))
    shmctl(shmid3, IPC_RMID, NULL);			

	return 0;
}