#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct emple {
	int leg;
	//char nom[10];
	//int edad;
};

int main()
{
	pid_t pid_h1 = 0;
	struct emple data;
	int a = 0;
    char caracteres[100];
	FILE *arch = NULL;
	
	//pid_h1 = fork();

	//if (pid_h1 != 0)	{
		
		printf("inicio padre\n");
		
		if ( (arch = fopen("empleados.txt", "r")) == NULL)	{
			printf("Padre: No se pudo abrir el archivo empleados.txt\n");
			return 0;
		}
		

		while (!feof(arch))	{

            fgets(caracteres, sizeof(int), arch);
            a = atoi(caracteres);

			//fread((void *)&a, sizeof(int), 1, arch);
            
	
			printf("data: %d\n", a);

		}
		
		
				//printf("data: %d - %s - %d\n", data.leg, data.nom, data.edad);
		fclose(arch);
		//waitpid(pid_h1, NULL, 0);
		printf("fin padre\n");	

	//}
	//else {
	//	printf("inicio hijo 1\n");
		
		/*if ( (arch = fopen("empleados.txt", "r")) == NULL)	{
			printf("Hijo: No se pudo abrir el archivo empleados.txt\n");
			return 0;
		}

		fclose(arch);*/
		//printf("fin hijo 1\n");
	//}
	
	
	return 0;
}