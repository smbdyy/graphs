#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "Vertex.h"
#include "Edge.h"
#include "AdjacencyList.h"
#include "VertexList.h"

struct Graph {
	unsigned int vertexCount;
	struct Vertex** vertices;
    struct AdjacencyList** adjacencyLists;
};

struct Graph* createEmptyGraph();
struct Graph* createRandomGraph();
unsigned int* findShortestPath(unsigned int fromVertexNumber, unsigned int toVertexNumber);
void deleteGraph(struct Graph* graph);
bool addVertex(struct Graph* graph, struct Vertex* vertex);
bool removeVertex(struct Graph* graph, unsigned int vertexNumber);
bool addEdge(struct Graph* graph, unsigned int fromVertexNumber, struct Edge* edge);
bool deleteEdgeFromGraph(struct Graph* graph, unsigned int fromVertexNumber, unsigned int edgeNumber);
int findDistance(struct Graph* graph, unsigned int fromVertexNumber, unsigned int toVertexNumber);
struct VertexList* findComputers(struct Graph* graph, unsigned int port);

#endif