#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void capturar_senal(int iNumSen, siginfo_t *info, void *ni)
{
    printf("Recibí la señal %d desde el PID %d\n", iNumSen, info->si_pid);
}

int main(int argc, char const *argv[])
{
    printf("Mi PID es: %d\n", getpid());
    struct sigaction act;              // La estructura que definirá como manejar la señal
    act.sa_sigaction = capturar_senal; // Definimos la rutina.
    sigfillset(&act.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    act.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGINT, &act, NULL);     // Establecemos la captura de la señal.

    // struct sigaction actsigint;              // La estructura que definirá como manejar la señal
    // actsigint.sa_sigaction = no_termino_nada; // Definimos la rutina.
    // sigfillset(&actsigint.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    // actsigint.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    // sigaction(SIGINT, &actsigint, NULL);     // Establecemos la captura de la señal.

    while(1)
        pause;
    return 0;
}
