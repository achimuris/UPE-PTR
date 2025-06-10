#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include <time.h>
#include <sys/time.h>

void capturar_senal(int numeroDeSenial);
double GetHoraActual();

double horaInicio;
double horaFinal;

int main(int argc, char const *argv[])
{
    /* Configuramos el tratamiento para la señal  SIGINT */
    signal(SIGINT, capturar_senal);

    horaInicio = GetHoraActual();
    //Acá tenemos un loop infinito
    for(;;)
        pause();

    return 0;
}

void capturar_senal(int numeroDeSenial)
{
    printf("El número de señal es: %d\n", numeroDeSenial);
    horaFinal = GetHoraActual();

    printf("La duración es de: %f en segundos\n", horaFinal - horaInicio);
}

double GetHoraActual()
{

    struct timeval tv;
    struct tm      * timeinfo;
    
    gettimeofday ( & tv, 0 );
    timeinfo = localtime ( & tv.tv_sec );
    
    double time_now = 3600 * timeinfo->tm_hour + 60 * timeinfo->tm_min  + timeinfo->tm_sec;
    time_now += ((double)(tv.tv_usec) / 1000000.0);

    return time_now;
}


