#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

struct Edge {
	unsigned int* ports;
	struct Vertex* toVertex;
};

struct Edge createEdge(unsigned int* ports, struct Vertex* toVertex);

#endif