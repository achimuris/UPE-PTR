#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MEM_COMP_NAME "/SM_COLORES"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

//Declaración de variables globales
pid_t pidPadre;
pid_t proceso2;
pid_t proceso3;

typedef struct data {
	char color;
    pid_t proceso1;
    pid_t proceso2;
    pid_t proceso3;
    char algo;
} dato;

void *addr;

int tam = sizeof(dato);

//Fin de declaración de variables globales

void capturar_senal(int ) ;
void imprimirHolaMundo();

//La estructura info es GLOBAL
dato info;


int main(int argc, char const *argv[])
{
    info.algo = 'Z';
	// redefinimos el comportamiento de la señal SIGTERM
    signal(SIGTERM, capturar_senal); // el nuevo comportamiento es lo que se define en la función 
	// "capturar_senal" 
    
	
	pidPadre = getpid();
    pid_t pidProceso2, pidProceso3;

    int fd;

	
	//cargamos la estructura
	info.color = 'A';
    info.proceso1 = pidPadre;
	
	// queremos grabar la estructura en memoria --->>
	
	
	//creamos el segmento de memoria
	fd = shm_open(MEM_COMP_NAME, O_CREAT| O_RDWR, S_IRUSR| S_IWUSR);
	
	if (fd == -1)	{
		printf("Error en creando la memoria");
		return 1;	
	}
	
	//truncamos el segmento de memoria
	if (ftruncate(fd, tam) == -1)
	{
		printf("Error en ftruncate");
		return 1;
	}
	
	//mapeamos el segmento de memoria con el espacio de direccionamiento del proceso
	addr = mmap(NULL, tam, PROT_WRITE, MAP_SHARED, fd, 0);
	
	if(addr == MAP_FAILED)
	{
		printf("Error al mapear el objeto de memoria compartida.\n");

		return 1;
	}
	

	

	pidProceso2 = fork();
    //Si es el proceso padre
    if(pidProceso2 > 0)
    {
        info.proceso2 = pidProceso2;

        pidProceso3 = fork();

        //Como seguimos en el padre
        if(pidProceso3 > 0)
        {
            info.proceso3 = pidProceso3;

            // copiamos la info de la estructura en la memoria
            memcpy(addr, &info, tam);

        }
    }
    
    while( 1 != 0){
        imprimirHolaMundo();
        //pause();
    }

    return 0;
}



void capturar_senal(int iNumSen) 
{
    int unMap, unLink;
	
	printf("Se recibió la señal %d el PID %d\n", iNumSen, getpid() );
    
    
    if (pidPadre == getpid())
    {
        
        waitpid(info.proceso2, NULL, 0);
        waitpid(info.proceso3, NULL, 0);

		sleep(3);
		
		//desmapear y borrar la memoria compartida
		unMap = munmap(addr, tam);
		
		if (unMap == -1)	{
			printf("Error en desmapeo");

            exit(0);
		}
		
		unLink = shm_unlink(MEM_COMP_NAME);
		
		if(unLink == -1)
		{
			printf("Error al eliminar el objeto de memoria.");
            exit(0);

		}	
    }
    
    exit(0);
}

void imprimirHolaMundo()
{
    //Leemos el segmento de la memoria compartida
    memcpy(&info, addr, tam);

    //printf("Soy el PID: %d y te digo HOLA MUNDO y en color %c \n", getpid(), info.color);
    sleep(3);
    if (pidPadre == getpid())
    {
        if (info.color == 'A')
        {
            printf("%sSoy el PID: %d y te digo HOLA MUNDO y en color %c \n", KRED, getpid(), info.color);
            info.color = 'B';
        }else{
            if (info.color == 'B')
            {
                printf("%sSoy el PID: %d y te digo HOLA MUNDO y en color %c \n", KBLU, getpid(), info.color);
                info.color = 'C';
            }else
            {
                if  (info.color == 'C')
                {
                    printf("%sSoy el PID: %d y te digo HOLA MUNDO y en color 
                    
                    
                    %c \n", KYEL, getpid(), info.color);
                    info.color = 'A';
                }
            }
        }
        //Guardar en la memoria compartida
        memcpy(addr, &info, tam);
        sleep(4);
    }
    
}