#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int numero1;
    int numero2;
    if (argc>1)
    {
        numero1 = atoi(argv[1]);
        numero2 = atoi(argv[2]);

        printf("Y la suma es: %d\n", numero1 + numero2);
    }
    
    
    printf("cantidad de parametros: %d \n", argc);
    sleep(6);

    return 0;
}
