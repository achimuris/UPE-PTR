#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
int main(void)
{
    system("clear");
    int menor, diferencia, diferencia2;
    unsigned int edades[40];
    int longitud = sizeof edades / sizeof edades[0];
    int x, existe, busqueda;
    int arreglo[] = {};

    clock_t tiempo_inicio, tiempo_final;
    double segundos;

    printf("Ingrese numero entero: \t");
    scanf("%i", &busqueda);

    clock_t start = clock();
    printf(" %f\n", start);
    pid_t pid;
    pid = fork();

    if (pid != 0)
    {
        pid = fork();
        if (pid != 0)
        {
            pid = fork();
            if (pid != 0)
            {
                pid = fork();
                if (pid != 0)
                {

                    // tiempo_inicio = clock();
                    waitpid(pid, NULL, 0);

                    sleep(6);

                    printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
                }
                else
                {
                    for (x = 0; x < longitud; x++)
                    {
                        edades[x] = pow(7, x);
                    }

                    for (int x = 0; x < longitud; x++)
                    {
                        if (arreglo[x] > busqueda)
                        {
                            existe = x - 1;
                            break;
                        }
                    }

                    existe--;
                    menor = edades[existe];
                    existe++;

                    diferencia = edades[existe] - busqueda;

                    diferencia2 = busqueda - menor;

                    if (diferencia < diferencia2)
                        printf("La potencia de 7 mas cercana a %d es=  %d\n", busqueda, edades[existe]);
                    else
                        printf("La potencia de 7 mas cercana a %d es=  %d\n", busqueda, menor);
                }

                waitpid(pid, NULL, 0);
            }
            else
            {

                for (x = 0; x < longitud; x++)
                {
                    edades[x] = pow(5, x);
                    //	printf("%i^%i= %u\n",num,x, edades[x]);
                }

                for (int x = 0; x < longitud; x++)
                {
                    if (arreglo[x] > busqueda)
                    {
                        existe = x - 1;
                        break;
                    }
                }

                existe--;
                menor = edades[existe];
                existe++;

                diferencia = edades[existe] - busqueda;

                diferencia2 = busqueda - menor;

                if (diferencia < diferencia2)
                    printf("La potencia de 5 mas cercana a %d es= %d\n", busqueda, edades[existe]);
                else
                    printf("La potencia de 5 mas cercana a %d es=  %d\n", busqueda, menor);
            }

            waitpid(pid, NULL, 0);
        }
        else
        {

            for (x = 0; x < longitud; x++)
            {
                edades[x] = pow(3, x);
                //	printf("%i^%i= %u\n",num,x, edades[x]);
            }

            for (int x = 0; x < longitud; x++)
            {
                if (arreglo[x] > busqueda)
                {
                    existe = x - 1;
                    break;
                }
            }

            existe--;
            menor = edades[existe];
            existe++;

            diferencia = edades[existe] - busqueda;

            diferencia2 = busqueda - menor;

            if (diferencia < diferencia2)
                printf("La potencia de 3 mas cercana a %d es= %d\n", busqueda, edades[existe]);
            else
                printf("La potencia de 3 mas cercana a %d es=  %d\n", busqueda, menor);
        }

        waitpid(pid, NULL, 0);
    }
    else
    {
        for (x = 0; x < longitud; x++)
        {
            edades[x] = pow(2, x);
        }

        for (int x = 0; x < longitud; x++)
        {
            if (arreglo[x] > busqueda)
            {
                existe = x - 1;
                break;
            }
        }

        existe--;
        menor = edades[existe];
        existe++;
        diferencia = edades[existe] - busqueda;

        diferencia2 = busqueda - menor;

        if (diferencia < diferencia2)
            printf("La potencia de 2 mas cercana a %d es= %d\n", busqueda, edades[existe]);
        else
            printf("La potencia de 2 mas cercana a %d es=  %d\n", busqueda, menor);
    }

    return 0;
}