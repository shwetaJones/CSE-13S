#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path &(*(p->vertices)) = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);
    free(*p);
    *p = NULL;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t prev;
    if (stack_empty(p->vertices)) {
        stack_push(p->vertices, v);
        path->length += graph_edge_weight(G, START_VERTEX, v);
        return false;
    } else {
        stack_peek(p->vertices, &prev);
        stack_push(p->vertices, v);
        p->length += graph_edge_weight(G, START_VERTEX, &prev);
    }
    return true;
    //uint32_t i;
    //i = stack_peek(p,&i);
    //uint32_t j = v;
    //p->length += graph_edge_weight(G,i,j);
    //return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t prev;
    if (stack_empty(p->vertices)) {
        return false;
        //stack_push(p->vertices, vertex);
        //path->length += graph_edge_weight(G, START_VERTEX, v);
    } else {
        uint32_t prev;
        stack_peek(p->vertices, &prev);
        stack_pop(p->vertices, v);
        p->length -= graph_edge_weight(G, v, &prev);
        return true;
    }
    //uint32_t i;
    //i = stack_peek(p, &i);
    //uint32_t j = v;
    //p->length -= graph_edge_weight(G, i, j);
    //return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    uint32_t y = src->length;
    uint32_t z = dst->length;
    z += y;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print((p->vertices), outfile, cities);
}
