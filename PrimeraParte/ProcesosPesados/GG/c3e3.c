#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



int main()
{
	pid_t pid_h1 = 0;
	pid_t pid_h2 = 0;
	pid_t pid_h3 = 0;
	
	pid_h1 = fork();
	
	if (pid_h1 != 0)	{
		
		pid_h2 = fork();
		
		if (pid_h2 != 0)	{
		
			pid_h3 = fork();
			
			if (pid_h3 != 0)	{
				waitpid(pid_h1, NULL, 0);
				waitpid(pid_h2, NULL, 0);
				waitpid(pid_h3, NULL, 0);
				printf("en proceso\n");
			
				pid_h1 = fork();
	
				if (pid_h1 != 0)	{
		
					pid_h2 = fork();
		
					if (pid_h2 != 0)	{
		
						pid_h3 = fork();
			
						if (pid_h3 != 0)	{
							waitpid(pid_h1, NULL, 0);
							waitpid(pid_h2, NULL, 0);
							waitpid(pid_h3, NULL, 0);
							printf("Fin\n");
				
						}
						else	{
							printf("inicio hijo 6 pid %d\n", getpid());
							printf("fin hijo 6\n");
						}
					}
					else	{
						printf("inicio hijo 5 pid %d\n", getpid());
						printf("fin hijo 5\n");
					}
				}
				else {
					printf("inicio hijo 4 pid %d\n", getpid());
					printf("fin hijo 4\n");
				}
			}
			else	{
				printf("inicio hijo 3 pid %d\n", getpid());
				printf("fin hijo 3\n");
			}
		}
		else	{
			printf("inicio hijo 2 pid %d\n", getpid());
			printf("fin hijo 2\n");
		}
	}
	else {
		printf("inicio hijo 1 pid %d\n", getpid());
		printf("fin hijo 1\n");
	}
	
	
	
	
	
	
	return 0;
}

