#include <malloc.h>
#include "ComponentList.h"

struct ComponentList* createComponentList(unsigned int count, struct VertexList** components) {
    struct ComponentList* list = (struct ComponentList* )malloc(sizeof(struct ComponentList));
    if (list == NULL) return NULL;

    list->count = count;
    list->components = components;
    return list;
}

void deleteComponentList(struct ComponentList* list) {
    if (list == NULL) return;
    for (int i = 0; i < list->count; i++) {
        deleteVertexList(list->components[i]);
    }

    free(list);
}