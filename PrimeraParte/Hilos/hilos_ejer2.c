#include <time.h>                                                   ///HILOS///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#define TamanioDelVector 3


/*
Desarrollar un programa que pida al usuario que ingrese un número entero.
Sobre el número ingresado, el programa deberá calcular en paralelo:
- La potencia de 2 más cercana a dicho número.
- La potencia de 3 más cercana a dicho número.
- La potencia de 5 más cercana a dicho número.
- La potencia de 7 más cercana a dicho número.
Finalmente, el programa deberá informar el tiempo que ha insumido realizar
desde que se ingresó el número hasta que se finalizaron todos los cálculos.
Ejemplo: Si el usuario ingresa el número 40:
- La potencia de 2 más cercana a dicho número: 32
- La potencia de 3 más cercana a dicho número: 27
- La potencia de 5 más cercana a dicho número. 25
- La potencia de 7 más cercana a dicho número. 49
*/


struct parametrosDeFuncionDeHilo
{
    int numero;
    int potencia;
} typedef parametro;


short numero_ingresado;
///--------------------------------------------------------------PROTOTIPOS-------------------------------------------------------------------------------///
void * CalcularPotencia(void *arg);
void TiempoEnSegundos();
///----------------------------------------------------------------MAIN------------------------------------------------------------------------------------///
int main()
{
///-------------------------------------------------------------MAIN THREADS--------------------------------------------------------------------------------///
    pthread_t Hilos[TamanioDelVector];
    

    printf("\nIngrese un Numero:\n");
    scanf("%hd",&numero_ingresado);

    parametro potenciaDe2;
    potenciaDe2.numero = numero_ingresado;
    potenciaDe2.potencia = 2;


    parametro potenciaDe3;
    potenciaDe3.numero = numero_ingresado;
    potenciaDe3.potencia = 3;

    
    
    pthread_create(&Hilos[0],NULL,CalcularPotencia, (void * )&potenciaDe2);
    pthread_create(&Hilos[1],NULL,CalcularPotencia, (void * )&potenciaDe3);


    pthread_join(Hilos[0],NULL);
    pthread_join(Hilos[1],NULL);
  
    return 0;
}
///-------------------------------------------------------------FUNCIONES-------------------------------------------------------------------------------///
void *CalcularPotencia(void *arg)
{
    short num;
    short aux;
    short indice;
    short potencia;
    
   
    parametro argu = *(parametro *)arg;
    
    num = argu.numero;
    potencia = argu.potencia;
    

    for(indice=0;indice<num;indice++)
    {
        aux=pow(potencia,indice);
        if(aux>=num)
        {
            indice=num;
            aux=aux/potencia;
        }
    }
    printf("\nLa potencia de %hd mas cercana a dicho numero es:%hd\n",potencia,aux);
}
///-------------------------------------------------------------FUNCIONES-------------------------------------------------------------------------------///
void TiempoEnSegundos()
{
    printf("\nEl Tiempo Transcurrido fue %.2fs \n",(float)clock()/CLOCKS_PER_SEC);
}