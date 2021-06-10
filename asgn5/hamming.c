#include "hamming.h"

#include "bm.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//typedef enum HAM_STATUS {
//HAM_OK = -3,
//HAM_ERR = -2,
//HAM_CORRECT	=-1,
//} HAM_STATUS;

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *A = bm_create(1, 4);
    uint8_t mask = 1;
    uint8_t bit;
    for (uint32_t i = 0; i < 4; i++) {
        bit = (msg >> i) & mask;
        if (bit == 1) {
            bm_set_bit(A, 0, i);
        }
    }
    BitMatrix *answer = bm_multiply(A, G);
    uint8_t val = bm_to_data(answer);
    return val;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *B = bm_create(1, 8);
    for (uint8_t i = 0; i < 8; i++) {
        //uint8_t mask = 1 << i;
        //bit = (code & mask) >> i;
        if (code % 2 == 1) {
            bm_set_bit(B, 0, i);
        }
    }
    *msg += 1;
    uint8_t final = 0x00;
    BitMatrix *answer = bm_multiply(B, Ht);
    //printf("%d", bm_rows(answer));
    for (uint32_t j = 0; j < 8; j++) {
        uint8_t value = bm_get_bit(answer, 0, j);
        final |= value << j;
    }
    //printf("%d", final);
    BitMatrix *result = bm_from_data(final, 8);
    if (bm_rows(result) > bm_rows(Ht)) {
        return HAM_ERR;
    }
    return HAM_OK;
}
