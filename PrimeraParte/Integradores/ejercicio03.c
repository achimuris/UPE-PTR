#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

long largoPista = 10;
/*

Desarrollar un sistema, que simule la carrera de caballos, de la línea de
partida tenemos un total de seis caballos.
La pista cuenta con 100 metros, cada caballo avanza de forma aleatoria entre
2 y 3 metros por salto.
Los caballos 1 y 5, son siempre favoritos, ellos avanzan entre 3 y 4 metros
por salto.
Cada caballo deberá ser considerado como un proceso o como un hilo.

*/
typedef struct caballoEnPista
{
    int numeroCaballo;
    int metrosFaltantes;
    int cantidadTiempo;
} datoCaballoEnPista;

void EmularSalto(datoCaballoEnPista * unCaballo)
{
    int saltoMinimo = 3;
    int saltoMaximo = 4;
    int saltoFinal = 0;

    //printf("Soy el caballo %d (mi pid es %d) me faltan %d metros de pista\n", unCaballo.numeroCaballo, getpid(), unCaballo.metrosFaltantes);
    /* Es un caballo favorito*/
    if (unCaballo->numeroCaballo == 1 || unCaballo->numeroCaballo == 5)
    {
        saltoMinimo = 3;
        saltoMaximo=4;


    
    }else{

        saltoMinimo=2;
        saltoMaximo=3;
    }

    srand(time(NULL));
    saltoFinal = (int) rand() % (saltoMaximo - saltoMinimo) + saltoMinimo;

    if ((unCaballo->metrosFaltantes - saltoFinal) <= 0) // && unCaballo->metrosFaltantes > 0)
    {
        //Llegó a la meta
        unCaballo->metrosFaltantes = 0;
        printf("Soy el caballo %d y mi pid es %d y llegué a la meta\n", unCaballo->numeroCaballo, getpid());
        exit(0);
        /*Almacenar la fecha y hora que cruzó la meta */
    }else{
        unCaballo->metrosFaltantes = unCaballo->metrosFaltantes - saltoFinal;
        printf("El caballo %d hizo un salto de %d metro(s) y le faltan %d metro(s) de distancia\n", unCaballo->numeroCaballo, saltoMaximo, unCaballo->metrosFaltantes);
    }
    
}

int main(int argc, char const *argv[])
{
    pid_t caballo[6];
    datoCaballoEnPista caballos[6];

    caballo[0] = fork();
    if (caballo[0] == 0)
    {
        /* Estamos en el hijo */
        caballos[0].numeroCaballo = 1;
        caballos[0].metrosFaltantes = largoPista;
        caballos[0].cantidadTiempo = 10000;
        while (caballos[0].metrosFaltantes != 0)
            EmularSalto(&caballos[0]);
    }else
    {
        caballo[1] = fork();
        if (caballo[1] == 0)
        {
            caballos[1].numeroCaballo = 2;
            caballos[1].metrosFaltantes = largoPista;
            caballos[1].cantidadTiempo = 10000;
            while (caballos[1].metrosFaltantes != 0)
                EmularSalto(&caballos[1]);
        }else{
            //Acá estamos en el proceso MAIN y esperamos a que todos los procesos hijos finalicen
            //Recordar que cada proceso hijo es UN CABALLO.
            waitpid(caballo[0], NULL, 0);
            waitpid(caballo[1], NULL, 0);
        }
    }

    return 0;
}
