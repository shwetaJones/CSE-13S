#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// referenced to the code from the assignment pdf
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// referenced pseudocode provided by Sahiti's section
void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t firstIndex = hash(bf->primary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, firstIndex);

    uint32_t secondIndex = hash(bf->secondary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, secondIndex);

    uint32_t thirdIndex = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, thirdIndex);
}

// referenced pseudocode provided by Sahiti's section
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t firstIndex = hash(bf->primary, oldspeak) % bf_size(bf);
    bv_get_bit(bf->filter, firstIndex);

    uint32_t secondIndex = hash(bf->secondary, oldspeak) % bf_size(bf);
    bv_get_bit(bf->filter, secondIndex);

    uint32_t thirdIndex = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_get_bit(bf->filter, thirdIndex);

    if (firstIndex == 1 && secondIndex == 1 && thirdIndex == 1) {
        return true;
    }
    return false;
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i) == 1) {
            count += 1;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
