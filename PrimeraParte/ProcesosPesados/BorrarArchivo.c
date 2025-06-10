#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include "webinter.h"
#include "comgral.h"
#include "webinter.sch"

#define EMP0 0
#define CODPAR 90
#define NRORENG 0

struct FileData {
    char name[256];
    time_t creationTime;
};

// Función de comparación para qsort()
int compare(const void *a, const void *b) {
    struct FileData *fileA = (struct FileData *)a;
    struct FileData *fileB = (struct FileData *)b;
    return (fileA->creationTime - fileB->creationTime);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    struct FileData files[1000];  // Array para almacenar los archivos
    int fileCount = 0;
    time_t currentTime = time(NULL);  // Tiempo actual
    //Esta hardcoding 30 días
    const int THIRTY_DAYS_IN_SECONDS = 30 * 24 * 60 * 60;  // 30 días en segundos

    // Nombre del directorio
    strcpy(directory, GetParNov(EMP0, CODPAR, NRORENG, Today()));

    // Abrir el directorio
    if ((dir = opendir(directory)) == NULL) {
        perror("No se puede abrir el directorio");
        return 1;
    }

    // Leer cada archivo en el directorio
    while ((entry = readdir(dir)) != NULL) {
        // Saltar directorios "." y ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construir el path completo del archivo
        char fullPath[512];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", directory, entry->d_name);

        // Obtener información del archivo
        if (stat(fullPath, &fileStat) == -1) {
            perror("No se puede obtener información del archivo");
            continue;
        }

        // Verificar si el archivo fue creado en los últimos 30 días
        if (difftime(currentTime, fileStat.st_ctime) <= THIRTY_DAYS_IN_SECONDS) {
            // Almacenar nombre y tiempo de creación en el array
            strncpy(files[fileCount].name, entry->d_name, sizeof(files[fileCount].name) - 1);
            files[fileCount].creationTime = fileStat.st_ctime;
            fileCount++;
        }
    }

    closedir(dir);

    // Ordenar los archivos por tiempo de creación
    qsort(files, fileCount, sizeof(struct FileData), compare);

    // Imprimir los archivos creados en los últimos 30 días, ordenados
    printf("Archivos creados en los últimos 30 días:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s - Creado el: %s", files[i].name, ctime(&files[i].creationTime));
    }

    return 0;
}
