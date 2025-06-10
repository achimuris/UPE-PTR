#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_A, sem_B, sem_C, sem_D, sem_E, sem_F;

// Función que representa la tarea de cocinar la panceta (hilo A)
void* cocinar_panceta(void* arg) {
    // Código para cocinar la panceta
        printf("Cocinando la panceta...\n");
    sleep(2);
    printf("La panceta está lista.\n");

    sem_post(&sem_D);

    return NULL;
}

// Función que representa la tarea de tostar el pan (hilo B)
void* tostar_pan(void* arg) {
    // Código para tostar el pan
    printf("Tostando el pan...\n");
    sleep(1);
    printf("El pan está tostado.\n");

    sem_post(&sem_D);

    return NULL;
}

// Función que representa la tarea de cortar la lechuga (hilo C)
void* cortar_lechuga(void* arg) {
    // Código para cortar la lechuga
    printf("Cortando la lechuga...\n");
    sleep(1);
    printf("La lechuga está cortada.\n");

    sem_post(&sem_D);

    return NULL;
}

// Función que representa la tarea de preparar el medallón (hilo D)
void* preparar_medallon(void* arg) {
    // Código para preparar el medallón
    printf("Preparando el medallón...\n");
    sleep(2);
    printf("El medallón está preparado.\n");

    sem_post(&sem_E);

    return NULL;
}

// Función que representa la tarea de cocinar el medallón (hilo E)
void* cocinar_medallon(void* arg) {
    // Esperar a que el hilo D termine
    sem_wait(&sem_E);

    // Código para cocinar el medallón
    printf("Cocinando el medallón...\n");
    sleep(2);
    printf("El medallón está cocinado.\n");

    sem_post(&sem_F);

    return NULL;
}

// Función que representa la tarea de armar la hamburguesa (hilo F)
void* armar_hamburguesa(void* arg) {
    // Esperar a que los hilos A, B, C y E terminen
    sem_wait(&sem_D);
    sem_wait(&sem_D);
    sem_wait(&sem_D);
    sem_wait(&sem_F);

    // Código para armar la hamburguesa
    printf("Armando la hamburguesa...\n");
    sleep(1);
    printf("La hamburguesa está lista.\n");

    return NULL;
}

int main() {
    pthread_t hilo_A, hilo_B, hilo_C, hilo_D, hilo_E, hilo_F;

    sem_init(&sem_A, 0, 0);
    sem_init(&sem_B, 0, 0);
    sem_init(&sem_C, 0, 0);
    sem_init(&sem_D, 0, 0);
    sem_init(&sem_E, 0, 0);
    sem_init(&sem_F, 0, 0);

    pthread_create(&hilo_A, NULL, cocinar_panceta, NULL);
    pthread_create(&hilo_B, NULL, tostar_pan, NULL);
    pthread_create(&hilo_C, NULL, cortar_lechuga, NULL);
    pthread_create(&hilo_D, NULL, preparar_medallon, NULL);
    pthread_create(&hilo_E, NULL, cocinar_medallon, NULL);
    pthread_create(&hilo_F, NULL, armar_hamburguesa, NULL);

    pthread_join(hilo_A, NULL);
    pthread_join(hilo_B, NULL);
    pthread_join(hilo_C, NULL);
    pthread_join(hilo_D, NULL);
    pthread_join(hilo_E, NULL);
    pthread_join(hilo_F, NULL);

    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);
    sem_destroy(&sem_D);
    sem_destroy(&sem_E);
    sem_destroy(&sem_F);

    return 0;
}