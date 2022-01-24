//Luiz Eduardo Alves da Costa
//Matrícula: 190112701

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
 
#define N 4 //depois trocar para um valor alto (ex: 1000 ou mais)
#define N_THREADS 8 //variar entre 1, 2, 4 e 8 threads para plotar o gráfico
 
float **C;
float **A;
float **B;
 
void *multiply(void *tid)
{ 
 int i, j, k;
 long t = (long) tid;
 printf("thread %ld\n",t);
 
 //TO-DO: multiplicação (aqui precisa indicar a divisão dos dados entre as threads)
 
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
 pthread_exit(NULL); //thread termina
} 
 
int main(int argc, char **argv) { 

    struct timespec tstart={0,0}, tend={0,0};
    srand(time(NULL));

    int i, j; 
    pthread_t threads[N_THREADS];
    int status;

    time_t t1;
    time_t t2;
 
    //alocacao dinamica das matrizes A, B e C
    A = (float **) malloc(N*sizeof(float*));
    for(i = 0 ; i < N ; i ++)
    A[i] = (float*) malloc(N*sizeof(float));
 
    B = (float **) malloc(N*sizeof(float*));
    for(i = 0 ; i < N ; i ++)
    B[i] = (float*) malloc(N*sizeof(float));
    
    C = (float **) malloc(N*sizeof(float*));
    for(i = 0 ; i < N ; i ++)
    C[i] = (float*) malloc(N*sizeof(float));
    
    //inicializacao das matrizes
    int count = 1;
    for (i = 0; i < N; i++) { 
        for (j = 0; j < N; j++) 
        {
            A[i][j] = count;
            B[i][j] = count;
            C[i][j] = 0;
            count++;
        }
    } 
 
    clock_gettime(CLOCK_MONOTONIC, &tstart); //Pega o Tempo inicial
    //TO-DO: criacao das threads
 
    for(i = 0 ; i < N_THREADS ; i++){
        printf("Criando uma thread %d\n",i);
        status = pthread_create(&threads[i],NULL,&multiply, (void*) i);
    
        if(status != 0 )
        {
            printf("Nao foi possivel criar thread\n");
            exit(1);
        }
    }
 
    for(i = 0 ; i < N_THREADS ; i++){
        pthread_join(threads[i], NULL);
    }
 
    clock_gettime(CLOCK_MONOTONIC, &tend);      //Pega o Tempo final
 
    printf("time: %.5f seconds\n",
    ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -   //Calcula o tempo de execução do programa (T_start e T_end)
    ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
 
 
	//imprime a matriz caso ela tenha tamanho menor que 5x5
	if(N < 5)
	{
		for (i = 0; i < N; i++) 
		{ 
			for (j = 0; j < N; j++) 
			{
				printf("%.2f ",C[i][j]);
			}
			printf("\n"); 
		} 
	}
    return 0; 
}
