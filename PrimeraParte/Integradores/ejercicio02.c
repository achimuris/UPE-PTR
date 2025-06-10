#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/* VARIABLES GLOBALES */
char  CUIL_EMPRESA_MUDANZA[14];
typedef struct cliente
{
    long    DNI;
    char  CUIL[14];
    short   correspondeIVA;
    float   monto;
} datocli;

datocli gDatoCliente;

void * informarAFIP (void * argumentos)
{
    sleep(2);
    datocli clienteRecibido = *(datocli *)argumentos;
    printf("PID HILO (%d) - Finalizó el envio a la AFIP la compra del cliente %s\n", pthread_self(), clienteRecibido.CUIL);
}

void * guardarBBDD (void * argumentos)
{
    sleep(3);
    datocli clienteRecibido = *(datocli *)argumentos;
    printf("Guardamos el DNI: %ld CUIL: %s\n", clienteRecibido.DNI, clienteRecibido.CUIL);
    printf("PID HILO (%d) - Finalizó el guardado en la BBDD\n", pthread_self());
}

/*PROTOTIPO DE FUNCIONES*/
void ImprimirFactura(datocli unCliente);

/*Desarrollar un programa con la siguiente premisa:
Siempre que se genera una factura, automáticamente, se envía una
notificación a la AFIP indicando DNI del cliente, CUIL de la empresa y el
monto total final (si corresponde IVA, deberá sumar el 21% del monto
informado).
La empresa que nos solicita el desarrollo de esta aplicación se encarga
de realizar servicios de mudanzas.
El CUIL de nuestra empresa es el siguiente: 50-77777777-7, este dato
deberá leerlo de un archivo de texto llamado “cuil.txt”.
El programa deberá solicitar, en primer lugar, los datos del cliente:
- DNI
- CUIL
- Si corresponde IVA o no.
- Monto a cobrar
Este programa deberá realizar concurrentemente:
- Informar a la AFIP (demora aleatoria entre 2 y 4 segundos). Simular
esta acción haciendo un sleep de entre 2 y 4 segundos e imprimiendo
en pantalla que finalizó el envío a la AFIP (al finalizar el sleep).
- Guardar la compra en nuestra base de datos (demora random entre 1
y 3 segundos, simular con sleep). Imprimir en pantalla: “Se ha
guardado en la base de datos” (al finalizar el sleep)
- Imprimir por consola la factura, indicando los datos del cliente y el
monto final. Siempre y cuando, ya se haya informado a la AFIP y se
haya persistido la compra en la base de datos.
Siempre imprimir por consola el ID de cada proceso o subproceso*/

int main(int argc, char const *argv[])
{
    pthread_t hilo1;
    pthread_t hilo2;

    strcpy(CUIL_EMPRESA_MUDANZA, "50-77777777-7");
    printf("Ingrese los datos del cliente\n");
    gDatoCliente.correspondeIVA = 1;
    gDatoCliente.DNI = 1231231;
    gDatoCliente.monto = 85012;
    strcpy(gDatoCliente.CUIL, "UN CUIL");


    printf("Ya cargó los datos del cliente\n");
    printf("Proceso principal PID: %d\n", getpid());

    pthread_create(&hilo1, NULL, informarAFIP, &gDatoCliente);
    pthread_create(&hilo2, NULL, guardarBBDD,  &gDatoCliente);


    /* Esperamos a que finalicen los hilos  */
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    ImprimirFactura(gDatoCliente);


    /* code */
    return 0;
}

void ImprimirFactura(datocli unCliente)
{

    printf("La factura se imprime...\n");
    printf("Datos del cliente:\n");
    printf("CUIL EMPRESA: %s\n", CUIL_EMPRESA_MUDANZA);

    if (unCliente.correspondeIVA != 0)
    {
        printf("MONTO FINAL: %f\n", unCliente.monto * 1.21);
    }else{
        printf("MONTO FINAL: %f\n", unCliente.monto);
    }
}
