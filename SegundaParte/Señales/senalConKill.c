#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void capturar_senal(int iNumSen) {
    printf("Se recibió la señal %d\n", iNumSen);
}

void capturar_senal2(int iNumSen) {
    printf("Se recibió la señal %d en el método 2\n", iNumSen);
}

int main(int argc, char const *argv[])
{
    printf("Soy el proceso %d\n", getpid());
    printf("El valor de argc: %d\n", argc);
    int numeroDePid = atoi(argv[1]);
    printf("Le equiero enviar un kill al proceso %d\n", numeroDePid);

    kill(numeroDePid, SIGINT);
    printf("Le enviamos kill - SIGTERM al pid %d\n", numeroDePid);
    return 0;
}



