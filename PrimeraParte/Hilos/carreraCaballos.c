#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_CABALLOS 6
#define TAMANIO_PISTA 10

struct carreraCaballos
{
    int numeroDeCaballo;
    int distanciaRecorrida;
};



void * CaballoNoFavorito(void * argumento)
{
    int pasos = (rand() %2) + 2;
    int numeroCaballo = *(int *)argumento;
    int pasosFinales = TAMANIO_PISTA;

    printf("No soy un favorito: %d\n", numeroCaballo);

    while (pasosFinales>0)
    {
        pasos = (rand() %2) + 2;


        pasosFinales -= pasos;
        printf("Soy el caballo %d y me quedan tantos metros: %d y salté un largo de %d metros\n", numeroCaballo, pasosFinales, pasos);
    }
    
    printf("Terminé y soy el caballo: %d\n", numeroCaballo);

}

void * CaballoFavorito(void * argumento)
{

    int pasos = (rand() %2) + 3;
    int numeroCaballo = *(int *)argumento;
    int pasosFinales = TAMANIO_PISTA;

    printf("Soy un favorito: %d\n", numeroCaballo);

    while (pasosFinales>0)
    {
        pasos = (rand() %2) + 3;
        pasosFinales -= pasos;
        printf("Soy el caballo %d y me quedan tantos metros: %d y salté un largo de %d metros\n", numeroCaballo, pasosFinales, pasos);
    }
    
    printf("Terminé y soy el caballo: %d\n", numeroCaballo);
}

bool EsUnCaballoFavorito(int numeroCaballo)
{
    printf("\tnumeroCaballo: %d\n", numeroCaballo);
    if (numeroCaballo == 1 || numeroCaballo == 5)
    {
        return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    
    pthread_t caballos[MAX_CABALLOS];

    int caballo1 = 1;
    int caballo2 = 2;
    int caballo3 = 3;
    int caballo4 = 4;
    int caballo5 = 5;
    int caballo6 = 6;
    srand(time(NULL));

    pthread_create(&caballos[0], NULL, CaballoFavorito, &caballo1);
    pthread_create(&caballos[1], NULL, CaballoNoFavorito, &caballo2);
    pthread_create(&caballos[2], NULL, CaballoNoFavorito, &caballo3);
    pthread_create(&caballos[3], NULL, CaballoNoFavorito, &caballo4);
    pthread_create(&caballos[4], NULL, CaballoFavorito, &caballo5);
    pthread_create(&caballos[5], NULL, CaballoNoFavorito, &caballo6);

    
    //Esperamos a que terminen los hijos
    for (int i = 0; i < MAX_CABALLOS; i++)
    {
        pthread_join(caballos[i], NULL);
        // if (EsUnCaballoFavorito(i + 1))
        //     printf("Ya finalizó el caballo (favorito): %d\n", i+1);
        // else
        //     printf("Ya finalizó el caballo (no favorito): %d\n", i+1);

    }


    return 0;
}
