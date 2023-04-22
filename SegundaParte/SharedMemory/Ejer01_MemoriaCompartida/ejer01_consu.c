#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "ejer01.h"

void *addr;
int tamanioEstructura; //Tamaño global

int main(int argc, char const *argv[])
{
    int fd;
    int res;
    configuracion dato;
    
    tamanioEstructura = sizeof(configuracion);
	// Obtengo el file descriptor de la memoria compartida.
    fd = shm_open(NOMBRE_MEMORIA_COMPARTIDA, O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Error ejer01.c: shm_open");
		return 10;
	}

    /* 
        Mapeamos la memoria compartida al espacio de dirección 
        de memoria del proceso
    */
	addr = mmap(NULL, tamanioEstructura, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("Error shm_open mmap");
		return 30;
	}

    //Creamos una copia del proceso.
    fork();

    while (1)
    {
        /*Tenemos que leer el color*/
        memcpy((void * )&dato, addr, tamanioEstructura);

        switch (dato.numeroColor)
        {
            case COLOR_AMARILLO:
                printf("%s\n", KYEL);
                break;
            case COLOR_VERDE:
                printf("%s\n", KGRN);
                break;
            case COLOR_AZUL:
                printf("%s\n", KBLU);
                break;
            case COLOR_ROJO:
                printf("%s\n", KRED);
                break;
        }
        /*printf con color*/
        printf("Hola Mundo desde %d\n", getpid());
        sleep(3);
    }
    
    return 0;
}