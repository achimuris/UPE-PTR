#include <stdio.h>
#include <sys/types.h> // Se define el tipo de dato pid_t
#include <sys/wait.h> // Se define la función waitpid();
#include <unistd.h> // Contiene las definiciones de fork() y sleep().

int main(int argc, char * argv[]) 
{
    // printf("La cantidad de argumentos: %d\n", argc);
    // for (int i = 0; i < argc; i++)
    // {
    //     printf("El parametro %d tiene el valor %s\n", (i + 1), argv[i]);
    // }
    
    pid_t pid_devuelto=0; 
    printf("Soy %d y mi padre es %d\n", getpid(), getppid());//La función getpid() devuelve el PID

    pid_devuelto=fork();

    if(pid_devuelto!=0) {
        printf("Soy el padre %d, cree a (%d).\n",    getpid(),pid_devuelto); 
        sleep(1);
        waitpid(pid_devuelto, NULL, 0);
    } 
    else {
        printf("Soy el hijo %d y dormiré 4s.\n",getpid()); 
        sleep(4); 
        printf("Soy el hijo, terminaré.\n"); 
    }


    return 0; 
}
