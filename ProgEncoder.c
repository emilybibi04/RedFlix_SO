// Proyecto de Sistemas Operativos: RedFlix
// Emily Valarezo Plaza

#include "ProgEncoder.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void load_frames(const char *filename, int bitrate, int *frames, int *frame_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    *frame_count = 0;
    int frame;
    while (fscanf(file, "%d", &frame) != EOF) {
        if (*frame_count < BUFFER_SIZE / bitrate) {
            frames[(*frame_count)++] = frame;
        }
    }
    fclose(file);
}
