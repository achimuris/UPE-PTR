#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    
    pid_t pid_devuelto = 15;

    pid_devuelto = fork();

    
    printf("getpid() %d - pid_devuelto %d\n", getpid(), pid_devuelto);
    
    
    
    return 0;
}
