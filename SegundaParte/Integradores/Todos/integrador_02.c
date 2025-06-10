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
int STORAGE_SIZE;

int main(int argc, char const *argv[])
{
    tConfiguracion miConfiguracion;
    STORAGE_SIZE = sizeof(tConfiguracion);
    printf("El valor de STORAGE_SIZE: %d\n", STORAGE_SIZE);
    char formaImprimir[30];
    
    // crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
	fd = shm_open(MI_MEMORIA_COMPARTIDA, O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Error integrador02.c: shm_open");
		return 10;
	}

    // Mapea el objeto de memoria compartida en el espacio de direccionamiento.
	addr = mmap(NULL, STORAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("Error al mapear en integrador02.c: mmap\n");
		return 30;
	}

    while( 1 )
    {

        
        memcpy(&miConfiguracion, addr, STORAGE_SIZE);
 
        switch (miConfiguracion.color)
        {
        case ROJO:
            strcpy(formaImprimir, IMPRIMIR_ROJO);
            break;
        case VERDE:
            strcpy(formaImprimir, IMPRIMIR_VERDE);
            break;
        case AZUL:
            strcpy(formaImprimir, IMPRIMIR_AZUL);
            break;
        case AMARILLO:
            strcpy(formaImprimir, IMPRIMIR_AMARILLO);
            break;
        
        default:
            strcpy(formaImprimir, IMPRIMIR_ROJO);
            break;
        }

        printf("%s - %d HOLA MUNDO\n",formaImprimir, getpid());
	    sleep(3);
    }

    return 0;
}