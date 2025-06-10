#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * tarea_de_hilo (void * argumento);
void * otra_tarea_de_hilo (void * args)
{

    printf("Termine\n");
}


int main(int argc, char const *argv[])
{
    pthread_t tid, tid1;
    int valorParaEnviarAlHilo = 8;
    printf("Soy el proceso %d\n", getpid());
    //Creamos el hilo y le pasamos la tarea a ejecutar.
    int resultado = pthread_create(&tid, NULL, tarea_de_hilo, &valorParaEnviarAlHilo );
    int resultado1 = pthread_create(&tid1, NULL, otra_tarea_de_hilo, &valorParaEnviarAlHilo );

    pthread_join(tid, NULL);
    pthread_join(tid1, NULL);

    // if (resultado != 0)
    // {
    //     printf("Hubo un error al crear el hilo\n");
    // }else{
    //     printf("¡El hilo se creo exitosamente!\n");
    //      pthread_join(tid, NULL);  
    //     printf("Termine de esperar al hilo");
    // }
    
    /* code */
    return 0;
}

void * tarea_de_hilo (void * argumento)
{
    int valorQueRecibeElHilo = *(int *)argumento;

    printf("Soy el hilo %d y recibí por parametro %d\n", pthread_self(), valorQueRecibeElHilo);
    sleep(4);
    printf("Algo más\n");
}
