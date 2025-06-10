#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char comandoLS[10];
    char comandoDATE[10];
    char *args[] = {"ls", "-l", NULL};

    strcpy(comandoLS, "ls");
    strcpy(comandoDATE, "date");
    pid_t nuevoProceso = 0;
    int bandera = 1;
    while(bandera >0)
    {
        int opcionUsuario = 0;

        printf("Ingrese una opción:  \n");
        printf("0. Finalizar el proceso\n");
        printf("1. Indicar la memoria utilizada en ese momento\n");
        printf("2. Hacer un ping a 8.8.8.8\n");
        printf("3. Informar el espacio en disco utilizado\n");

        scanf("%d", &opcionUsuario);


        switch (opcionUsuario)
        {
        case 0:
            printf("El proceso %d ha finalizado\n", getpid());
            bandera=0;
            break;

        case 1:
            nuevoProceso = fork();

            if (nuevoProceso==0)
            {
                printf("Estamos informando la cantidad de memoria libre en este instante. Desde el pid %d\n", getpid());
                bandera=0;
                exit(0);
            }
            break;        
        case 2:
        nuevoProceso = fork();

        if (nuevoProceso==0)
        {
            printf("Estamos haciendo ping al 8.8.8.8. Desde el pid %d\n", getpid());
            bandera=0;
        }
            break;        
        case 3:
        nuevoProceso = fork();

        if (nuevoProceso==0)
        {
            printf("Estamos informando el espacio en disco utilizado. Desde el pid %d\n", getpid());
            bandera=0;
        }
    
            break;        
        default:
            printf("Opción no valida\n");
            break;
        }
        waitpid(nuevoProceso, NULL, 0);
    }

    return 0;
}