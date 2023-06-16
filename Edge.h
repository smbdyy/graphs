#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

struct Edge {
	unsigned int* ports;
	unsigned int toVertexNumber;
};

struct Edge createEdge(unsigned int* ports, unsigned int toVertexNumber);

#endif