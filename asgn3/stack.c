#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Referenced Code provided by the pdf and code from Sahiti's office hour
struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

// Initializes the stack based on the capacity
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Deletes the values within the stack
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Returns if the stack is empty
bool stack_empty(Stack *s) {
    return s->top == 0;
}

// Returns is the stack is full
bool stack_full(Stack *s) {
    return s->top == 1;
}

// Returns the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Adds to the stack
bool stack_push(Stack *s, int64_t x) {
    if (s->top == s->capacity) {
        s->capacity = 2 * s->capacity;
        s->items = (int64_t *) realloc(s->items, s->capacity * sizeof(int64_t));
        if (s->items == NULL) {
            return false;
        }
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

// Removes from the stack
bool stack_pop(Stack *s, int64_t *x) {
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

// Prints the stack
void stack_print(Stack *s) {
    for (uint32_t p = 0; p < s->top; p++) {
        printf("%ld ", s->items[s->top]);
    }
    printf("\n");
}
