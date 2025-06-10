/*
Desarrollar un programa que al ejecutarse solicite números al usuario hasta que se
ingrese 0. Para cada número ingresado se deberá crear un nuevo proceso que
realice las siguientes operaciones:
a) Factorial
b) Potencia al cubo de ese número
c) Raíz cuadrada del número
d) Suma desde 1 hasta el número (Ejemplo con 4: 1 + 2 + 3 +4=9)
Cada una de estas operaciones deberá ser realizada por un hilo independiente.
Debe garantizarse la concurrencia. Es decir, cuando el usuario ingresa un número
no deberá esperar hasta que se informen los resultados, sino que deberá poder
seguir ingresando números.

*/

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

long long factorial(int n);
double raizCuadrada(int n);
double potenciaAlCubo(int n);

int main(int argc, char const *argv[])
{
    int num;
    
    pid_t pid_factorial;
    pid_t pid_raiz;
    pid_t pid_potencia;

    printf("Ingrese un número entero positivo: ");
    scanf("%d", &num);

    while(num != 0)
    {
        // pid_factorial = fork();
        // if (pid_factorial != 0)
        // {
        //     long long fact = factorial(num);
        //     printf("El factorial de %d es %llu\n", num, fact);
        //     return 0;
        // }

        pid_raiz = fork();

        if (pid_raiz != 0)
        {
            printf("La raíz cuadrada de %d es %f\n", num, raizCuadrada(num));
            return 0;
        }

        pid_potencia = fork();
        if (pid_potencia != 0)
        {
            printf("La potencia al cubo de %d es %f\n", num, potenciaAlCubo(num));
            return 0;
        }

        //Esto siempre es bloque del padre
        waitpid(pid_potencia, NULL, 0);
        waitpid(pid_raiz, NULL, 0);
        waitpid(pid_factorial, NULL, 0);


        printf("Ingrese un número entero positivo: ");
        scanf("%d", &num);
    }

    printf("Terminé\n");
    

    return 0;
}

long long factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

double raizCuadrada(int n)
{
    return sqrt(n);
}
double potenciaAlCubo(int n)
{
    return (n * n * n);
}


