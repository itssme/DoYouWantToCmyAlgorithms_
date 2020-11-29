#ifndef GENETICMAZE_HEAP_H
#define GENETICMAZE_HEAP_H

#include "types.h"

typedef struct Point {
    snumber x;
    snumber y;
    snumber baseCost;
    snumber backPointIdx;
    float heuCost;
} Point;

typedef struct Heap {
    snumber size;
    snumber capacity;
    Point* data;
} Heap;

Heap* newHeap();
void freeHeap(Heap** heap);
void clearHeap(Heap* heap);
void heapInsert(Heap* heap, Point* point);
snumber heapExtract(Heap* heap, Point* point);

#endif