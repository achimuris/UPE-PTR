#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    
    sleep(3);


    fork();
    sleep(3);


    fork();
    sleep(3);

    fork();
    sleep(3);

    
    return 0;
}
