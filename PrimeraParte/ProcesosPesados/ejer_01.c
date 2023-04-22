#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>



/*
1) Desarrollar un programa que reciba dos parámetros y realice en simultáneo las
siguientes operaciones:
a) Factorial del primer número
b) Factorial del segundo número
c) El primer número elevado al segundo.
*/

int factorial(int);
double potencia (double, double);

int main(int argc, char *argv[]){

    int numero1 = atoi(argv[1]);
    int numero2 = atoi(argv[2]);
    int resultado = 0;

    pid_t pid_devuelto = 0;

    pid_devuelto = fork();

    if(pid_devuelto!=0){
        printf("Soy el padre %d, cree a (%d).\n", getpid(), pid_devuelto);

        resultado = factorial(numero1);

        printf("Soy el factorial del %d: %d\n", numero1, resultado);

        waitpid(pid_devuelto, NULL, 0);

         printf("Soy el padre y terminare\n");

    }else{
        printf("Soy el hijo %d y mi padre es %d\n",getpid(), getppid());

        pid_devuelto = fork();

        if(pid_devuelto==0){

        printf("Soy el Nieto %d y mi padre es %d\n",getpid(), getppid());

        resultado = potencia(numero1,numero2);

        printf("El numero %d elevado a %d: %d\n", numero1,numero2, resultado);

        }else{
        resultado = factorial(numero2);

        printf("Soy el factorial del %d: %d\n", numero2, resultado);

        waitpid(pid_devuelto, NULL, 0);
        printf("Soy el hijo  y terminare\n");

        }
    }


    return 0;
}

int factorial(int unNumero){

    printf("Soy %d\n", getpid());

    if (unNumero == 0) {
        return 1;
    } else {
        return unNumero * factorial(unNumero-1);
    }

}

double potencia(double numero1, double numero2){

    return pow(numero1,numero2);
}

/*double potencia(double numero1, double numero2){

    int potencia = 1;
    int i=0;
    while(i<numero2){
        potencia *= numero1;
        i++;
    }

    return potencia;
}*/