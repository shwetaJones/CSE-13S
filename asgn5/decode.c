#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "hvi:o:"
void helpInfo(void) {
    printf("SYNOPSIS\n");
    printf("   A Hamming(8, 4) systemic code decoder.\n");
    printf("\n");
    printf("USAGE");
    printf("   ./encode [-h] [-v] [-i infile] [-o outfile]");
    printf("\n");
    printf("OPTIONS");
    printf("   -h            Program usage and help.\n");
    printf("   -v            Print statistics of decoding to stderr.\n");
    printf("   -i infile     Input data to decode.\n");
    printf("   -o outfile    Output of decoded data.\n");
}

// Taken from code within the pdf
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

// Referenced code within the pdf and Eugene's section logic
int main(int argc, char *argv[]) {
    int opt = 0;
    bool printStats = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            helpInfo();
            return 0;
            break;
        case 'v': printStats = true; break;
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
        default: fprintf(stderr, "Usage %s -[hvi:o:]\n", argv[0]);
        }
    }
    BitMatrix *H = bm_create(8, 4);
    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (i != j) {
                bm_set_bit(H, i, j);
            }
        }
    }
    for (uint32_t i = 4; i < 8; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (j + 4 == i) {
                bm_set_bit(H, i, j);
            }
        }
    }
    //bm_print(H);
    char upper;
    char lower;
    //uint8_t packed;

    //char byte;
    float process = 0;
    float correct = 0;
    float uncorrect = 0;
    float ok = 0;
    while ((upper = fgetc(infile)), !feof(infile)) {
        lower = fgetc(infile);
        if (feof(infile))
            break;
        uint8_t packed = pack_byte(upper, lower);
        uint8_t msg = 0x00;
        enum HAM_STATUS decoded = ham_decode(H, packed, &msg);
        process += 2;
        if (decoded == -3) {
            ok += 1;
        } else {
            correct += 1;
            uncorrect += 1;
        }
        fputc(packed, outfile);
        fputc(decoded, outfile);
    }

    if (printStats == true) {
        fprintf(stderr, "Total bytes processed: %d\n", (uint32_t) process);
        fprintf(stderr, "Uncorrected errors: %d\n", (uint32_t) uncorrect);
        fprintf(stderr, "Corrected errors: %d\n", (uint32_t) correct);
        float error = (float) correct / (float) uncorrect;
        fprintf(stderr, "Error rate: %f\n", error);
    }
    bm_delete(&H);
    fclose(infile);
    fclose(outfile);
}
