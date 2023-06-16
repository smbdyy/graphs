#ifndef GRAPH_H
#define GRAPH_H

#include "Vretex.h"
#include "Edge.h"

struct Graph {
	unsigned int vertexCount;
	struct Vertex** vertexes;
	struct Edge*** adjacencyList;
};

struct Graph* createEmptyGraph();
struct Graph* createRandomGraph();
unsigned int* findShortestPath(unsigned int fromVertexNumber, unsigned int toVertexNumber);
void clearGraph(Graph* graph);
bool addVertex(Graph* graph, Vertex* vertex);
bool removeVertex(Graph* graph, unsigned int vertexNumber);
void printGraphAsMatrix(Graph* graph);
void printGraphAsAdjacencyList(Graph* graph);
bool addEdge(Graph* graph, unsigned int fromVertexNumber, unsigned int toVertexNumber);
bool removeEdge(Graph* graph, unsigned int edgeNumber);

#endif