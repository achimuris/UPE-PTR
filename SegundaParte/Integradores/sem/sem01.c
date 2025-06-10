#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>

void * LeerCobros(void *arguments);
void * LeerPedidos(void *arguments);
int saldo = 0;
sem_t semaforo1;

int main(int argc, char const *argv[])
{
    int nroCliente;
    pthread_t hilo1, hilo2;
    sem_init(&semaforo1, 0, 1);

    printf("Ingrese el número de cliente");
    scanf("%d", &nroCliente);
    

    while (nroCliente!=0)
    {
        pthread_create(&hilo1, NULL, LeerCobros, &nroCliente);
        pthread_create(&hilo2, NULL, LeerPedidos, &nroCliente);


        pthread_join(hilo1, NULL);
        pthread_join(hilo2, NULL);

        printf("El saldo del cliente %d es de %d\n", nroCliente, saldo);
        
        //Volvemos a colocar 0 en la variable global.
        saldo=0;

        //Acá pedimos que ingrese un nuevo cliente
        printf("Ingrese el número de cliente");
        scanf("%d", &nroCliente);
    }
    
    sem_destroy(&semaforo1);


    return 0;
}

void * LeerCobros(void *arguments)
{
    FILE *arch = NULL;
	char cadena[100], *token, fecc[11];
	int largo = 0, nrocampo = 0, poscampo = 0, clic = 0;
	double impc = 0.0;

	int cli = *((int *)arguments);
	
	if ( (arch = fopen("cobros.txt", "rt")) == NULL)	{
		printf("No se pudo abrir el archivo cobros.txt\n");
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
					clic = atoi(token);
				break;
				case 1:
					strncpy(fecc, token, strlen(token));
					fecc[strlen(token)] = '\0';
				break;
				case 2:
					impc = atoi(token);
				break;
			}
				
			nrocampo++;
		}
			
		if (cli == clic)	{
			
			sem_wait(&semaforo1);
			saldo += impc;
			sem_post(&semaforo1);
			
			//printf("cobro: %d - %s - %f\n", clic, fecc, impc);
		}
		
		
		
	}
		
	fclose(arch);
	
	//printf("El saldo del cliente %d es %f\n", clic, saldo);

}

void * LeerPedidos(void *arguments)
{
	FILE *arch = NULL;
	char cadena[100], *token;
	int largo = 0, nrocampo = 0, poscampo = 0, nump = 0, clip = 0;
	double impp = 0.0;
	
	int cli = *((int *)arguments);
	
	if ( (arch = fopen("pedidos_entregados.txt", "rt")) == NULL)	{
		printf("No se pudo abrir el archivo pedidos_entregados.txt\n");
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
					nump = atoi(token);
				break;
				case 1:
					clip = atoi(token);
				break;
				case 2:
					impp = atoi(token);
				break;
			}
				
			nrocampo++;
		}
		
		
		if (cli == clip)	{
			//sección crítica
			
			sem_wait(&semaforo1);
			saldo -= impp;
			sem_post(&semaforo1);
			
			//printf("pedido: %d - %d - %f\n", nump, clip, impp);
		}
		
	}
	
	fclose(arch);
	
	//printf("El saldo del cliente %d es %f\n", clip, saldo);
}
