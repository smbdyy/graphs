#include <malloc.h>
#include "VertexList.h"

struct VertexList* createVertexList() {
    struct VertexList* list = (struct VertexList* )malloc(sizeof(struct VertexList));
    if (list == NULL) return NULL;

    list->size = 0;
    list->vertices = NULL;

    return list;
}

void deleteVertexList(struct VertexList* list) {
    free(list->vertices);
    free(list);
}
