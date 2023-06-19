#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Queue.h"
#include "ComponentList.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MAX_RANDOM_VERTICES 10

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
    if (graph == NULL) return NULL;
    srand(time(NULL));

    unsigned int vertexAmount = rand() % MAX_RANDOM_VERTICES + 1;
    unsigned int portsAmount = rand() % vertexAmount + 1;

    unsigned int* ports = (unsigned int* )malloc(sizeof(unsigned int) * portsAmount);
    if (ports == NULL) {
        deleteGraph(graph);
        return NULL;
    }
    for (unsigned int i = 0; i < portsAmount; i++) {
        ports[i] = rand();
    }

    struct Vertex** vertices = (struct Vertex** )malloc(sizeof(struct Vertex*) * vertexAmount);
    if (vertices == NULL) {
        deleteGraph(graph);
        free(ports);
        return NULL;
    }
    for (unsigned int i = 0; i < vertexAmount; i++) {
        unsigned int port = ports[rand() % portsAmount];
        char name[200];
        sprintf(name, "random name %u", i);
        vertices[i] = createVertex(name, port);
    }

    struct AdjacencyList** adjacencyLists = (struct AdjacencyList** )
            malloc(sizeof(struct AdjacencyList*) * vertexAmount);
    if (adjacencyLists == NULL) {
        deleteGraph(graph);
        free(ports);
        free(vertices);
        return NULL;
    }

    for (unsigned int i = 0; i < vertexAmount; i++) {
        unsigned int edgesAmount = rand() % vertexAmount;
        struct Edge** edges = (struct Edge** )malloc(sizeof(struct Edge* ) * edgesAmount);
        if (edges == NULL) {
            deleteGraph(graph);
            free(ports);
            free(vertices);
            return NULL;
        }
        for (unsigned int j = 0; j < edgesAmount; j++) {
            unsigned int portsInEdgeAmount = rand() % portsAmount + 1;
            unsigned int* portsInEdge = (unsigned int* )malloc(sizeof(unsigned int) * portsInEdgeAmount);

            if (portsInEdge == NULL) {
                deleteGraph(graph);
                free(ports);
                free(vertices);
                free(edges);
                return NULL;
            }

            for (unsigned int k = 0; k < portsInEdgeAmount; k++) {
                portsInEdge[k] = ports[rand() % portsAmount];
            }

            unsigned int toVertexNumber = rand() % vertexAmount;
            while (toVertexNumber == i) {
                toVertexNumber = rand() % vertexAmount;
            }

            struct Edge* edge = createEdge(portsInEdgeAmount, portsInEdge, toVertexNumber);
            if (edge == NULL) {
                deleteGraph(graph);
                free(ports);
                free(vertices);
                free(edges);
                free(portsInEdge);
                return NULL;
            }
            edges[j] = edge;
        }

        adjacencyLists[i] = createAdjacencyList(edgesAmount, edges);
        if (adjacencyLists[i] == NULL) {
            for (unsigned int j = 0; j < i; j++) {
                deleteAdjacencyList(adjacencyLists[j]);
            }
            deleteGraph(graph);
            free(ports);
            free(vertices);
            free(edges);
            return NULL;
        }
    }

    free(ports);
    graph->vertexCount = vertexAmount;
    graph->adjacencyLists = adjacencyLists;
    graph->vertices = vertices;

    return graph;
}

void deleteGraph(struct Graph* graph) {
    if (graph == NULL) return;
    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        deleteVertex(graph->vertices[i]);
        deleteAdjacencyList(graph->adjacencyLists[i]);
    }

    free(graph->vertices);
    free(graph->adjacencyLists);
}

bool addVertex(struct Graph* graph, struct Vertex* vertex) {
    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        if (vertex == graph->vertices[i]) return false;
    }

    struct Vertex** newVertices = (struct Vertex** )malloc(sizeof(struct Vertex*) * (graph->vertexCount + 1));
    if (newVertices == NULL) return false;
    struct AdjacencyList** newLists = (struct AdjacencyList** )
            malloc(sizeof(struct AdjacencyList*) * (graph->vertexCount + 1));
    if (newLists == NULL) {
        free(newVertices);
        return NULL;
    }

    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        newVertices[i] = graph->vertices[i];
        newLists[i] = graph->adjacencyLists[i];
    }

    free(graph->vertices);
    free(graph->adjacencyLists);
    graph->vertices = newVertices;
    graph->adjacencyLists = newLists;
    graph->vertices[graph->vertexCount] = vertex;
    graph->adjacencyLists[graph->vertexCount] = createAdjacencyList(0, NULL);
    graph->vertexCount++;

    return true;
}

