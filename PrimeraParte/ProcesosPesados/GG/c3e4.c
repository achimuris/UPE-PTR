#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int potencia(int, int);

int main()
{
	int num = 0, i = 0, pot = 0, resant = 0, resdes = 0, res = 0;
	pid_t pid_h1 = 0;
	pid_t pid_h2 = 0;
	pid_t pid_h3 = 0;
	pid_t pid_h4 = 0;
	
	printf("Ingrese un número entero: ");
	scanf("%d", &num);
	
	pid_h1 = fork();
	
	if (pid_h1 != 0)	{
		
		pid_h2 = fork();
		
		if (pid_h2 != 0)	{
		
			pid_h3 = fork();
			
			if (pid_h3 != 0)	{
				
				pid_h4 = fork();
				
				if (pid_h4 != 0)	{
				
					printf("inicio padre pid %d\n", getpid());
					waitpid(pid_h1, NULL, 0);
					waitpid(pid_h2, NULL, 0);
					waitpid(pid_h3, NULL, 0);
					waitpid(pid_h4, NULL, 0);
					printf("fin padre\n");
					
				
				}
				else {
					printf("inicio hijo 4 pid %d\n", getpid());
					for (i = 0; resdes < num; i++)
						resdes = potencia(7, i);
		
					i -= 2;
					resant = potencia(7, i);
					
					if ( (num - resant) < (resdes - num))
						res = resant;
					else
						res = resdes;
		
					printf("fin hijo 4: potencia de 7 más cercada a %d es %d\n", num, res);
				}
			}
			else	{
				printf("inicio hijo 3 pid %d\n", getpid());
				for (i = 0; resdes < num; i++)
					resdes = potencia(5, i);
		
				i -= 2;
				resant = potencia(5, i);
				
				if ( (num - resant) < (resdes - num))
					res = resant;
				else
					res = resdes;
		
				printf("fin hijo 3: potencia de 5 más cercana a %d es %d\n", num, res);
			}
		}
		else	{
			printf("inicio hijo 2 pid %d\n", getpid());
			for (i = 0; resdes < num; i++)
				resdes = potencia(3, i);
		
			i -= 2;
			resant = potencia(3, i);
			
			if ( (num - resant) < (resdes - num))
				res = resant;
			else
				res = resdes;
		
			printf("fin hijo 2: potencia de 3 más cercana a %d es %d\n", num, res);
		}
	}
	else {
		printf("inicio hijo 1 pid %d\n", getpid());
		
		for (i = 0; resdes < num; i++)	{
			resdes = potencia(2, i);
			//printf("2 a la %d = res %d\n", i, res);
		}
		
		i -= 2;
		resant = potencia(2, i);
		
		//printf("%d -%d < %d - %d\n", num, resant, resdes, num);
		
		if ( (num - resant) < (resdes - num))
			res = resant;
		else
			res = resdes;
		
		printf("fin hijo 1: potencia de 2 más cercana a %d es %d\n", num, res);
	}
	
	
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