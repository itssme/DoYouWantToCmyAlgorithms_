#ifndef GENETICMAZE_QUEUE_H
#define GENETICMAZE_QUEUE_H

typedef struct Point {
    int previous;
    int index;
} Point;

// old, old1, old2, current, next [read_index], next1, next2, [write_index], .., .. CAPACITY

typedef struct Queue {
    int read_index;
    int write_index;
    int capacity;
    Point* data;
} Queue;

Queue* newQueue();
void freeQueue(Queue** queue);
void queueInsert(Queue* queue, Point* point);
int queueRead(Queue* queue, Point* point, int* index);

#endif