#include "Vertex.h"
#include <malloc.h>
#include <memory.h>

struct Vertex* createVertex(char* computerName, unsigned int port) {
	struct Vertex* v = (struct Vertex* )malloc(sizeof(struct Vertex));
    if (v == NULL) return NULL;

    v->computerName = (char* )malloc(sizeof(char) * 200);
    if (v->computerName == NULL) {
        return NULL;
    }
    memcpy(v->computerName, computerName, 200);
	v->port = port;

	return v;
}

void deleteVertex(struct Vertex* vertex) {
    if (vertex == NULL) return;
    free(vertex->computerName);
	free(vertex);
}