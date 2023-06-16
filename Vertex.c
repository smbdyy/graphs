#include "Vertex.h"
#include <stdlib.h>

struct Vertex* createVertex(char* computerName, unsigned int port) {
	struct Vertex* v = (struct Vertex* )malloc(sizeof(struct Vertex));
	v->computerName = computerName;
	v->port = port;

	return v;
}

void deleteVertex(struct Vertex* vertex) {
	free(vertex->computerName);
	free(vertex);
}