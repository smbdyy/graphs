#include "AdjacencyList.h"
#include "malloc.h"

void deleteAdjacencyList(struct AdjacencyList* list) {
    for (int i = 0; i < list->size; i++) {
        deleteEdge(list->edges[i]);
    }

    free(list->edges);
}