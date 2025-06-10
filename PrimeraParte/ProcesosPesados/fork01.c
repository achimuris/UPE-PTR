#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#include <stdlib.h>

int main(int argc, char const *argv[])
{
    
    printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
    pid_t unPID = fork();
    if (unPID != 0)
    {
        printf("Soy el proceso %d y mi padre es %d y el valor de unPID es %d\n", getpid(), getppid(), unPID);
        /* Espero a mi hijo */
        waitpid(unPID, NULL, 0);
    }else{
        if (unPID == -1)
        {
            printf("¡¡¡Ocurrio un error al generar el proceso hijo!!!!");
            return -1;
        }
        
        sleep(3);
        printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
        fork();
    }
    
    
    

    
    printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
    sleep(3);
    printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
    fork();
    printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
    sleep(3);
    printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
    
    return 0;
}
