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
    char valor [2];

    pid = getpid();
    int tamanio =  sizeof(char) + sizeof(char);



    printf("Soy el proceso 1 y mi PID es %d y el tamanio de un entero es de %d\n", pid, tamanio);

	// crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
	fd = shm_open(SHARED_MEMORY_UPE, O_RDONLY, S_IRUSR | S_IWUSR);

    // Mapea el objeto de memoria compartida en el espacio de direccionamiento.
	addr = mmap(NULL, tamanio, PROT_READ, MAP_SHARED, fd, 0);


    //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
	memcpy(&valor, addr, tamanio);

    int valorNumero;
    
    for(int i = 0; i<10;i++)
    {

        //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
        memcpy(&valor, addr, tamanio);

        printf("\033[31mHola Mundo\033[0m\nEstoy leyendo el valor de la MC: %s\n", valor);

     
        sleep(3);


    }
  
    // Desmapea el objeto de memoria compartida del espacio de direcciones del proceso llamador (set.exe).
	res = munmap(addr, tamanio);

    // shm_unlink: Remueve el segmento de memoria compartida.
	fd = shm_unlink(SHARED_MEMORY_UPE);

    return 0;
}
