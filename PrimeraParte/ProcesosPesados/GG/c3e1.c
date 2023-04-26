#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


void factorial(int num);

int main(int argc, char *argv[])
{
	pid_t pid_h1 = 0;
	pid_t pid_h2 = 0;
	int i = 0, pot = 0;
	
	if (argc != 3)	{
		printf("error: cantidad de parámetros incorrecta, debe ingresar 2 números\n");
		return 0;
	}
	
	if (atoi(argv[1]) < 1 || atoi(argv[2]) < 1)	{
		printf("error: debe ingresar números positivos\n");
		return 0;
	}
	
	pid_h1 = fork();

	if (pid_h1 != 0)	{
		
		pid_h2 = fork();
		
		if (pid_h2 != 0)	{
			printf("inicio padre\n");
			
			pot = atoi(argv[1]);
			for (i = 1; i < atoi(argv[2]); i++)	{
				pot = pot * atoi(argv[1]);
			}
				
			waitpid(pid_h1, NULL, 0);
			waitpid(pid_h2, NULL, 0);
			printf("potencia %d a la %d = %d\n", atoi(argv[1]), atoi(argv[2]), pot);
			printf("fin padre\n");	
			
		}
		else	{
			printf("inicio hijo 2\n");
			factorial(atoi(argv[1]));
			printf("fin hijo 2\n");
		}
	}
	else {
		printf("inicio hijo 1\n");
		factorial(atoi(argv[2]));
		printf("fin hijo 1\n");
	}
	
	
	return 0;
}

void factorial(int num)
{
	int valf = 1;
	
	while(num > 1)	{
		valf = valf * num;
		printf("%d x ", num);
		num--;
	}

	printf("1 = %d\n", valf);
}