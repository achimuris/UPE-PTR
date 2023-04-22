#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "ejer01.h"

void *addr;
int tamanioEstructura; //Tamaño global

void manejador_alarma_signal(int signum);

int main(int argc, char const *argv[])
{
    int fd;
    int res;
    configuracion dato;
    
    signal(SIGALRM, manejador_alarma_signal);
    alarm(TIEMPO_ACTUALIZACION_TERMINAL);

    tamanioEstructura = sizeof(configuracion);
	// crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
	fd = shm_open(NOMBRE_MEMORIA_COMPARTIDA, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("Error ejer01.c: shm_open");
		return 10;
	}

	// Fija el tamaño del objeto de memoria compartida.
	res = ftruncate(fd, tamanioEstructura);
	if (res == -1)
	{
		perror("Error ejer01.c: ftruncate");
		return 20;
	}

	// Mapea el objeto de memoria compartida en el espacio de direccionamiento.
	addr = mmap(NULL, tamanioEstructura, PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("Error al mapear en ejer01.c: mmap");
		return 30;
	}


    //Inicializamos la estructura con el color ROJO
    dato.numeroColor=COLOR_ROJO;
    //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
	memcpy(addr, (void *)&dato, tamanioEstructura);

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
        printf("Hola Mundo desde %d (proceso1.exe)\n", getpid());

        sleep(3);
    }
    
    return 0;
}

void manejador_alarma_signal(int signum)
{

    /*Ahora cambiaremos de color*/
    configuracion dato;
    memcpy((void * )&dato, addr, tamanioEstructura);

    switch (dato.numeroColor)
    {
        case COLOR_AMARILLO:
            dato.numeroColor = COLOR_VERDE;
            break;
        case COLOR_VERDE:
            dato.numeroColor = COLOR_ROJO;
            break;
        case COLOR_AZUL:
            dato.numeroColor = COLOR_AMARILLO;
            break;
        case COLOR_ROJO:
            dato.numeroColor = COLOR_AZUL;
            break;
        default:
            break;
    }

    memcpy(addr, (void * )&dato, tamanioEstructura);
    alarm(TIEMPO_ACTUALIZACION_TERMINAL);
}
