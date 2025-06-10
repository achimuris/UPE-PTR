#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int potencia(int, int);
void *potenciaD(void *arg);
int num = 0;

int main()
{
	clock_t ini, fin;
	double tiempo = 0.0;
	pthread_t pth1, pth2, pth3, pth4;
	int arg1, arg2, arg3, arg4;
	int resultado;

	
	printf("Ingrese un número entero: ");
	scanf("%d", &num);
	
	ini = clock();
	
	printf("inicio Main Thread\n");
	
	arg1 = 2;
	resultado = pthread_create(&pth1, NULL, potenciaD, &arg1);
	arg2 = 3;
	resultado = pthread_create(&pth2, NULL, potenciaD, &arg2);
	arg3 = 5;
	resultado = pthread_create(&pth3, NULL, potenciaD, &arg3);
	arg4 = 7;
	resultado = pthread_create(&pth4, NULL, potenciaD, &arg4);
	
	resultado = pthread_join(pth1, NULL);
	resultado = pthread_join(pth2, NULL);
	resultado = pthread_join(pth3, NULL);
	resultado = pthread_join(pth4, NULL);
	
	fin = clock();
					
	tiempo += (double)(fin - ini) / CLOCKS_PER_SEC;
					
	printf("tiempo de ejecución de cálculos %f segundos\n", tiempo);
	
	printf("Fin Main Thread\n");

	return 0;
}

int potencia(int pnum, int ppot)
{
    int pres = 1;
    while (ppot >= 1)
    {
        pres = pres * pnum;
        ppot--;
    }
    return pres;
}

void *potenciaD(void *arg)
{
	int d = *((int *)arg);
	int i = 0, resant = 0, resdes = 0, res = 0;
	
	printf("soy thread %d\n", pthread_self());
	
	for (i = 0; resdes < num; i++)
		resdes = potencia(d, i);
		
	i -= 2;
	resant = potencia(d, i);

	if ((num - resant) < (resdes - num))
		res = resant;
	else
		res = resdes;
	
	printf("fin thread %d: potencia de %d más cercada a %d es %d\n", pthread_self(), d, num, res);
}