#include "code.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "hi:o:"

void helpInfo(void) {
    printf("SYNOPSIS\n");
    printf("  A Huffman encoder\n");
    printf("  Decompresses a file using the Huffman coding algorithm.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./decode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h            Program usage and help.\n");
    printf("  -v            Print compression statistics.\n");
    printf("  -i infile     Input file to decompress.\n");
    printf("  -o outfile    Output of decompressed data.\n");
}

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
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
    char val;
    while ((val = fgetc(infile)), !feof(infile)) {
        if (feof(infile)) {
            break;
        }
        printf("%c", val);
    }
    fclose(infile);
    fclose(outfile);
}
