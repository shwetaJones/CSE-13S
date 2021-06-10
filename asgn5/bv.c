#include "bv.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Referenced code provided in Sahiti's section
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v == NULL) {
        return NULL;
    }
    v->length = length;
    if (length % 8 == 0) {
        v->vector = (uint8_t *) calloc((length / 8), sizeof(uint8_t));
    } else {
        uint32_t diff = length % 8;
        uint32_t newlength = diff + length;
        v->vector = (uint8_t *) calloc((newlength / 8), sizeof(uint8_t));
    }
    //v->vector = (uint8_t *) calloc ((length / 8), sizeof (uint8_t));
    if (v->vector == NULL) {
        free(v);
        return NULL;
    }
    return v;
}

// Referenced code provided in Sahiti's section
void bv_delete(BitVector **v) {
    free((*v)->vector);
    free(*v);
    *v = NULL;
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

// Referenced code provided in Sahiti's section
void bv_set_bit(BitVector *v, uint32_t i) {
    //uint8_t data = v->vector[i/8];
    uint8_t mask = 1 << (i % 8);
    //data = data | mask;
    v->vector[i / 8] = v->vector[i / 8] | mask;
}

// Referenced code provided in Sahiti's section
void bv_clr_bit(BitVector *v, uint32_t i) {
    uint8_t mask = ~(1 << (i % 8));
    v->vector[i / 8] = v->vector[i / 8] & mask;
}

// Referenced code provided in Sahiti's section
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    uint8_t data = v->vector[i / 8];
    return (data >> i % 8) & 1;
}

// Referenced code provided in Sahiti's section
void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    v->vector[i / 8] = v->vector[i / 8] ^ bit;
}

void bv_print(BitVector *v) {
    for (uint32_t i = 0; i < v->length; i++) {
        printf("%d ", bv_get_bit(v, i));
    }
    printf("\n");
}

//int main(void){
//BitVector *v = bv_create(32);
//bv_print(v);
//for (uint32_t i = 0; i<bv_length(v); i++){
//bv_set_bit(v, i);
//}
//uint32_t length = bv_length(v);
//printf("%d\n", length);
//uint32_t val = bv_get_bit(v, 6);
//printf("%d\n", val);
//uint32_t shift = (uint32_t)1;
//bv_set_bit(v, 1);
//bv_delete(&v);
//bv_print(v);
//uint8_t val = bv_get_bit(v, 1);
//printf("%d", val);
//}
