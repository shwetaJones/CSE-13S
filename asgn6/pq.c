#include "pq.h"

#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stio.h>
#include <unistd.h>

PriorityQueue *pq_create(uint32_t capacity) {
}

void pq_delete(PriorityQueue **q) {
}

bool pq_empty(PriorityQueue *q) {
    if (pq->size == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    if (pq->size == pq->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
}

bool dequeue(PriorityQueue *q, Node **n) {
}

void pq_print(PriorityQueue *q) {
}
