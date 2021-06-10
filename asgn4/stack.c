#include "stack.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

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

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
}

bool stack_empty(Stack *s) {
    s->top = 0;
    return true;
}

bool stack_full(Stack *s) {
    s->top = s->capacity;
    return true;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, uint32_t x) {
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

bool stack_peek(Stack *s, uint32_t *x) {
    if (!stack_empty(s)) {
        *x = s->items[(s->top) - 1];
        return true;
    }
    return false;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

void stack_copy(Stack *dst, Stack *src) {
    dst = stack_create(4);
    src = stack_create(4);
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}

//int main(void){
//Stack *s = stack_create(4);
//printf("%d\n", stack_push(s, 4));
//stack_push(s, 6);
//char *cities[3][10] = {"Texas", "Cali", "Oregon"};
//FILE *outfile = stdout;
//stack_print(s, outfile, *cities);
//printf
//uint32_t a;
//printf("%d\n", stack_peek(s, &a));
//printf("%d\n", a);
//printf("%d\n", stack_size(s));
//stack_delete(&s);
//if (s == NULL){
//printf("delete works");
//}
//printf("%d\n", stack_size(s));
//return 0;
//}
