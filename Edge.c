#include "Edge.h"
#include <malloc.h>

struct Edge* createEdge(unsigned int* ports, unsigned int toVertexNumber) {
	struct Edge* e = (struct Edge* )malloc(sizeof(struct Edge));
    if (e == NULL) return NULL;

	e->ports = ports;
	e->toVertexNumber = toVertexNumber;

	return e;
}

void deleteEdge(struct Edge* edge) {
	free(edge->ports);
	free(edge);
}