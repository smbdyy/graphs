#ifndef GRAPHS_ADJACENCYLIST_H
#define GRAPHS_ADJACENCYLIST_H

#include "Edge.h"
#include "malloc.h"

struct AdjacencyList {
    unsigned int size;
    struct Edge** edges;
};

void deleteAdjacencyList(struct AdjacencyList* list);

#endif
