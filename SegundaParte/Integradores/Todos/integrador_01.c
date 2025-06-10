#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include "libreria.h"




int res;
int fd;
int len;
pid_t pid;
void *addr;
int gSTORAGE_SIZE;
void capturar_senal(int iNumSen, siginfo_t *info, void *ni);
int main(int argc, char const *argv[])
{
    struct sigaction act; 			    // La estructura que definirá como manejar la señal 
    act.sa_sigaction=capturar_senal; 	// Definimos la rutina.
    sigfillset(&act.sa_mask); 		    // Bloqueamos todas las señales mientras se ejecuta la rutina.
    act.sa_flags=SA_SIGINFO; 		    // Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGINT,  &act, NULL); 	// Establecemos la captura de la señal.
    sigaction(SIGTERM, &act, NULL); 	// Establecemos la captura de la señal.
 




    int colorActual = ROJO;
    tConfiguracion miConfiguracion;
    gSTORAGE_SIZE = sizeof(tConfiguracion);
    
    // crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
	fd = shm_open(MI_MEMORIA_COMPARTIDA, O_RDWR | O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Error integrador01.c: shm_open");
		return 10;
	}

	// Fija el tamaño del objeto de memoria compartida.
	res = ftruncate(fd, gSTORAGE_SIZE);
	if (res == -1)
	{
		perror("Error integrador01.c: ftruncate");
		return 20;
	}

	// Mapea el objeto de memoria compartida en el espacio de direccionamiento.
	addr = mmap(NULL, gSTORAGE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("Error al mapear en integrador01.c: mmap");
		return 30;
	}

    while( 1 )
    {
        switch (colorActual)
        {
        case ROJO:
            colorActual = VERDE;
            break;
        case VERDE:
            colorActual = AZUL;
            break;
        case AZUL:
            colorActual = AMARILLO;
            break;
        case AMARILLO:
            colorActual = ROJO;
            break;
        
        default:
            colorActual = ROJO;
            break;
        }
        sleep(4);
        miConfiguracion.color = colorActual;
        

        printf("%d - El color actual es: %d\n", getpid(), miConfiguracion.color);
        //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
	    memcpy(addr, &miConfiguracion, gSTORAGE_SIZE);
    }

    return 0;
}

void capturar_senal(int iNumSen, siginfo_t *info, void *ni)
{
    printf("Recibí la señal %d desde el PID %d y esto es un cierre seguro\n", iNumSen, info->si_pid);
	
    // Desmapea el objeto de memoria compartida del espacio de direcciones del proceso llamador (set.exe).
	res = munmap(addr, gSTORAGE_SIZE);
	if (res == -1)
	{
		perror("munmap");
		exit(40);
	}    
    // shm_open: Remueve el segmento de memoria compartida.
	fd = shm_unlink(MI_MEMORIA_COMPARTIDA);
	if (fd == -1)
	{
		perror("unlink");
		exit ( 100);
	}
    exit(0);
}