#ifndef VERTEX_H
#define VERTEX_H

struct Vertex {
	char* computerName;
	unsigned int port;
};

struct Vertex* createVertex(char* computerName, unsigned int port);
void deleteVertex(Vertex* vertex);

#endif