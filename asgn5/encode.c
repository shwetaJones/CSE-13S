#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "hi:o:"

void helpInfo(void) {
    printf("SYNOPSIS\n");
    printf("   A Hamming(8, 4) systemic code generator.\n");
    printf("\n");
    printf("USAGE");
    printf("   ./encode [-h] [-i infile] [-o outfile]");
    printf("\n");
    printf("OPTIONS");
    printf("   -h            Program usage and help.\n");
    printf("   -i infile     Input data to encode.\n");
    printf("   -o outfile    Output of encoded data.\n");
}

// Taken from code within the pdf
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// Taken from code within the pdf
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

// Referenced code provided in pdf and Eugene's logic
int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    //strcut stat statbuf;
    //fstat(fileno(infile), &statbuf);
    //fchmod(fileno(outfile), statbuf.st_mode);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            helpInfo();
            return 0;
            break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Failed to open the file");
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Failed to open the file");
            }
            break;
        default: fprintf(stderr, "Usage %s -[hio]\n", argv[0]);
        }
    }

    //fstat(fileno(infile), &statbuf);
    //fchmod(fileno(outfile), statbuf.st_mode);

    BitMatrix *G = bm_create(4, 8);
    char byte;
    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (i == j) {
                bm_set_bit(G, i, j);
            }
        }
    }
    for (uint32_t s = 0; s < bm_rows(G); s++) {
        for (uint32_t t = 4; t < bm_cols(G); t++) {
            if (s + 4 != t) {
                bm_set_bit(G, s, t);
            }
        }
    }
    //bm_print(m);
    while ((byte = fgetc(infile)), !feof(infile)) {
        if (feof(infile))
            break;
        uint8_t lower = lower_nibble(byte);
        uint8_t upper = upper_nibble(byte);
        uint8_t lowerCode = ham_encode(G, lower);
        uint8_t upperCode = ham_encode(G, upper);
        fputc(lowerCode, outfile);
        fputc(upperCode, outfile);
    }
    bm_delete(&G);
    fclose(infile);
    fclose(outfile);
}
