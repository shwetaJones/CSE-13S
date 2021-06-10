#include "shell.h"

#include "counts.h"
#include "gaps.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(uint32_t *A, uint32_t n) {
    int i = 0;
    while (i < GAPS) {
        uint32_t gap = gaps[i];
        for (uint32_t k = gap; k < n; k++) {
            uint32_t j = k;
            uint32_t m = A[k];
            while (j >= gap && comparisons(&m, &A[j - gap]) == true) {
                swaps(&A[j], &A[j - gap]);
                j -= gap;
            }
            A[j] = m;
        }
        i++;
    }
}
