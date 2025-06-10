#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void capturar_senal(int iNumSen) {
    printf("Se recibió la señal %d\n", iNumSen);
}

void capturar_senal2(int iNumSen) {
    printf("Se recibió la señal %d en el método 2\n", iNumSen);
}

int main() {

    signal(SIGINT, capturar_senal); 	// Cuando se reciba SIGINT, ejecutar capturar_senal.
    // signal(SIGALRM, capturar_senal2); 	// Ídem para SIGALRM.
    // signal(SIGTERM, capturar_senal); 	// Ídem para SIGTERM.
 
    printf("Terminé de configurar el proceso %d\n", getpid());

    for(;;)		// Un loop infinito.
        pause();	// Se ejecuta pause dentro del loop para que no sea espera activa.
 
    return 0;
}
