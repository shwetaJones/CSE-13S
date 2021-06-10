#include "quick.h"

#include "counts.h"
#include "queue.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t b = lo - 1;
    int64_t c = hi + 1;
    while (b < c) {
        b++;
        while (comparisons(&A[b], &pivot) == true) {
            b++;
        }
        c--;
        while (comparisons(&pivot, &A[c]) == true) {
            c--;
        }
        if (b < c) {
            swaps(&A[b], &A[c]);
        }
    }
    return c;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t hi = 0;
    int64_t lo = n - 1;
    Stack *Q = stack_create(n);
    if (stack_push(Q, hi) == true && stack_push(Q, lo) == true) {
        while (stack_empty(Q) != true) {
            if (stack_pop(Q, &hi) == true && stack_pop(Q, &lo) == true) {
                int64_t p = partition(A, lo, hi);
                if (lo < p) {
                    stack_push(Q, lo);
                    stack_push(Q, p);
                }
                if (hi > p + 1) {
                    stack_push(Q, (p + 1));
                    stack_push(Q, hi);
                }
            }
        }
        stack_delete(&Q);
    }
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t hi = 0;
    int64_t lo = n - 1;
    Queue *Q = queue_create(n);
    if (enqueue(Q, hi) == true && enqueue(Q, lo) == true) {
        while (queue_full(Q) == true) {
            if (dequeue(Q, &lo) == true && dequeue(Q, &hi) == true) {
                int64_t p = partition(A, lo, hi);
                if (lo < p) {
                    enqueue(Q, lo);
                    enqueue(Q, p);
                }
                if (hi > p + 1) {
                    enqueue(Q, (p + 1));
                    enqueue(Q, hi);
                }
            }
        }
        queue_delete(&Q);
    }
}
