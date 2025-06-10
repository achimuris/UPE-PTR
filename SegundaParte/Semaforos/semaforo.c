#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NR_LOOP 150000

static int contador = 0;
sem_t semaforo1;

static void * funcion1(void *arg)
{
    for(int i = 0; i < NR_LOOP; i++)    
    {
        sem_wait(&semaforo1);
        //Inicio Sección crítica Hilo 1
        contador++;
        //Fin Sección crítica Hilo 1
        sem_post(&semaforo1);
    }
    printf("Termino el primero\n");
}


static void * funcion2(void *arg)
{
    for(int i = 0; i < NR_LOOP; i++)    
    {
        sem_wait(&semaforo1);
        //Inicio Sección crítica Hilo 2
        contador--;
        //Fin Sección crítica Hilo 2
        sem_post(&semaforo1);
    }
    printf("Termino el segundo \n");
}

int main() {
    pthread_t hilo1, hilo2;
    sem_init(&semaforo1, 0, 1); //Inicializo el semaforo
    pthread_create(&hilo1, NULL, *funcion1, NULL);
    pthread_create(&hilo2, NULL, *funcion2, NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    printf("Valor del contador: %d\n", contador);
    sem_destroy(&semaforo1);
    return (EXIT_SUCCESS);
}
