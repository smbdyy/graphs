#include "AdjacencyList.h"
#include "malloc.h"

void deleteAdjacencyList(struct AdjacencyList* list) {
    for (int i = 0; i < list->size; i++) {
        deleteEdge(list->edges[i]);
    }

    free(list->edges);
}

bool deleteEdgeFromList(struct AdjacencyList* list, unsigned int edgeNumber) {
    if (edgeNumber >= list->size) return false;

    struct Edge** newList = (struct Edge** )malloc(sizeof(struct Edge*) * (list->size - 1));
    if (newList == NULL) return false;

    deleteEdge(list->edges[edgeNumber]);
    for (int i = 0; i < edgeNumber; i++) {
        newList[i] = list->edges[i];
    }
    for (unsigned int i = edgeNumber + 1; i < list->size; i++) {
        newList[i - 1] = list->edges[i];
    }

    free(list->edges);
    list->edges = newList;
    list->size--;

    return true;
}

bool addEdgeToList(struct AdjacencyList* list, struct Edge* edge) {
    struct Edge** newList = (struct Edge** )malloc(sizeof(struct Edge*) * (list->size + 1));
    if (newList == NULL) return false;

    for (unsigned int i = 0; i < list->size; i++) {
        newList[i] = list->edges[i];
    }
    newList[list->size] = edge;

    free(list->edges);
    list->edges = newList;
    list->size++;

    return true;
}