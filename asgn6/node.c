#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <uistd.h>

struct Node {
    Node *left;
    Node *right;
    uint8_t symbol;
    uint64_t frequency;
};

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return NULL;
    }
    n->symbol = symbol;
    n->frequency = frequency;
    n->left = NULL;
    n->right = NULL;
}

void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

Node *node_join(Node *left, Node *right) {
    Node *n = node_create($, (left->freq + right->freq));
    //n->symbol = $;
    //n->freq = left->freq + right->freq;
    n->left = left;
    n->right = right;
}

void node_print(Node *n) {
    printf("%d, %d", n->symbol, n->frequency);
}
