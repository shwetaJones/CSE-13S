#include "bubble.h"

#include "counts.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(uint32_t *A, uint32_t n) {
    uint32_t ival = n - 1;
    uint32_t i = 0;
    while (i < ival) {
        uint32_t j = i + 1;
        while (j < n) {
            if (comparisons(&A[j], &A[i]) == true) {
                swaps(&A[j], &A[i]);
            }
            j++;
        }
        i++;
    }
}
