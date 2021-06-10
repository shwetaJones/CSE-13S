#include "bm.h"

#include "bv.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

// Referenced code provided in Sahiti's section
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    m->vector = bv_create(rows * cols);
    return m;
}

// Referenced code provided in Sahiti's section
void bm_delete(BitMatrix **m) {
    //for (uint32_t i=0; i < (*m)->rows; i++){
    //free((*m)->vector[i]);
    //}
    free((*m)->vector);
    free(*m);
    *m = NULL;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// Referenced code provided in Sahiti's section
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t cols = bm_cols(m);
    bv_set_bit(m->vector, (r * cols) + c);
}

// Referenced code provided in Sahiti's section
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * (bm_cols(m)) + c);
}

// Referenced code provided in Sahiti's section
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t cols = bm_cols(m);
    return bv_get_bit(m->vector, (r * cols) + c);
}

// Referenced code provided in Sahiti's section
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *m = bm_create(1, length);
    for (uint32_t i = 0; i < length; i++) {
        if (byte & (1 << i)) {
            bv_set_bit(m->vector, i);
        } else {
            bv_clr_bit(m->vector, i);
        }
    }
    return m;
}

// Referenced code provided in Sahiti's section
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t val = 0x00;
    for (uint32_t i = 0; i < 8; i++) {
        //if (bv_get_bit(m->vector, i) == 1){
        //val |= (i) << 1;
        //}
        uint8_t indiv = bv_get_bit(m->vector, i);
        val |= indiv;
        //if (bv_get_bit(m->vector, i) == 1){
        //val |= 1%2 << (7-i);
        //}
    }
    //printf("%d\n", val);
    return val;
}

// Referenced code provided in Sahiti's section
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    // A is msg, B is generator matrix (G) <-- encode
    // A is one liner B is decoder matrix <-- decode
    BitMatrix *pdt = bm_create(A->rows, B->cols);
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < B->cols; j++) {
            uint8_t result = 0;
            for (uint32_t k = 0; k < B->rows; k += 1) {
                result += (bm_get_bit(A, i, k) * bm_get_bit(B, k, j));
            }
            if (result > 0) {
                bm_set_bit(pdt, i, j);
            }
        }
    }
    return pdt;
}

void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < bm_rows(m); i += 1) {
        for (uint32_t j = 0; j < bm_cols(m); j += 1) {
            printf("%d ", bm_get_bit(m, i, j));
        }
        printf("\n");
    }
}

/*
int main(void){
    BitMatrix *m = bm_create(4, 4);
    for (uint32_t i=0; i<bm_rows(m); i++){
        for (uint32_t j=0; j<bm_cols(m); j++){
	    bm_set_bit(m, i, j);
	}
    }
}
*/
