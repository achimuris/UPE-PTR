#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS	4

void *tareaA(void *args);
void *tareaB(void *args);
void *tareaC(void *args);
void *tareaD(void *args);

int main(int argc, char const *argv[])
{
    pthread_t hiloA, hiloB, hiloC, hiloD;

    int numeroIngresado = 0;

    printf("Ingrese un número:\n");
    scanf("%d", &numeroIngresado);

    while (numeroIngresado!=0)
    {
        
        pthread_create(&hiloA, NULL, tareaA, &numeroIngresado);
        pthread_create(&hiloB, NULL, tareaB, &numeroIngresado);
        pthread_create(&hiloC, NULL, tareaC, &numeroIngresado);
        pthread_create(&hiloD, NULL, tareaD, &numeroIngresado);


        pthread_join(hiloA, NULL);
        pthread_join(hiloB, NULL);
        pthread_join(hiloC, NULL);
        pthread_join(hiloD, NULL);

        printf("Ingrese un número:\n");
        scanf("%d", &numeroIngresado);
    }
    



    printf("Terminó la ejecución del programa\n");

    return 0;
}

void *tareaA(void *args)
{
    int num = *((int *)args);
    printf("Estoy realizando el factorial de: %d\n", num);
}

void *tareaB(void *args)
{
    int num = *((int *)args);
    printf("Estoy realizando la potencial al cubo de: %d\n", (num * num * num));
}

void *tareaC(void *args)
{
    int num = *((int *)args);
    printf("Estoy realizando la raíz cuadrada de: %f\n", sqrtf(num));
}

void *tareaD(void *args)
{
    int num = *((int *)args);
    int suma =0;
    for(int i = 1; i<=num; i++)
    {
        suma+=i;
    }
    printf("Estoy realizando la sumatoria de: %d es %d\n", num, suma);
}