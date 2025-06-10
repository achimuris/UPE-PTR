#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>


void *factorial(void *arg);

int main(int argc, char *argv[])
{
	pthread_t pth1, pth2;
	int arg1, arg2;
	int i = 0, pot = 0;
	
	if (argc != 3)	{
		printf("error: cantidad de parámetros incorrecta, debe ingresar 2 números\n");
		return 0;
	}
	
	if (atoi(argv[1]) < 1 || atoi(argv[2]) < 1)	{
		printf("error: debe ingresar números positivos\n");
		return 0;
	}
	
	printf("inicio Main Thread\n");
	
	
	arg1 = atoi(argv[1]);
	pthread_create(&pth1, NULL, factorial, &arg1);
	arg2 = atoi(argv[2]);
	pthread_create(&pth2, NULL, factorial, &arg2);
	
	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);
	
	pot = atoi(argv[1]);
	for (i = 1; i < atoi(argv[2]); i++)	{
		pot = pot * atoi(argv[1]);
	}	
	printf("en Main potencia %d a la %d = %d\n", atoi(argv[1]), atoi(argv[2]), pot);
	
	return 0;
}

void *factorial(void *arg)
{
	int num = *((int *)arg);
	
	int valf = 1;
	
	while(num > 1)	{
		valf = valf * num;
		printf("%d x ", num);
		num--;
	}

	printf("1 = %d\n", valf);
}