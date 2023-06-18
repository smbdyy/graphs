#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include "VertexList.h"

struct ComponentList {
    unsigned int count;
    struct VertexList** components;
};

struct ComponentList* createComponentList(unsigned int count, struct VertexList** components);
void deleteComponentList(struct ComponentList* list);

#endif
