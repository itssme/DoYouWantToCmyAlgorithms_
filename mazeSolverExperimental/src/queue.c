#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"

Queue* newQueue() {
    Queue* queue = malloc(sizeof(Queue));

    queue->write_index = 0;
    queue->read_index = 0;
    queue->capacity = 64;
    queue->data = malloc(sizeof(Point) * queue->capacity);

    return queue;
}

void freeQueue(Queue** queue) {
    if (queue != NULL) {
        free((*queue)->data);
        free(*queue);
        *queue = NULL;
    }
}

void queueInsert(Queue* queue, Point* point) {
    if (queue->write_index >= queue->capacity) {
        queue->capacity *= 2;
        queue->data = realloc(queue->data, sizeof(Point) * queue->capacity);
    }
    memcpy(queue->data + queue->write_index, point, sizeof(struct Point));
    queue->write_index++;
}

int queueRead(Queue* queue, Point* point, int* index) {
    if (queue->read_index >= queue->write_index) return 0;

    memcpy(point, queue->data + queue->read_index, sizeof(struct Point));
    *index = queue->read_index;
    queue->read_index++;
    return 1;
}