bool deleteVertexFromGraph(struct Graph* graph, unsigned int vertexNumber) {
    if (vertexNumber >= graph->vertexCount) return false;

    struct Vertex** newVertices = (struct Vertex** )malloc(sizeof(struct Vertex*) * (graph->vertexCount - 1));
    if (newVertices == NULL) return false;
    struct AdjacencyList** newLists = (struct AdjacencyList** )
            malloc(sizeof(struct AdjacencyList*) * (graph->vertexCount - 1));
    if (newLists == NULL) {
        free(newVertices);
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

        for (unsigned int j = 0; j < newLists[i]->size; j++) {
            if (newLists[i]->edges[j]->toVertexNumber == vertexNumber) {
                if (!deleteEdgeFromList(newLists[i], j)) return false;
            }
        }
    }

    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        for (unsigned int j = 0; j < newLists[i]->size; j++) {
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
    for (unsigned int i = 0; i < list->size; i++) {
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

    if (distances == NULL || visited == NULL || queue == NULL) {
        free(distances);
        free(visited);
        deleteQueue(queue);
        return -1;
    }

    for (unsigned int i = 0; i < n; i++) {
        distances[i] = -1;
        visited[i] = false;
    }

    distances[fromVertexNumber] = 0;
    visited[fromVertexNumber] = true;
    if (!enqueue(queue, fromVertexNumber)) {
        free(distances);
        free(visited);
        deleteQueue(queue);
        return -1;
    }

    while (queue->front != NULL) {
        unsigned int vertexNumber = dequeue(queue);
        struct Vertex* vertex = graph->vertices[vertexNumber];
        struct AdjacencyList* edges = graph->adjacencyLists[vertexNumber];
        for (unsigned int i = 0; i < edges->size; i++) {
            struct Edge* edge = edges->edges[i];

            unsigned int to = edge->toVertexNumber;
            struct Vertex* toVertex = graph->vertices[to];
            if (!containsPort(edge, vertex->port) || !containsPort(edge, toVertex->port) || visited[to]) {
                continue;
            }

            distances[to] = distances[vertexNumber] + 1;
            visited[to] = true;
            if (!enqueue(queue, to))  {
                free(distances);
                free(visited);
                deleteQueue(queue);
                return -1;
            }
            if (to == toVertexNumber) {
                int answer = distances[to];
                free(distances);
                free(visited);
                deleteQueue(queue);
                return answer;
            }
        }
    }

    int answer = distances[toVertexNumber];
    free(distances);
    free(visited);
    deleteQueue(queue);
    return answer;
}

struct VertexList* findComputers(struct Graph* graph, unsigned int port) {
    unsigned int n = graph->vertexCount;

    bool* visited = (bool* )malloc(sizeof(bool) * n);
    struct Queue* queue = createQueue();

    if (visited == NULL || queue == NULL) {
        free(visited);
        deleteQueue(queue);
        return NULL;
    }

    for (unsigned int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (unsigned int i = 0; i < n; i++) {
        if (visited[i] || graph->vertices[i]->port != port) continue;

        if (!enqueue(queue, i)) {
            free(visited);
            deleteQueue(queue);
            return NULL;
        }
        visited[i] = true;

        while (queue->front != NULL) {
            unsigned int vertexNumber = dequeue(queue);
            struct AdjacencyList* edges = graph->adjacencyLists[vertexNumber];
            struct Vertex* vertex = graph->vertices[vertexNumber];
            for (unsigned int j = 0; j < edges->size; j++) {
                struct Edge* edge = edges->edges[j];
                unsigned int to = edge->toVertexNumber;

                struct Vertex* toVertex = graph->vertices[to];
                if (!containsPort(edge, vertex->port) || !containsPort(edge, toVertex->port) || visited[to]) {
                    continue;
                }

                if (!enqueue(queue, to)) {
                    free(visited);
                    deleteQueue(queue);
                    return NULL;
                }
                visited[to] = true;
            }
        }
    }

    deleteQueue(queue);
    unsigned int count = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (visited[i]) count++;
    }

    struct Vertex** vertices = (struct Vertex** )malloc(sizeof(struct Vertex* ) * count);
    int index = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (visited[i]) {
            vertices[index] = graph->vertices[i];
            index++;
        }
    }

    free(visited);
    return createVertexList(count, vertices);
}

bool isReachable(struct Graph* graph, unsigned int fromNumber, unsigned int toNumber) {
    struct AdjacencyList* list = graph->adjacencyLists[fromNumber];
    struct Vertex* fromVertex = graph->vertices[fromNumber];
    struct Vertex* toVertex = graph->vertices[toNumber];
    for (unsigned int i = 0; i < list->size; i++) {
        struct Edge* edge = list->edges[i];
        if (edge->toVertexNumber == toNumber && containsPort(edge, toVertex->port) && containsPort(edge, fromVertex->port)) {
            return true;
        }
    }

    return false;
}

void freeMarked(bool** marked, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        free(marked[i]);
    }

    free(marked);
}

