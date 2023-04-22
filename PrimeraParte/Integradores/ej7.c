#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define CANTIDAD_MAXIMA 10

void CrearHijos(int profundidad, int anchura);
int main (int argc, char *argv[]){
    int i;
    int profundidad, anchura;
    
    pid_t pid_hijo;

    if (argc != 3) {
        printf("Debe informar anchura y profundidad!!!\n");
        exit(0);
    }

    profundidad = atoi(argv[1]); /* profundidad */
    anchura = atoi(argv[2]); /* anchura */

    printf("La profundidad es: %d\n", profundidad);
    printf("La anchura es: %d\n", anchura);

    CrearHijos(profundidad, anchura);

    sleep (2);
    return 0;
}

void CrearHijos(int profundidad, int anchura)
{
    pid_t procesos[anchura];
    int i = 0;
    int cantidadDeHijos = anchura;
    
    for (int i = 0; i < cantidadDeHijos; i++)
    {
        procesos[i] = fork();
        
        if (procesos[i] == 0)
        {
            printf("%d - %d - Proceso a lo ancho - %d\n", (profundidad), (i+1), getpid());

            //El primer hijo también es padre.
            if (i == 0 && ((profundidad -1) > 0))
            {
                CrearHijos((profundidad - 1), anchura);
            }
            exit(0);
        }
        else
        {
            if ((profundidad - 1) == 0)
            {
                cantidadDeHijos--;//Garantizamos que el último nivel tenga un hijo menos. Igual que el gráfico.
            }
        }
    }   

    //Esperamos a los procesos hijos.
    for(i=0; i < cantidadDeHijos; i++)
    {
        waitpid(procesos[i], NULL, 0);
    }
}