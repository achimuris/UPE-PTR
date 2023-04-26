#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

typedef struct emple {
	int leg;
	char nom[20];
	int edad;
} emple;



FILE *arch = NULL;
emple data;
char cadena[100], *token;
int largo = 0, nrocampo = 0, poscampo = 0, cant_reg_m50 = 0, empleado = 0;


int main()
{
	pid_t pid_h1 = 0;

	pid_h1 = fork();

	if (pid_h1 != 0)	{
		
		printf("inicio padre\n");
		
		if ( (arch = fopen("empleados.txt", "rt")) == NULL)	{
			printf("Padre: No se pudo abrir el archivo empleados.txt\n");
			return 0;
		}
		

		while (fgets(cadena, 100, arch) != NULL)	{
			// obtengo un registro 
			cadena[strlen(cadena)-1] = '\0';
			
			// ahora tengo que separar cada campo del registro
			largo = strlen(cadena);
			
			nrocampo = poscampo = 0;
			
			while (poscampo < largo)	{
				
				token = strtok(&cadena[poscampo], "\t");
				poscampo += strlen(token) + 1;
			
				switch(nrocampo)	{
					case 0:
						data.leg = atoi(token);
					break;
					case 1:
						strncpy(data.nom, token, strlen(token));
						data.nom[strlen(token)] = '\0';
					break;
					case 2:
						data.edad = atoi(token);
					break;
				}
				
				nrocampo++;
			}
			
			//printf("dato: %d - %s - %d\n", data.leg, data.nom, data.edad);
			if (data.edad > 50)
				cant_reg_m50++;
			
		}

		fclose(arch);
		waitpid(pid_h1, NULL, 0);
		printf("cantidad de empleados con edad mayor a 50 años %d\n", cant_reg_m50);
		printf("fin padre\n");	

	}
	else {
		printf("inicio hijo 1\n");
		
		do {
			printf("Ingrese un número de empleado (para finalizar 0) \n");
			scanf("%d", &empleado);
	
			if ( (arch = fopen("empleados.txt", "r")) == NULL)	{
				printf("Hijo: No se pudo abrir el archivo empleados.txt\n");
				return 0;
			}
			
			while (fgets(cadena, 100, arch) != NULL)	{
				// obtengo un registro 
				cadena[strlen(cadena)-1] = '\0';
			
				// ahora tengo que separar cada campo del registro
				largo = strlen(cadena);
			
				nrocampo = poscampo = 0;
			
				while (poscampo < largo)	{
				
					token = strtok(&cadena[poscampo], "\t");
					poscampo += strlen(token) + 1;
			
					switch(nrocampo)	{
						case 0:
							data.leg = atoi(token);
						break;
						case 1:
							strncpy(data.nom, token, strlen(token));
							data.nom[strlen(token)] = '\0';
						break;
						case 2:
							data.edad = atoi(token);
						break;
					}
				
					nrocampo++;
				}
			
				if (data.leg == empleado)	{
					printf("info del empleado: %d - %s - %d\n", data.leg, data.nom, data.edad);
					fclose(arch);
				}
			
			}
		
		}	while(empleado != 0);

		
		printf("fin hijo 1\n");
	}
	
	
	return 0;
}
