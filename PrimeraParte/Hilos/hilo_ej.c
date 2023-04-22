#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS 5

void *perform_work(void *arguments)
{
    // CASTEA LA DIRECCION DE MEMORIA
    int index = *((int *)arguments);
    int sleep_time = 2;// 1 + rand() % NUM_THREADS;
    printf("HILO %d: Empecé.\n", index);
    printf("HILO %d: Voy a esperar %d segundos. \n", index, sleep_time);
    sleep(sleep_time);
    printf("HILO %d: Finalicé. \n", index);
}

void * holamundo(void * argumentos)
{
    printf("HILO 2: Estoy en el hilo de HOLA MUNDO - %d - y voy a dormir 2 segundos\n", pthread_self());
    sleep(2);
    printf("HILO 2: Finalicé\n");
}

void * saludar(void * argumentos)
{

    //int index = *((int *)arguments);
    char * nombre = ((char *)argumentos);
    printf("HILO 3: Estoy en el hilo de SALUDAR - %d -  y voy a dormir 2 segundos\n", pthread_self());
    printf("HILO 3: Saludo a %s\n", nombre);
    sleep(2);
    printf("HILO 3: Finalicé\n");
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    int result_code;

    // create all thread one by one
    for (i = 0; i < NUM_THREADS; i++)
    {
        printf("EN MAIN: Creando el hilo %d.\n", i);
        thread_args[i] = i;

        if (i == 2)
        {
            result_code = pthread_create(&threads[i], NULL, holamundo, &thread_args[i]);
        }
        else if (i == 3)
        {
            char andres [50];
            strcpy(andres, "Andres");
            result_code = pthread_create(&threads[i], NULL, saludar, andres);
        }else
        {
            result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        }
        
        
        assert(!result_code);
    }

    printf("EN MAIN: Todos los hilos han sido creados.\n");

    // wait for each thread to complete
    for (i = 0; i < NUM_THREADS; i++)
    {
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
        printf("EN MAIN: Hilo %d ha finalizado.\n", i);
    }
    printf("El programa MAIN ha finalizado.\n");
    return 0;
}
