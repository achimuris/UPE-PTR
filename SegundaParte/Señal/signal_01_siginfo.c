#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int continuar=1;
double GetHoraActual();
void capturar_senal(int iNumSen, siginfo_t *info, void *ni)
{
    printf("Se recibió la señal.\n");
    continuar=0;
}

void no_termino_nada(int iNumSen, siginfo_t *info, void *ni)
{
    printf("¡No termino nada!\n");
    printf("info->si_signo %d\n", info->si_signo);
    printf("info->si_status %d\n", info->si_status);
    printf("info->si_errno %d\n", info->si_errno);
    printf("info->si_pid %d\n", info->si_pid);
    //printf("info->si_code %d\n", info.si_code);
    // printf("info->si_int %d\n", info->si_int);
    // printf("info->si_int %d\n", info->si_int);
    // printf("info->si_int %d\n", info->si_int);
}



int main()
{
    time_t rawtime;
    struct tm *timeinfo;
    clock_t tiempo_inicio, tiempo_final;
    double segundos;
    tiempo_inicio = GetHoraActual();
    
    struct sigaction act;              // La estructura que definirá como manejar la señal
    act.sa_sigaction = capturar_senal; // Definimos la rutina.
    sigfillset(&act.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    act.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGUSR1, &act, NULL);     // Establecemos la captura de la señal.

    struct sigaction actsigint;              // La estructura que definirá como manejar la señal
    actsigint.sa_sigaction = no_termino_nada; // Definimos la rutina.
    sigfillset(&actsigint.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    actsigint.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGINT, &actsigint, NULL);     // Establecemos la captura de la señal.
    
    while (continuar == 1){
        time(&rawtime);    
        timeinfo = localtime(&rawtime);
        printf("(%d) - Hora Actual:  %s\n",  getpid(), asctime(timeinfo));
        fflush(stdout);
        sleep(5);
    }

    tiempo_final = GetHoraActual();
    printf("Tiempo de inicio: %f\n", tiempo_inicio);
    printf("Tiempo final: %f\n", tiempo_final);
    segundos = (double)(tiempo_inicio - tiempo_final) / CLOCKS_PER_SEC; 
    printf("Segundos Transcurridos desde el inicio: %f\n", segundos);
    return 0;
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