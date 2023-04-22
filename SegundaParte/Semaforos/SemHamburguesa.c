#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<semaphore.h>

typedef struct 
{
	int indice;

}componentes;


void * preparacion(void * arg);
void * cocinarMedallon(void * arg);

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
sem_t semaforoDE,semaforoAF,semaforoBF, semaforoCF, semaforoEF;

int main(int argc, char const *argv[])
{
	componentes Componente[6];
	sem_init(&semaforoDE,0,0);
	sem_init(&semaforoAF,0,0);
	sem_init(&semaforoBF,0,0);
	sem_init(&semaforoCF,0,0);
	sem_init(&semaforoEF,0,0);

	pthread_t pasos[6];

	for (int i = 0; i < 6; i++)
	{
		Componente[i].indice = i;
		pthread_create(&pasos[i], NULL,&preparacion, &Componente[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		pthread_join(pasos[i],NULL);
	}

	sem_destroy(&semaforoDE);
	sem_destroy(&semaforoAF);
	sem_destroy(&semaforoBF);
	sem_destroy(&semaforoCF);
	sem_destroy(&semaforoEF);
	return 0;
}

void * preparacion(void * arg)
{
 	componentes Componente = *(componentes*) arg;

	 if(Componente.indice == 0)
	 {
	 	int tiempo;	 	
	 	tiempo = rand() % (6 - 1 + 1) + 1;
	 	printf("Hilo A, Cocinando la panceta\n\n");
	 	sleep(tiempo);
	 	sem_post(&semaforoAF);
	 }
	 else if (Componente.indice == 1)
	 {
	 	int tiempo;
	 	tiempo = rand() % (6 - 1 + 1) + 1;
	 	printf("Hilo B, Tostando el pan\n\n");
	 	sleep(tiempo);
	 	sem_post(&semaforoBF);
	 }
	 else if (Componente.indice == 2)
	 {
	 	int tiempo;
	 	tiempo = rand() % (6 - 1 + 1) + 1;
	 	printf("Hilo C, Cortando la lechuga\n\n");
	 	sleep(tiempo);
	 	sem_post(&semaforoCF);
	 }
	 else if (Componente.indice == 3)
	 {
	 	int tiempo;

	 	tiempo = rand() % (6 - 1 + 1) + 1;
	 	printf("Hilo D, Preparando el medallon\n\n");
	 	sleep(tiempo);
	 	sem_post(&semaforoDE);
	 /*	pthread_mutex_lock(&m);
	 	 pthread_t ultimo_paso;
	 	 pthread_create(&ultimo_paso, NULL, &cocinarMedallon, NULL);
	 	 pthread_join(ultimo_paso, NULL);
	 	pthread_mutex_unlock(&m);*/
	 }
	 else if (Componente.indice == 4)
	 {
	 	int tiempo; 
	 	sem_wait(&semaforoDE);	
	 	tiempo = rand() % (6 - 1 + 1) + 1;
	 	printf("Hilo E, Cocinando el Medallon\n\n");
	 	sleep(tiempo);
	 	sem_post(&semaforoEF);
	 }
	 else if (Componente.indice == 5)
	 {
	 	int tiempo; 	
	 	sem_wait(&semaforoAF);
	 	sem_wait(&semaforoBF);
	 	sem_wait(&semaforoCF);
	 	sem_wait(&semaforoEF);
	 	tiempo = rand() % (6 - 1 + 1) + 1;
	 	printf("Hilo F, Arma la hamburguesa\n\n");
	 	sleep(tiempo);
	 }
}

void * cocinarMedallon(void * arg)
{
	//sem_wait(&sema2);
	printf("Completando Hamburguesa\n\n");
	//sem_post(&sema2);
}