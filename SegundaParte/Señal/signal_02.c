#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

void capturar_senal_SIGINT(int numeroDeSenial);
void captura_senal_SIGURS1(int numeroDeSenial);


int main(int argc, char const *argv[])
{
    /* Configuramos el tratamiento para la señal  SIGINT */
    signal(SIGINT, capturar_senal_SIGINT);
    signal(SIGUSR1, captura_senal_SIGURS1);

    //Acá tenemos un loop infinito
    for(;;)
        pause();

    return 0;
}

void capturar_senal_SIGINT(int numeroDeSenial)
{
    printf("Aunque me digas que termine, no voy a terminar\n", numeroDeSenial);
}

void captura_senal_SIGURS1(int numeroDeSenial)
{
    printf("FINALIZO\n");
    exit(0);
}