#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // Se define el tipo de dato pid_t
#include <sys/wait.h> // Se define la función waitpid();
#include <unistd.h> // Contiene las definiciones de fork() y sleep().
#include <math.h> // Contiene algunas funcionalidades de matematicas

int main(int argc, char const *argv[])
{
    int numeroIngresado=0;
    char numeroEnTexto[5];
    int x, y, z, w;
    long valorFinal = 0;
    int numeros[5];
    char caracterAux;
    int i = 0;

    printf("Ingrese la potencia: ");

    scanf("%d", &numeroIngresado);

    printf("El número que ingresó es: %d\n", numeroIngresado);

    sprintf(numeroEnTexto, "%d", numeroIngresado);

    printf("El número en texto es %s\n", numeroEnTexto);

    x = numeroEnTexto[0] - '0';
    y = numeroEnTexto[1] - '0';
    z = numeroEnTexto[2] - '0';
    w = numeroEnTexto[3] - '0';

    printf("El valor de X %d\nEl valor de Y: %d\nEl valor de Z: %d\nEl valor de W: %d\n", x, y, z, w);
    valorFinal = pow(x, y) * pow(z, w);

    printf("El resultado de la operación del abuelo es %ld\n", valorFinal);

    return 0;
}
