#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <stdlib.h>
#include <time.h>

#define MAX_RANDOM_VERTICES 50

struct Graph* createEmptyGraph() {
    struct Graph* graph = (struct Graph* )malloc(sizeof(struct Graph));
    graph->vertexCount = 0;
    graph->adjacencyLists = NULL;
    graph->vertices = NULL;

    return graph;
}

//struct Graph* createRandomGraph() {
//    struct Graph* graph = (struct Graph* )malloc(sizeof(struct Graph));
//    srand(time(NULL));
//
//    unsigned int vertexAmount = rand() % MAX_RANDOM_VERTICES + 1;
//    graph->vertexCount = vertexAmount;
//    unsigned int portsAmount = rand() % vertexAmount + 1;
//
//    unsigned int* ports = (unsigned int* )malloc(sizeof(unsigned int) * portsAmount);
//    for (int i = 0; i < portsAmount; i++) {
//        ports[i] = rand();
//    }
//
//    struct Vertex** vertices = (struct Vertex** )malloc(sizeof(struct Vertex*) * vertexAmount);
//    for (int i = 0; i < vertexAmount; i++) {
//        unsigned int port = ports[rand() % portsAmount];
//        vertices[i] = createVertex("random name", port);
//    }
//
//    struct Edge*** adjacencyList = (struct Edge*** )malloc(sizeof(struct Edge**) * vertexAmount);
//    for (int i = 0; i < vertexAmount; i++) {
//
//    }
//}

void deleteGraph(struct Graph* graph) {
    for (int i = 0; i < graph->vertexCount; i++) {
        deleteVertex(graph->vertices[i]);
        deleteAdjacencyList(graph->adjacencyLists[i]);
    }

    free(graph->vertices);
    free(graph->adjacencyLists);
}

bool addVertex(struct Graph* graph, struct Vertex* vertex) {
    for (int i = 0; i < graph->vertexCount; i++) {
        if (vertex == graph->vertices[i]) return false;
    }

    struct Vertex** newVertices = (struct Vertex** )realloc(
            graph->vertices, sizeof(struct Vertex*) * (graph->vertexCount + 1));
    struct AdjacencyList** newLists = (struct AdjacencyList** )realloc(
            graph->adjacencyLists, sizeof(struct AdjacencyList* ) * (graph->vertexCount + 1));

    if (newVertices == NULL || newLists == NULL) {
        return false;
    }

    graph->vertices = newVertices;
    graph->adjacencyLists = newLists;
    graph->vertices[graph->vertexCount] = vertex;
    graph->adjacencyLists[graph->vertexCount] = NULL;
    graph->vertexCount++;

    return true;
}

bool removeVertex(struct Graph* graph, unsigned int vertexNumber) {
    if (vertexNumber >= graph->vertexCount) return false;

    
}