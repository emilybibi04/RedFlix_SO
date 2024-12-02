// Proyecto de Sistemas Operativos: RedFlix
// Emily Valarezo Plaza

#include "ProgStreamer.h"
#include <pthread.h>
#include <stdio.h>

void init_buffer(Buffer *buf) {
    buf->head = buf->tail = buf->count = 0;
    pthread_mutex_init(&buf->lock, NULL);
}

void push_to_buffer(Buffer *buf, int frame) {
    pthread_mutex_lock(&buf->lock);
    if (buf->count < MAX_BUFFER) {
        buf->buffer[buf->tail] = frame;
        buf->tail = (buf->tail + 1) % MAX_BUFFER;
        buf->count++;
    }
    pthread_mutex_unlock(&buf->lock);
}

int pop_from_buffer(Buffer *buf) {
    pthread_mutex_lock(&buf->lock);
    int frame = -1; // Valor predeterminado si el buffer está vacío.
    if (buf->count > 0) {
        frame = buf->buffer[buf->head];
        buf->head = (buf->head + 1) % MAX_BUFFER;
        buf->count--;
    }
    pthread_mutex_unlock(&buf->lock);
    return frame;
}
