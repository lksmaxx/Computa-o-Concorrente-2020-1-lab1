//lab 01 computacao concorrente
//Lucas Maximino Torres DRE: 118110129

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 2
#define ARRAY_S 75

typedef struct
{
	int array_s;
	int* array;
}t_args;


void* soma1 (void* arg)
{
	t_args* argst = (t_args*) arg;
	int size = argst->array_s;
	int* array = argst->array;
	for(int i = 0 ; i < size ; i++)
	{
		*(array + i)+= 1;
	}
	pthread_exit(NULL);
}


int main()
{
	int array_m[ARRAY_S];
	pthread_t tid[N_THREADS];
	t_args* args;	
	printf("Valores iniciais:\n");	
	for(int i = 0; i < ARRAY_S; i++)
	{
		array_m[i] = i;
		
		printf("[%d]:%d\n",i,array_m[i]);
	}
	for(int i = 0 ; i < N_THREADS ; i++)
	{
		args = malloc(sizeof(t_args));
		if(i == N_THREADS -1)
			args->array_s = (ARRAY_S / N_THREADS) + ARRAY_S % N_THREADS;
		else
			args->array_s = (ARRAY_S / N_THREADS);
		args->array = (array_m + ( i * ARRAY_S / N_THREADS));
		if(pthread_create(&tid[i],NULL,soma1,args))
		{
			printf("Falha ao criar a thread n: %d\n",i);
			return -1;
		}
	
	}
	for( int i = 0; i < N_THREADS ; i++ )
	{
		if(pthread_join(tid[i],NULL))
		{
			printf("Erro em join n:%d\n",i);
			return -2;
		}
	}
	printf("Valores finais:\n");
	for( int i = 0 ; i < ARRAY_S ; i++)
	{
		printf("[%d]:%d\n",i,array_m[i]);
	}
	free(args);
	pthread_exit(NULL);
	
	return 0;
}
