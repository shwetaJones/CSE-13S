#include "ht.h"

#include "ll.h"
#include "node.h"
#include "speck.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// References code provided within the assignment pdf
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < ht_size(*ht); i++) {
        if ((*ht)->lists[i]) {
            ll_delete(&((*ht)->lists[i]));
        }
    }
    free((*ht)->lists);
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// Referenced code provided by Sahiti
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    LinkedList *a = ht->lists[hash(ht->salt, oldspeak) % ht_size(ht)];
    if (a == NULL) {
        return NULL;
    }
    Node *b = ll_lookup(a, oldspeak);
    return b;
}

// Referenced code provided by Sahiti
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t val = (hash(ht->salt, oldspeak) % ht_size(ht));
    if (ht->lists[val] == NULL) {
        ht->lists[val] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[val], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if ((ht)->lists[i]) {
            count += 1;
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        LinkedList *a = ht->lists[i];
        if (a != NULL) {
            ll_print(a);
        }
    }
}
