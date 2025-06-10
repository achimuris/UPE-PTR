#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_h1, sem_h2, sem_h3;

void* hilo1(void* arg) {
    while (1) {
        sem_wait(&sem_h1);
        sleep(1);
        printf("\nH1");
        fflush(stdout);  // Se utiliza fflush para asegurar que la salida se imprima inmediatamente
        sem_post(&sem_h2);
    }
    return NULL;
}

void* hilo2(void* arg) {
    while (1) {
        sem_wait(&sem_h2);
        sleep(1);
        printf("-H2");
        fflush(stdout);  // Se utiliza fflush para asegurar que la salida se imprima inmediatamente
        sem_post(&sem_h3);
        
    }
    return NULL;
}

void* hilo3(void* arg) {
    while (1) {
        sem_wait(&sem_h3);
        sleep(1);
        printf("-H3");
        fflush(stdout);  // Se utiliza fflush para asegurar que la salida se imprima inmediatamente
        sem_post(&sem_h3);
        sem_wait(&sem_h3);
        sem_post(&sem_h1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    sem_init(&sem_h1, 0, 1);
    sem_init(&sem_h2, 0, 0);
    sem_init(&sem_h3, 0, 0);

    pthread_create(&thread1, NULL, hilo1, NULL);
    pthread_create(&thread2, NULL, hilo2, NULL);
    pthread_create(&thread3, NULL, hilo3, NULL);

    sem_post(&sem_h1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    sem_destroy(&sem_h1);
    sem_destroy(&sem_h2);
    sem_destroy(&sem_h3);

    return 0;
}


/*#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


sem_t semaforo1, semaforo2, semaforo3, semaforo4;
void * H1(void * args)
{
    while(1)
    {

        sem_wait(&semaforo1);
        sleep(1);
        printf("\nH1");
        sem_post(&semaforo2);
    }

}

void * H2(void * args)
{
    while (1)
    {
        sem_wait(&semaforo2);
        sleep(1);
        printf("-H2");
        sem_post(&semaforo3);
    } 
}

void * H3(void * args)
{

    while(1){
        sleep(1);

        sem_wait(&semaforo3);
        printf("-H3");
        sem_post(&semaforo3);
        sem_post(&semaforo3);
    };
    
}



int main(int argc, char const *argv[])
{
    int nroCliente = 1;
    pthread_t hilo1, hilo2, hilo3;

    sem_init(&semaforo1, 0, 1);
    sem_init(&semaforo2, 0, 0);
    sem_init(&semaforo3, 0, 0);
    //sem_init(&semaforo4, 0, 0);
    pthread_create(&hilo1, NULL, H1, &nroCliente);
    pthread_create(&hilo2, NULL, H2, &nroCliente);
    pthread_create(&hilo3, NULL, H3, &nroCliente);


    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);




    return 0;
}
*/