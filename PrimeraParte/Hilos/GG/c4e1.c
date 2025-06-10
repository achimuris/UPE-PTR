#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS	3

void *informe_thread(void *args);

int main()
{
	pthread_t threads[NUM_THREADS];
	int thread_args[NUM_THREADS];
	int i;
	int resultado;
	
	for (i = 0; i < NUM_THREADS; i++)	{
		printf("en Main creando thread %d\n", i);
		thread_args[i] = i;
		
		resultado = pthread_create(&threads[i], NULL, informe_thread, &thread_args[i]);
	}

	for (i = 0; i < NUM_THREADS; i++)	{
		resultado = pthread_join(threads[i], NULL);
	}
	
	printf("en Proceso\n");
	
	for (i = 0; i < NUM_THREADS; i++)	{
		printf("en Main creando thread %d\n", i);
		thread_args[i] = i;
		
		resultado = pthread_create(&threads[i], NULL, informe_thread, &thread_args[i]);
	}
	
	for (i = 0; i < NUM_THREADS; i++)	{
		resultado = pthread_join(threads[i], NULL);
	}
	
	printf("Fin\n");
	
	return 0;
}

void *informe_thread(void *args)
{
	printf("soy el thread %d\n", pthread_self());
	
}