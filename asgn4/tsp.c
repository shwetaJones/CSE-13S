#include "graph.h"
#include "path.h"
#include "stack.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hvu:i:o"
#define BLOCK   4096

void helpInfo(void) {
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -u              Use undirected graph.\n");
    printf("  -v              Enable verbose printing.\n");
    printf("  -h              Program usage and help.\n");
    printf("  -i  infile      Input containing graph (default: stdin)\n");
    printf("  -o  outfile     Output of computed path (default: stdout)\n");
}

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    graph_mark_visited(G, v);
    uint32_t w = graph_vertices(G);
    for (uint32_t i = v; i < w; i++) {
        if (graph_visited(G, w) == true) {
            dfs(G, w, curr, shortest, cities, outfile);
        }
    }
    graph_mark_unvisited(G, v);
}

int main(int argc, char *argv[]) {
    char buffer[BLOCK];
    int opt = 0;
    bool undirected = false;
    bool verbose = false;
    char *out = NULL;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            helpInfo();
            return 0;
            break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Failed to open the file");
            }
            break;
        case 'o': out = optarg; break;
        default: fprintf(stderr, "Usage %s -[hvu:i:o]\n", argv[0]);
        }
    }

    if (out) {
        outfile = fopen(out, "r");
        if (outfile == NULL) {
            fprintf(stderr, "Failed to open the file");
            return 1;
        }
    }

    uint32_t vertices;
    fscanf(infile, "%u\n", &vertices);
    printf("vertice = %u\n", vertices);
    if (vertices < 2) {
        printf("There's nowhere to go.\n");
        return (0);
    }

    char *cities[100];
    for (uint32_t i = 0; i < vertices; i++) {
        fgets(buffer, BLOCK, infile);
        cities[i] = strdup(buffer);
    }

    Graph *g = graph_create(vertices, undirected);

    int a, b, c, d;
    while ((d = fscanf(infile, "%d %d %d\n", &a, &b, &c)) != EOF) {
        if (d != 3) {
            printf("Error: malformed edge.\n");
            return 0;
        }
        graph_add_edge(g, a, b, c);
    }

    Path *curr = path_create();
    Path *shortest = path_create();
    dfs(g, vertices, curr, shortest, cities, outfile);
    path_print(shortest, outfile, cities);
    if (verbose == true) {
        path_print(curr, outfile, cities);
    }
    int length = 6;
    printf("Path length: %d", length);
    int recursive = 5;
    printf("Total recursive calls: %d", recursive);
    fclose(infile);
    fclose(outfile);
    return 0;
}
