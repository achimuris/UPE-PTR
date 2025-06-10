#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAXIMA_CANTIDAD_DE_CABALLOS 6
#define CABALLO_FAVORITO_01 1
#define CABALLO_FAVORITO_05 5
#define TAMANIO_PISTA 10

int Salto(int limiteInferior, int limiteSuperior);

typedef struct caballoEnCompetencia
{
    int numero;
    int distancia_a_la_meta;
} caballo;

struct otraEstructura
{

};

caballo unCaballo;

void * CaballoNormal(void * args)
{
    caballo esteCaballo;
    esteCaballo = *(caballo *)args;
    int elSalto;

    while (esteCaballo.distancia_a_la_meta > 0)
    {
        elSalto = Salto(1, 2);
        esteCaballo.distancia_a_la_meta -= elSalto;
        printf("PID %d - El caballo %d realizó un salto de %d m y le quedan %d.\n", pthread_self(),  esteCaballo.numero, elSalto, esteCaballo.distancia_a_la_meta);
    }
    //En este punto el caballo ya cruzó la meta
    printf("NORMAL PID: %d - El caballo %d ha llegado a la meta\n", pthread_self(), esteCaballo.numero);
}

void * CaballoFavorito(void * args)
{
    caballo esteCaballo;
    esteCaballo = *(caballo *)args;
    int elSalto;

    
    
    while (esteCaballo.distancia_a_la_meta > 0)
    {
        elSalto = Salto(3, 4);


        esteCaballo.distancia_a_la_meta -= elSalto;
        printf("PID %d - El caballo %d realizó un salto de %d m y le quedan %d.\n", pthread_self(),  esteCaballo.numero, elSalto, esteCaballo.distancia_a_la_meta);
    }
    //En este punto el caballo ya cruzó la meta
    printf("FAVORITO: PID: %d - El caballo %d ha llegado a la meta\n", pthread_self(), esteCaballo.numero);
    
}

int Salto(int limiteInferior, int limiteSuperior)
{
    int metrosSaltados = 0;
    srand (time(NULL));
    int numeroAleatorio = rand();
    //printf("El número aleatorio es: %d\n", numeroAleatorio);
    metrosSaltados = numeroAleatorio % (limiteSuperior + 1 - limiteInferior) + limiteInferior;

    return metrosSaltados;
}

int main(int argc, char const *argv[])
{
    pthread_t hilosCaballos[MAXIMA_CANTIDAD_DE_CABALLOS];
    caballo dCaballo[MAXIMA_CANTIDAD_DE_CABALLOS];
    for (int i = 0; i < MAXIMA_CANTIDAD_DE_CABALLOS; i++)
    {
        //Todos los caballos en la carrera tienen una distancia para llegar a la meta de cien metros
        dCaballo[i].distancia_a_la_meta = TAMANIO_PISTA;
        dCaballo[i].numero = i + 1;

        //Comenzamos a crear los hilos
        if (dCaballo[i].numero == CABALLO_FAVORITO_01 || dCaballo[i].numero == CABALLO_FAVORITO_05)
        {
            int resultado = pthread_create(&hilosCaballos[i], NULL, CaballoFavorito, &dCaballo[i] );
        }else
        {
            int resultado = pthread_create(&hilosCaballos[i], NULL, CaballoNormal, &dCaballo[i] );
        }
    }
    for (int i = 0; i < MAXIMA_CANTIDAD_DE_CABALLOS; i++)
    {
        pthread_join(hilosCaballos[i], NULL);
    }
    
    return 0;
}
