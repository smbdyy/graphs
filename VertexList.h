#ifndef VERTEXLIST_H
#define VERTEXLIST_H

struct VertexList {
    unsigned int size;
    struct Vertex** vertices;
};

struct VertexList* createVertexList(unsigned int size, struct Vertex** vertices);
void deleteVertexList(struct VertexList* list);

#endif
