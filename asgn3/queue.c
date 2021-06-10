#include "queue.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Refered to pseudocode provided by Sahiti during section
struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};

// Creates the queue with capacity from user
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

// Clears through the queue
void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

// Returns whether the queue is empty or not
bool queue_empty(Queue *q) {
    if (q->size == 0) {
        return true;
    } else {
        return false;
    }
}

// Returns if the queue is full or not
bool queue_full(Queue *q) {
    if (q->size == q->capacity) {
        return true;
    } else {
        return false;
    }
}

// Returns size of the queue
uint32_t queue_size(Queue *q) {
    return q->size;
}

// Adds to the tail
bool enqueue(Queue *q, int64_t x) {
    if (q->size == q->capacity) {
        return false;
    }
    q->size += 1;
    q->items[q->tail] = x;
    q->tail = (q->tail + 1) % q->capacity;
    return true;
}

// Removes from the head
bool dequeue(Queue *q, int64_t *x) {
    if (q->size == 0) {
        return false;
    }
    q->size -= 1;
    *x = q->items[q->head];
    q->head = (q->head + 1) % q->capacity;
    return true;
}

// Prints the values from queue
void queue_print(Queue *q) {
    for (uint32_t i = q->head; i <= q->tail; i++) {
        printf("%ld ", q->items[i]);
    }
}

//int main(void){
//Queue *q = queue_create(3);
//printf("%d", queue_size(q));
//enqueue(q, 1);
//queue_print(q);
//return 0;
//}
