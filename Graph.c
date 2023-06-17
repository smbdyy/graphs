#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <stdlib.h>
#include <time.h>

#define MAX_RANDOM_VERTICES 50

struct Graph* createEmptyGraph() {
    struct Graph* graph = (struct Graph* )malloc(sizeof(struct Graph));
    if (graph == NULL) return NULL;

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

    struct Vertex** newVertices = (struct Vertex** )malloc(sizeof(struct Vertex*) * (graph->vertexCount + 1));
    struct AdjacencyList** newLists = (struct AdjacencyList** )
            malloc(sizeof(struct AdjacencyList*) * (graph->vertexCount + 1));

    if (newVertices == NULL || newLists == NULL) {
        return false;
    }

    for (int i = 0; i < graph->vertexCount; i++) {
        newVertices[i] = graph->vertices[i];
        newLists[i] = graph->adjacencyLists[i];
    }

    free(graph->vertices);
    free(graph->adjacencyLists);
    graph->vertices = newVertices;
    graph->adjacencyLists = newLists;
    graph->vertices[graph->vertexCount] = vertex;
    graph->adjacencyLists[graph->vertexCount]->size = 0;
    graph->vertexCount++;

    return true;
}

bool removeVertex(struct Graph* graph, unsigned int vertexNumber) {
    if (vertexNumber >= graph->vertexCount) return false;

    struct Vertex** newVertices = (struct Vertex** )malloc(sizeof(struct Vertex*) * (graph->vertexCount - 1));
    struct AdjacencyList** newLists = (struct AdjacencyList** )
            malloc(sizeof(struct AdjacencyList*) * (graph->vertexCount - 1));

    if (newVertices == NULL || newLists == NULL) {
        return false;
    }

    deleteVertex(graph->vertices[vertexNumber]);
    deleteAdjacencyList(graph->adjacencyLists[vertexNumber]);

    for (unsigned int i = vertexNumber; i < graph->vertexCount - 1; i++) {
        graph->vertices[i] = graph->vertices[i + 1];
        graph->adjacencyLists[i] = graph->adjacencyLists[i + 1];
    }

    graph->vertexCount--;
    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        newVertices[i] = graph->vertices[i];
        newLists[i] = graph->adjacencyLists[i];

        for (int j = 0; j < newLists[i]->size; j++) {
            if (newLists[i]->edges[j]->toVertexNumber == vertexNumber) {
                deleteEdgeFromList(newLists[i], j);
            }
        }
    }

    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        for (int j = 0; j < newLists[i]->size; j++) {
            if (newLists[i]->edges[j]->toVertexNumber > vertexNumber) {
                newLists[i]->edges[j]->toVertexNumber--;
            }
        }
    }

    return true;
}