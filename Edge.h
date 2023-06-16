#ifndef EDGE_H
#define EDGE_H

struct Edge {
	unsigned int* ports;
	unsigned int toVertexNumber;
};

struct Edge* createEdge(unsigned int* ports, unsigned int toVertexNumber);
void deleteEdge(struct Edge* edge);

#endif