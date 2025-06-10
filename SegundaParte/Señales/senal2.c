#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void capturar_senal(int iNumSen, siginfo_t *info, void *ni) {
    printf("Se recibió la señal: %d\n", iNumSen);
    printf("También se puede leer por acá: %d\n", info->si_signo);
    printf("El proceso que envió la señal fue: %d\n", info->si_pid);
    printf("El usuario que envió la señal fue: %d\n", info->si_uid);
    printf("si_code: %d\n", info->si_code);
}


int main () {

    printf("PID %d\n", getpid());
    struct sigaction act; 			// La estructura que definirá como manejar la señal 
    act.sa_sigaction=capturar_senal; 	// Definimos la rutina.
    sigfillset(&act.sa_mask); 		// Bloqueamos todas las señales mientras se ejecuta la rutina.
    act.sa_flags=SA_SIGINFO; 		// Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGINT, &act, NULL); 	// Establecemos la captura de la señal.
    for(;;)
 	    pause();
    return 0;
}
