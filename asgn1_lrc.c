#include "philos.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static inline uint8_t left(uint8_t pos, uint8_t players) {
    return ((pos + players - 1) % players);
}

static inline uint8_t right(uint8_t pos, uint8_t players) {
    return ((pos + 1) % players);
}

int roll(void) {
    return (random() % 6);
}
int main() {
    unsigned int seed = 0;
    printf("Random Seed: ");
    scanf("%d", &seed);
    srandom(seed);
    if (seed > UINT32_MAX || seed < 1) {
        printf("Pseudorandom number must be non-negative (%d)\n", seed);
    } else {
        int players = 0;
        printf("How many players? ");
        scanf("%d", &players);
        if (players > 0 && players < 15) {
            int playerLives[players];
            for (int i = 0; i < players; i++) {
                playerLives[i] = 3;
            }
            int center = 0;
            int deadCount = 0;
            while (deadCount < (players - 1)) {
                for (int j = 0; j < players; j++) {
                    int rolls = playerLives[j];
                    if (rolls > 0) {
                        printf("%s rolls... ", philosophers[j]);
                        int numRounds = rolls;
                        if (rolls > 2) {
                            numRounds = 3;
                        } else {
                            numRounds = rolls;
                        }
                        for (int a = 0; a < numRounds; a++) {
                            int rollVal = roll();
                            if (rollVal == 0) {
                                int leftPlayer = left(j, players);
                                playerLives[j] -= 1;
                                playerLives[leftPlayer] += 1;
                                printf("gives $1 to %s ", philosophers[leftPlayer]);
                            } else if (rollVal == 1) {
                                int rightPlayer = right(j, players);
                                playerLives[j] -= 1;
                                playerLives[rightPlayer] += 1;
                                printf("gives $1 to %s ", philosophers[rightPlayer]);
                            } else if (rollVal == 2) {
                                playerLives[j] -= 1;
                                center += 1;
                                printf("puts $1 in the pot ");
                            } else {
                                printf("gets a pass ");
                            }
                            if (a == (numRounds - 1)) {
                                printf("\n");
                            }
                        }
                    }
                    deadCount = 0;
                    for (int k = 0; k < players; k++) {
                        if (playerLives[k] < 1) {
                            deadCount += 1;
                        }
                    }
                    if (deadCount == (players - 1)) {
                        break;
                    }
                }
            }
            int highest = 0;
            int highestPos = 0;
            for (int h = 0; h < players; h++) {
                if (playerLives[h] > highest) {
                    highest = playerLives[h];
                    highestPos = h;
                }
            }
            printf("%s wins the $%d pot with $%d left in the bank\n", philosophers[highestPos],
                center, playerLives[highestPos]);
        } else {
            printf("Number of players must be from 1-14 \n");
        }
    }
    return 0;
}
