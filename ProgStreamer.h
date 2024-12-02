// Proyecto de Sistemas Operativos: RedFlix
// Emily Valarezo Plaza

#ifndef STREAMER_H
#define STREAMER_H

#include <pthread.h>

#define MAX_BUFFER 1024

typedef struct {
    int buffer[MAX_BUFFER];
    int head;
    int tail;
    int count;
    pthread_mutex_t lock;
} Buffer;

// Declaraciones
void init_buffer(Buffer *buf);
void push_to_buffer(Buffer *buf, int frame);
int pop_from_buffer(Buffer *buf);

#endif // STREAMER_H