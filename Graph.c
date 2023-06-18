#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Queue.h"
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

struct Graph* createRandomGraph() {
    struct Graph* graph = (struct Graph* )malloc(sizeof(struct Graph));
    srand(time(NULL));

    unsigned int vertexAmount = rand() % MAX_RANDOM_VERTICES + 1;
    graph->vertexCount = vertexAmount;
    unsigned int portsAmount = rand() % vertexAmount + 1;

    unsigned int* ports = (unsigned int* )malloc(sizeof(unsigned int) * portsAmount);
    if (ports == NULL) return NULL;
    for (int i = 0; i < portsAmount; i++) {
        ports[i] = rand();
    }

    struct Vertex** vertices = (struct Vertex** )malloc(sizeof(struct Vertex*) * vertexAmount);
    if (vertices == NULL) return NULL;
    for (int i = 0; i < vertexAmount; i++) {
        unsigned int port = ports[rand() % portsAmount];
        vertices[i] = createVertex("random name", port);
    }

    struct AdjacencyList** adjacencyLists = (struct AdjacencyList** )
            malloc(sizeof(struct AdjacencyList*) * vertexAmount);
    if (adjacencyLists == NULL) return NULL;

    for (int i = 0; i < vertexAmount; i++) {
        unsigned int edgesAmount = rand() % vertexAmount;
        struct Edge** edges = (struct Edge** )malloc(sizeof(struct Edge* ) * edgesAmount);
        if (edges == NULL) return NULL;
        for (int j = 0; j < edgesAmount; j++) {
            unsigned int portsInEdgeAmount = rand() % portsAmount + 1;
            unsigned int* portsInEdge = (unsigned int* )malloc(sizeof(unsigned int) * portsInEdgeAmount);

            if (portsInEdge == NULL) return NULL;

            for (int k = 0; k < portsInEdgeAmount; k++) {
                portsInEdge[i] = ports[rand() % portsAmount];
            }

            unsigned int toVertexNumber = rand() % vertexAmount;
            while (toVertexNumber == i) {
                toVertexNumber = rand() % vertexAmount;
            }

            struct Edge* edge = createEdge(portsInEdgeAmount, portsInEdge, toVertexNumber);
            if (edge == NULL) return NULL;
            edges[j] = edge;
        }

        adjacencyLists[i]->size = edgesAmount;
        adjacencyLists[i]->edges = edges;
    }

    free(ports);
    graph->vertexCount = vertexAmount;
    graph->adjacencyLists = adjacencyLists;
    graph->vertices = vertices;

    return graph;
}

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
                if (!deleteEdgeFromList(newLists[i], j)) return false;
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

bool addEdge(struct Graph* graph, unsigned int fromVertexNumber, struct Edge* edge) {
    if (fromVertexNumber >= graph->vertexCount) return false;

    struct AdjacencyList* list = graph->adjacencyLists[fromVertexNumber];
    for (int i = 0; i < list->size; i++) {
        if (list->edges[i] == edge) return false;
    }

    return addEdgeToList(list, edge);
}

bool deleteEdgeFromGraph(struct Graph* graph, unsigned int fromVertexNumber, unsigned int edgeNumber) {
    if (fromVertexNumber >= graph->vertexCount) return false;

    return deleteEdgeFromList(graph->adjacencyLists[fromVertexNumber], edgeNumber);
}

int findDistance(struct Graph* graph, unsigned int fromVertexNumber, unsigned int toVertexNumber) {
    unsigned int n = graph->vertexCount;
    if (fromVertexNumber >= n || toVertexNumber >= n) return -1;

    int* distances = (int* )malloc(sizeof(int) * n);
    bool* visited = (bool* )malloc(sizeof(bool) * n);
    struct Queue* queue = createQueue();

    if (distances == NULL || visited == NULL || queue == NULL) return -1;

    for (int i = 0; i < n; i++) {
        distances[i] = -1;
        visited[i] = false;
    }

    distances[fromVertexNumber] = 0;
    visited[fromVertexNumber] = true;
    enqueue(queue, fromVertexNumber);

    while (queue->front != NULL) {
        unsigned int vertexNumber = dequeue(queue);
        struct Vertex* vertex = graph->vertices[vertexNumber];
        struct AdjacencyList* edges = graph->adjacencyLists[vertexNumber];
        for (int i = 0; i < edges->size; i++) {
            struct Edge* edge = edges->edges[i];

            unsigned int to = edge->toVertexNumber;
            struct Vertex* toVertex = graph->vertices[to];
            if (!containsPort(edge, vertex->port) || !containsPort(edge, toVertex->port) || visited[to]) {
                continue;
            }

            distances[to] = distances[vertexNumber] + 1;
            visited[to] = true;
            enqueue(queue, to);
            if (to == toVertexNumber) return distances[to];
        }
    }

    return distances[toVertexNumber];
}