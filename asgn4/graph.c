#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    if (G->undirected == true) {
        printf("is undirected\n");
    } else {
        printf("not undirected\n");
    }
    for (uint32_t i = 0; i < vertices; i++) {
        G->visited[i] = false;
    }
    for (uint32_t j = 0; j < vertices; j++) {
        for (uint32_t k = 0; k < vertices; k++) {
            G->matrix[j][k] = 0;
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    //for (uint32_t i = 0; i<G->vertices; i++){
    //free(G->matrix[i]);
    //}
    //free((*G)->matrix);
    free(*G);
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    G->matrix[i][j] = k;
    if (G->undirected == true) {
        G->matrix[j][i] = k;
    }
    return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (G->matrix[i][j] > 0) {
        return true;
    } else {
        return false;
    }
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (G->matrix[i][j] > 0) {
        uint32_t val = G->matrix[i][j];
        return val;
    } else {
        return 0;
    }
}

bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v] == true) {
        return true;
    } else {
        return false;
    }
}

void graph_mark_visited(Graph *G, uint32_t v) {
    G->visited[v] = true;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    G->visited[v] = false;
}

void graph_print(Graph *G) {
    for (uint32_t m = 0; m < G->vertices; m++) {
        for (uint32_t n = 0; n < G->vertices; n++) {
            printf("%d\t", G->matrix[m][n]);
        }
        printf("\n");
    }
}
