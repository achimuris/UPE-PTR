#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "sm01.h"


int main(int argc, char const *argv[])
{
    int res;
	int fd;
	int len;
	pid_t pid;
	void *addr;
    char valor = '0';

    pid = getpid();
    int tamanio = sizeof(char);



    printf("Soy el proceso 1 y mi PID es %d y el tamanio de un entero es de %d\n", pid, tamanio);

	// crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
	fd = shm_open(SHARED_MEMORY_UPE, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    // Fija el tamaño del objeto de memoria compartida.
	res = ftruncate(fd, tamanio);

    // Mapea el objeto de memoria compartida en el espacio de direccionamiento.
	addr = mmap(NULL, tamanio, PROT_WRITE, MAP_SHARED, fd, 0);

    //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
	memcpy(addr, &valor, tamanio);

    int valorNumero;
    
    for(int i = 0; i<10;i++)
    {

        //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
        memcpy(addr, &valor, tamanio);

        printf("El valor de VALOR: %c\n", valor);

        switch (valorNumero)
        {
        case 0:
            valor = DEF_ROJO;
            break;
        
        case 1:
            valor = DEF_VERDE;
            //sprintf(valor, "%c", DEF_VERDE);
            break;
        case 2:
            valor = DEF_AZUL;
            //sprintf(valor, "%c", DEF_AZUL);
            break;
        case 3:
            valor = DEF_AMARILLO;
            //sprintf(valor, "%c", DEF_AMARILLO);
            valorNumero=0;
            break;

        }

        sleep(3);

        valorNumero++;
    }
  
    // Desmapea el objeto de memoria compartida del espacio de direcciones del proceso llamador (set.exe).
	res = munmap(addr, tamanio);

    // shm_unlink: Remueve el segmento de memoria compartida.
	fd = shm_unlink(SHARED_MEMORY_UPE);

    return 0;
}
