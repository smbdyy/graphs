#include <malloc.h>
#include "VertexList.h"

struct VertexList* createVertexList(unsigned int size, struct Vertex** vertices) {
    struct VertexList* list = (struct VertexList* )malloc(sizeof(struct VertexList));
    if (list == NULL) return NULL;

    list->size = size;
    list->vertices = vertices;

    return list;
}

void deleteVertexList(struct VertexList* list) {
    free(list->vertices);
    free(list);
}
