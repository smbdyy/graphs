#ifndef GRAPHS_ADJACENCYLIST_H
#define GRAPHS_ADJACENCYLIST_H

#include <stdbool.h>
#include "Edge.h"
#include "malloc.h"

struct AdjacencyList {
    unsigned int size;
    struct Edge** edges;
};

void deleteAdjacencyList(struct AdjacencyList* list);
bool deleteEdgeFromList(struct AdjacencyList* list, unsigned int edgeNumber);
bool addEdgeToList(struct AdjacencyList* list, struct Edge* edge);

#endif
