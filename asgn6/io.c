#include "io.h"

#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
}

bool read_bit(int infile, uint8_t *bit) {
}

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        if (get_bit(c, i) == 1) {
            set_bit(buffer, bufind);
        } else {
        }
    }
}

void flush_codes(int outfile) {
}
