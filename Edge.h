#include <stdbool.h>

#ifndef EDGE_H
#define EDGE_H

struct Edge {
    unsigned int portsAmount;
	unsigned int* ports;
	unsigned int toVertexNumber;
};

struct Edge* createEdge(unsigned int portsAmount, unsigned int* ports, unsigned int toVertexNumber);
void deleteEdge(struct Edge* edge);
bool containsPort(struct Edge* edge, unsigned int port);

#endif