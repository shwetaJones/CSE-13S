#include "defines.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Code {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

Code code_init(void) {
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    if (c->top > 0) {
        return true;
    } else {
        return false;
    }
}

bool code_push_bit(Code *c, uint8_t bit) {
    c->top = bit;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    c->top = c->bit;
    return true;
}

void code_print(Code *c) {
}
