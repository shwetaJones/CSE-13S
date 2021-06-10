#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WORD    "[a-zA-Z0-9_]+(-|')?[a-zA-Z0-9_]+)*"
#define OPTIONS "ht:f:ms"
#define BF_SIZE 2 << 20
#define HT_SIZE 10000

void helpInfo(void) {
    printf("SYNOPSIS\n");
    printf("  A word filtering program for the GPRSC.\n");
    printf("  Filters out and reports bad words parsed from stdin.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./banhammer [-hsm] [-t size] [-f size]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h           Program usage and help.\n");
    printf("  -s           Print program statistics.\n");
    printf("  -m           Enable move-to-front rule.\n");
    printf("  -t size      Specify hash table size (default: 10000).\n");
    printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t bfSize = BF_SIZE;
    uint32_t htSize = HT_SIZE;
    bool mtf = false;
    bool stats = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            helpInfo();
            return 0;
            break;
        case 't':
            htSize = atoi(optarg);
            if (htSize <= 0) {
                printf("Invalid hash table size.\n");
                return 0;
                break;
            }
            break;
        case 'f':
            bfSize = atoi(optarg);
            if (bfSize <= 0) {
                printf("Invalid Bloom Filter size.\n");
                return 0;
                break;
            }
            break;
        case 'm': mtf = true; break;
        case 's': stats = true; break;
        default: fprintf(stderr, "Usage %s -[ht:f:ms]\n", argv[0]);
        }
    }
    HashTable *ht = ht_create(htSize, mtf);
    if (!ht) {
        fprintf(stderr, "Invalid hash table size.\n");
        exit(0);
    }

    BloomFilter *bf = bf_create(bfSize);
    if (!bf) {
        fprintf(stderr, "Invalid Bloom Filter size.\n");
        exit(0);
    }

    char badList[10000];
    FILE *badFile = fopen("badspeak.txt", "r");
    while (fscanf(badFile, "%s\n", badList) != EOF) {
        bf_insert(bf, badList);
        ht_insert(ht, badList, NULL);
    }
    fclose(badFile);

    char oldList[4000];
    char newList[4000];
    FILE *newFile = fopen("newspeak.txt", "r");
    while (fscanf(newFile, "%s %s\n", oldList, newList) != EOF) {
        bf_insert(bf, oldList);
        ht_insert(ht, oldList, newList);
    }
    fclose(newFile);

    char *word = NULL;
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failer to compile regex.\n");
        return 0;
    }
    LinkedList *forbidden = ll_create(mtf);
    LinkedList *partial = ll_create(mtf);
    while ((word = next_word(stdin, &re)) != NULL) {
        for (uint32_t i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }
        if (bf_probe(bf, word) == true && ht_lookup(ht, word) != NULL) {
            if (ht_lookup(ht, word)->newspeak != NULL) {
                ll_insert(partial, ht_lookup(ht, word)->oldspeak, ht_lookup(ht, word)->newspeak);
            } else if (ht_lookup(ht, word)->newspeak == NULL) {
                ll_insert(forbidden, ht_lookup(ht, word)->oldspeak, NULL);
            }
        }
    }
    if (stats != true) {
        if (ll_length(forbidden) != 0 && ll_length(partial) != 0) {
            printf("Dear beloved citizen of the GPRSC,\n");
            printf("\n");
            printf("We have some good news, and we have some bad news.\n");
            printf("The good news is that there is bad news. The bad news is that you will\n");
            printf("be send to joycamp and subjected to a week-long destitute existence.\n");
            printf("This is the penalty for using degenerate words, as well as using\n");
            printf("oldspeak in place of newspeak. We hope you can correct your behavior.\n");
            printf("\n");
            printf("Your transgressions, followed by the words you must think on:\n");
            printf("\n");
            ll_print(forbidden);
            ll_print(partial);
        } else if (ll_length(forbidden) != 0 && ll_length(partial) == 0) {
            printf("Dear beloved citizen of the GPRSC,\n");
            printf("\n");
            printf("You have been caught using degenerate words that may cause\n");
            printf("distress among the moral and upstanding citizens of the GPRSC.\n");
            printf("As such, you will be sent to joycamp, It is there where you will\n");
            printf("sit and reflect on the consequences of your choice in language.\n");
            printf("\n");
            printf("Your transgressions:\n");
            ll_print(forbidden);
        } else if (ll_length(forbidden) == 0 && ll_length(partial) != 0) {
            printf("Dear beloved citizen of the GPRSC,\n");
            printf("We recognize your efforts in conforming to the language standards\n");
            printf("of the GPRSC. Alas, you have been caught uttering questionable words\n");
            printf("and thinking unpleasent thoughts. You must correct your wrongspeak\n");
            printf("and badthink at once. Failture to do so will result in your deliverance\n");
            printf("to joycamp\n");
            printf("\n");
            printf("Words that you must think on\n");
            printf("\n");
            ll_print(partial);
        }
    }
    if (stats == true) {
        printf("Seeks: %lu\n", seeks);

        float seekLength = (seeks / links);
        printf("Average seek length: %f\n", seekLength);

        float htcount = ht_count(ht);
        float htsize = ht_size(ht);
        float hashLoad = 100 * (htcount / htsize);
        printf("Hash table load: %f%%\n", hashLoad);

        float bfcount = bf_count(bf);
        float bfsize = bf_size(bf);
        float bloomLoad = 100 * (bfcount / bfsize);
        bloomLoad = hashLoad;
        printf("Bloom filter load: %f%%\n", bloomLoad);
    }
    clear_words();
    regfree(&re);
    ll_delete(&forbidden);
    ll_delete(&partial);
    bf_delete(&bf);
    ht_delete(&ht);
    return 0;
}
