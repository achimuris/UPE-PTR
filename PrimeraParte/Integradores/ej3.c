#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

typedef struct{
    int numberoCaballo;
    int salto;
    int pista;
}data;

void * CarreraCaballo(void * args);

int random_number(int min_num, int max_num);
//void saltoCaballosRestantes(data DATOS[]);

int main(int argc, char const *argv[])
{
	data DATOS[6];
	pthread_t caballos[6];	

	for (int i = 0; i < 6; i++)
	{
        DATOS[i].numberoCaballo = (i + 1);
		DATOS[i].pista = 10;

        pthread_create(&caballos[i],NULL, (void *)&CarreraCaballo, &DATOS[i]);
	}

	for (int i = 0; i < 6; i++)
    {
        pthread_join(caballos[i], NULL);
    }
	
	return 0;
}


int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}


//void * CalcularPotencia(void *arg);
void * CarreraCaballo(void *arg)
{
	clock_t t_ini, t_fin;
    double secs;
    //int indice = DATOS
    data caballo = *(data *)arg;
    int valorDelSalto = 0;

    t_ini = clock();//calculo de tiempo inicio
    while(caballo.pista > 0)
    {
        if (caballo.numberoCaballo == 1 || caballo.numberoCaballo==5)
        {
            valorDelSalto = random_number(3, 4);
        }else
        {
            valorDelSalto = random_number(1, 2);
        }
        
        caballo.salto = valorDelSalto;
  	    
  	    caballo.pista -= caballo.salto;

  	    if(caballo.pista > 0){
      		printf("%d - faltan %d metros para que llegue el caballo %d\n", pthread_self(), caballo.pista, caballo.numberoCaballo);
  		    sleep(2);
  	    }

  	    if(caballo.pista <= 0){
  		    printf("El caballo %d llego a la meta\n", caballo.numberoCaballo);
  	    }  	  
    }
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
}

/*void saltoCaballosRestantes(data DATOS[])
{
		
}*/