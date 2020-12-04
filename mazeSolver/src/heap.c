#include <stdlib.h>
#include <string.h>
#include "heap.h"

Heap* newHeap() {
    Heap* heap = malloc(sizeof(Heap));

    heap->size = 0;
    heap->capacity = 16;
    heap->data = malloc(sizeof(Point) * heap->capacity);

    return heap;
}

void freeHeap(Heap** heap) {
    if (heap != NULL) {
        free((*heap)->data);
        free(*heap);
        *heap = NULL;
    }
}

void clearHeap(Heap* heap) {
    heap->size = 0;
}

static void setPoint(Heap* heap, snumber index, Point* point) {
    memcpy(heap->data + index, point, sizeof(Point));
}

void heapInsert(Heap* heap, Point* point) {
    if (heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, sizeof(Point) * heap->capacity);
    }
    snumber index = heap->size;
    setPoint(heap, index, point);
    heap->size++;

    while (index != 0) {
        snumber parent = (index - 1) >> 1; // div 2
        if (heap->data[index].heuCost >= heap->data[parent].heuCost) {
            return;
        }
        Point tmp;
        memcpy(&tmp, heap->data + index, sizeof(Point));
        setPoint(heap, index, heap->data + parent);
        setPoint(heap, parent, &tmp);
        index = parent;
    }
}

snumber heapExtract(Heap* heap, Point* point) {
    if (heap->size == 0) return 0;

    memcpy(point, heap->data, sizeof(Point));
    heap->size--;
    setPoint(heap, 0, heap->data + (heap->size));

    snumber parent = 0;

    while (1) {
        snumber left_child = parent * 2 + 1;
        if (left_child >= heap->size) {
            return 1;
        }

        snumber right_child = left_child + 1;
        if (right_child >= heap->size) {
            if (heap->data[left_child].heuCost < heap->data[parent].heuCost) {
                Point tmp;
                memcpy(&tmp, heap->data + parent, sizeof(Point));
                setPoint(heap, parent, heap->data + left_child);
                setPoint(heap, left_child, &tmp);
            }

            return 1;
        }

        if (heap->data[left_child].heuCost < heap->data[parent].heuCost &&
            heap->data[left_child].heuCost <= heap->data[right_child].heuCost) {
            Point tmp;
            memcpy(&tmp, heap->data + parent, sizeof(Point));
            setPoint(heap, parent, heap->data + left_child);
            setPoint(heap, left_child, &tmp);
            parent = left_child;
        } else if (heap->data[right_child].heuCost < heap->data[parent].heuCost) {
            Point tmp;
            memcpy(&tmp, heap->data + parent, sizeof(Point));
            setPoint(heap, parent, heap->data + right_child);
            setPoint(heap, right_child, &tmp);
            parent = right_child;
        } else {
            return 1;
        }
    }
}