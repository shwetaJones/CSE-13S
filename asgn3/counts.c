#include "counts.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t compCount = 0;
uint32_t swapCount = 0;

bool comparisons(uint32_t *i, uint32_t *j) {
    compCount += 1;
    if (*i < *j == true) {
        return true;
    } else {
        return false;
    }
}

void swaps(uint32_t *i, uint32_t *j) {
    swapCount += 3;
    int temp = *i;
    *i = *j;
    *j = temp;
}
