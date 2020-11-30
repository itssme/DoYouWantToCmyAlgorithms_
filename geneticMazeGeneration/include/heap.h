#ifndef GENETICMAZE_HEAP_H
#define GENETICMAZE_HEAP_H

#include "types.h"

// this struct would be better if it was only 16 bytes large (gcc will we able to put one point
//  into one xmm register and thus improve performance)
// maybe don't store x,y here but use backPointIdx to lookup those values in the
//  maze back array if needed (that would be O(1) anyway)
typedef struct Point {
    snumber x;
    snumber y;
    //snumber baseCost;
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