struct ComponentList* splitToComponents(struct Graph* graph) {
    unsigned int componentsCount = 0;
    unsigned int n = graph->vertexCount;

    bool* visited = (bool* )malloc(sizeof(bool) * n);
    struct Queue* queue = createQueue();
    bool** marked = (bool** )malloc(sizeof(bool* ) * n);

    if (visited == NULL || queue == NULL || marked == NULL) {
        free(visited);
        free(marked);
        deleteQueue(queue);
        return NULL;
    }

    for (unsigned int i = 0; i < n; i++) {
        marked[i] = (bool* )malloc(sizeof(bool) * n);
        if (marked[i] == NULL) {
            free(visited);
            deleteQueue(queue);
            freeMarked(marked, n);
            return NULL;
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (unsigned int i = 0; i < n; i++) {
        if (visited[i]) continue;

        if (!enqueue(queue, i)) {
            free(visited);
            deleteQueue(queue);
            freeMarked(marked, n);
            return NULL;
        }

        visited[i] = true;
        marked[componentsCount][i] = true;

        while (queue->front != NULL) {
            unsigned int vertexNumber = dequeue(queue);
            struct Vertex* vertex = graph->vertices[vertexNumber];
            struct AdjacencyList* list = graph->adjacencyLists[vertexNumber];

            for (unsigned int j = 0; j < list->size; j++) {
                struct Edge* edge = list->edges[j];
                struct Vertex* toVertex = graph->vertices[edge->toVertexNumber];
                if (visited[edge->toVertexNumber] ||
                    !containsPort(edge, vertex->port) ||
                    !containsPort(edge, toVertex->port) ||
                    !isReachable(graph, edge->toVertexNumber, vertexNumber))
                    continue;

                if (!enqueue(queue, edge->toVertexNumber)) {
                    free(visited);
                    freeMarked(marked, n);
                    deleteQueue(queue);
                    return NULL;
                }

                visited[edge->toVertexNumber] = true;
                marked[componentsCount][edge->toVertexNumber] = true;
            }
        }

        componentsCount++;
    }

    struct VertexList** vertexLists = (struct VertexList** )malloc(sizeof(struct VertexList*) * componentsCount);
    if (vertexLists == NULL) {
        free(visited);
        freeMarked(marked, n);
        deleteQueue(queue);
        return NULL;
    }

    for (unsigned int i = 0; i < componentsCount; i++) {
        unsigned int size = 0;
        for (unsigned int j = 0; j < n; j++) {
            if (marked[i][j]) size++;
        }

        struct Vertex** vertices = (struct Vertex** )malloc(sizeof(struct Vertex* ) * size);
        if (vertices == NULL) {
            free(visited);
            freeMarked(marked, n);
            deleteQueue(queue);
            deleteVertexLists(vertexLists, componentsCount);
            return NULL;
        }

        unsigned int vertexIndex = 0;
        for (unsigned int j = 0; j < n; j++) {
            if (marked[i][j]) {
                vertices[vertexIndex] = graph->vertices[j];
                vertexIndex++;
            }
        }

        struct VertexList* list = createVertexList(size, vertices);
        if (list == NULL) {
            free(vertices);
            free(visited);
            freeMarked(marked, n);
            deleteQueue(queue);
            deleteVertexLists(vertexLists, componentsCount);
            return NULL;
        }

        free(vertices);
        vertexLists[i] = list;
    }

    struct ComponentList* list = createComponentList(componentsCount, vertexLists);

    free(visited);
    freeMarked(marked, n);
    deleteQueue(queue);
    deleteVertexLists(vertexLists, componentsCount);
    return list;
}