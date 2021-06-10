#include "bubble.h"
#include "counts.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"

//Followed the pseudocode provided by Eugene during section to create this code
void createArray(uint32_t *A, int length) {
    for (int i = 0; i < length; i++) {
        A[i] = random();
    }
}

void stats(char *sortName, int elements, int length, uint32_t *A) {
    printf("%s\n", sortName);
    printf("%d elements, %d moves, %d compares\n", length, swapCount, compCount);
    if (elements > 0) {
        int newLine = 0;
        while (newLine < elements) {
            printf("%13" PRIu32, A[newLine]);
            if ((newLine + 1) % 5 == 0) {
                printf("\n");
            }
            newLine++;
        }
        if (newLine % 5 > 0) {
            printf("\n");
        }
    }
}

enum Sorting {
    bubble,
    shell,
    stack,
    queue,
} Sorting;

int main(int argc, char *argv[]) {
    Set s = set_empty();
    int opt = 0;
    int seed = 13371453; //default from PDF, pg 10
    int length = 100; //default from PDF, pg 10
    int elements = 100; //default from PDF, pg 10
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': s = set_complement(set_empty()); break;
        case 'b': s = set_insert(s, bubble); break;
        case 's': s = set_insert(s, shell); break;
        case 'q': s = set_insert(s, stack); break;
        case 'Q': s = set_insert(s, queue); break;
        case 'r': seed = atoi(optarg); break;
        case 'n': length = atoi(optarg); break;
        case 'p': elements = atoi(optarg); break;
        default: fprintf(stderr, "Usage %s -[absqQr:n:p]\n", argv[0]);
        }
    }
    if (elements > length) {
        elements = length;
    }
    void (*sortCalls[4])(uint32_t *, uint32_t);
    sortCalls[0] = bubble_sort;
    sortCalls[1] = shell_sort;
    sortCalls[2] = quick_sort_stack;
    sortCalls[3] = quick_sort_stack;
    char *sorts[4] = { "Bubble Sort", "Shell Sort", "Quick Sort (Stack)", "Quick Sort (Queue)" };
    uint32_t *A = (uint32_t *) malloc(length * sizeof(uint32_t));
    int i = bubble;
    while (i <= queue) {
        if (set_member(s, i)) {
            compCount = 0;
            swapCount = 0;
            srandom(seed);
            createArray(A, length);
            sortCalls[i](A, length);
            stats(sorts[i], elements, length, A);
        }
        i++;
    }
    free(A);
    return 0;
}
