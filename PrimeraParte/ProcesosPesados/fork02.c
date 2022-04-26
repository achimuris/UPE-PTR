#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid_devuelto;
    printf("Soy %d\n", getpid());

    pid_devuelto = fork();

    printf("Por solicitud de Nicolas. Mi PID es %d\n", getpid());

    // Código del PADRE
    if (pid_devuelto != 0)
    {
        printf("Soy el padre %d, cree a %d. Valor de pid_devuelto: %d\n", getpid(), pid_devuelto, pid_devuelto);
        sleep(1);

        // Esperamos a que finalice el hijo.
        waitpid(pid_devuelto, NULL, 0);
    }
    else
    {
        printf("Soy el hijo %d, y dormiré 4 segundos. Valor de pid_devuelto: %d\n", getpid(), pid_devuelto);
        sleep(4);
        printf("Soy el hijo %d y termine!!\n", getpid());
    }

    printf("Antes de ejecutar el return 0; Mi PID es %d\n", getpid());

    return 0;
}
