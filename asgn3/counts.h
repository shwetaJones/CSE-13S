#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t compCount;
uint32_t swapCount;

bool comparisons(uint32_t *i, uint32_t *j);
void swaps(uint32_t *i, uint32_t *j);

#endif
