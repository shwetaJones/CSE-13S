#include "ll.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

uint64_t seeks;
uint64_t links;

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

// Referenced psuedocode provided by Sahiti
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll == NULL) {
        return NULL;
    }
    ll->length = 0;
    ll->mtf = mtf;
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    return ll;
}

void ll_delete(LinkedList **ll) {
    while ((*ll)->head != NULL) {
        Node *a = (*ll)->head->next;
        node_delete(&(*ll)->head);
        (*ll)->head = a;
    }
    free(*ll);
    (*ll) = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

// Referenced pseudocode provided by Sahiti
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks += 1;
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        int val = strcmp(oldspeak, n->oldspeak);
        if (val == 0) {
            if (ll->mtf) {
                n->prev->next = n->next;
                n->next->prev = n->prev;
                n->next = ll->head->next;
                n->prev = ll->head;
                ll->head->next->prev = n;
                ll->head->next = n;
            }
            links += 1;
            return n;
        }
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *n = node_create(oldspeak, newspeak);
        n->next = ll->head->next;
        n->prev = ll->head;
        ll->head->next->prev = n;
        ll->head->next = n;
        ll->length += 1;
    }
}

void ll_print(LinkedList *ll) {
    if (ll != NULL) {
        Node *n = ll->head->next;
        for (uint32_t i = 0; i < ll_length(ll); i++) {
            node_print(n);
            n = n->next;
        }
        printf("\n");
    }
}
