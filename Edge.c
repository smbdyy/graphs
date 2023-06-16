#include "Edge.h"

struct Edge* createEdge(unsigned int* ports, unsigned int toVertexNumber) {
	struct Edge* e = (struct Edge* )malloc(sizeof(struct Edge));
	e->ports = ports;
	e->toVertexNumber = toVertexNumber;

	return e;
}

void deleteEdge(struct Edge* edge) {
	free(edge->ports);
	free(edge);
}