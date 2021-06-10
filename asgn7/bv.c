#include "bv.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Referenced code by Sahiti
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv == NULL) {
        return NULL;
    }
    bv->length = length;
    bv->vector = (uint8_t *) calloc((length / 8), sizeof(uint8_t));
    if (bv->vector == NULL) {
        free(bv);
        return NULL;
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

// Referenced old code and code from Sahiti
void bv_set_bit(BitVector *bv, uint32_t i) {
    uint8_t mask = 1 << (i % 8);
    bv->vector[i / 8] = bv->vector[i / 8] & mask;
}

// Referenced old code and code from Sahiti
void bv_clr_bit(BitVector *bv, uint32_t i) {
    uint8_t mask = ~(1 << (i % 8));
    bv->vector[i / 8] = bv->vector[i / 8] & mask;
}

// Referenced old code and code from Sahiti
uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    uint8_t mask = 1 << (i % 8);
    return (bv->vector[i / 8] & mask) >> (i % 8);
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        printf("%d", bv_get_bit(bv, i));
    }
    printf("\n");
}
