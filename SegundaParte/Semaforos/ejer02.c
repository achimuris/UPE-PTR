#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define CANTIDAD_DE_LINEAS 10000
#define CANTIDAD_DE_HILOS 10


void *SumarEnteros(void *arg);
unsigned long saldo;
sem_t semaforo;

int main()
{
    int indice =0;
    int parametros[CANTIDAD_DE_HILOS];
    pthread_t Hilos[CANTIDAD_DE_HILOS];

    //Esta inicializado en 1
    sem_init(&semaforo, 0, 1);

    for(indice=0;indice<CANTIDAD_DE_HILOS;indice++)
    {
        parametros[indice] = indice;
        pthread_create(&Hilos[indice],NULL, SumarEnteros, &parametros[indice]);
    }

    for(indice=0;indice<CANTIDAD_DE_HILOS;indice++)
    {
        pthread_join(Hilos[indice],NULL);
    }
    printf("\nSaldo:%lu\n",saldo);

    return 0;
}

void * SumarEnteros(void *arg)
{
    int posicion = 0;
    posicion = *(int *)arg;

    int desde = (posicion * 1000) + 1;
    int hasta = desde + 999;

    srand(time(NULL));    

    for (int i = desde; i < hasta; i++)
    {        
        //Sección crítica
        sem_wait(&semaforo);
        saldo = saldo + (rand() % 10);
        sem_post(&semaforo);
        //FIN Sección crítica
    }
}