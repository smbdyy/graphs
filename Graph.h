#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "Vertex.h"
#include "Edge.h"
#include "AdjacencyList.h"

struct Graph {
	unsigned int vertexCount;
	struct Vertex** vertices;
    struct AdjacencyList** adjacencyLists;
};

struct Graph* createEmptyGraph();
struct Graph* createRandomGraph();
unsigned int* findShortestPath(unsigned int fromVertexNumber, unsigned int toVertexNumber);
void clearGraph(struct Graph* graph);
bool addVertex(struct Graph* graph, struct Vertex* vertex);
bool removeVertex(struct Graph* graph, unsigned int vertexNumber);
void printGraphAsMatrix(struct Graph* graph);
void printGraphAsAdjacencyList(struct Graph* graph);
bool addEdge(struct Graph* graph, unsigned int fromVertexNumber, unsigned int toVertexNumber);
bool removeEdge(struct Graph* graph, unsigned int edgeNumber);

#endif