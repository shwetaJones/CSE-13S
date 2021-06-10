#include "node.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Refered to code from previous code
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return NULL;
    }
    n->oldspeak = oldspeak ? strcpy(malloc(strlen(oldspeak) + 1), oldspeak) : NULL;
    n->newspeak = newspeak ? strcpy(malloc(strlen(oldspeak) + 1), oldspeak) : NULL;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// Refered to previous code
void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
}

// Refered to psuedocode provided in assignment pdf
void node_print(Node *n) {
    if (n->oldspeak && n->newspeak != NULL) {
        printf(" %s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->oldspeak != NULL && n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    }
}
