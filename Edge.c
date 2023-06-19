#include "Edge.h"
#include <malloc.h>

struct Edge* createEdge(unsigned int portsAmount, unsigned int* ports, unsigned int toVertexNumber) {
	struct Edge* e = (struct Edge* )malloc(sizeof(struct Edge));
    if (e == NULL) return NULL;

    e->portsAmount = portsAmount;
	e->ports = ports;
	e->toVertexNumber = toVertexNumber;

	return e;
}

void deleteEdge(struct Edge* edge) {
    if (edge == NULL) return;
	free(edge->ports);
	free(edge);
}

bool containsPort(struct Edge* edge, unsigned int port) {
    for (unsigned int i = 0; i < edge->portsAmount; i++) {
        if (edge->ports[i] == port) return true;
    }

    return false;
}

bool addPort(struct Edge* edge, unsigned int port) {
    unsigned int* newPorts = (unsigned int* )malloc(sizeof(unsigned int) * (edge->portsAmount + 1));
    if (newPorts == NULL) return false;

    newPorts[edge->portsAmount] = port;
    for (unsigned int i = 0; i < edge->portsAmount; i++) {
        newPorts[i] = edge->ports[i];
    }

    free(edge->ports);
    edge->ports = newPorts;
    edge->portsAmount++;
    return true;
}

bool deletePort(struct Edge* edge, unsigned int portNumber) {
    if (portNumber >= edge->portsAmount) return false;

    unsigned int* newPorts = (unsigned int* )malloc(sizeof(unsigned int) * (edge->portsAmount - 1));
    if (newPorts == NULL) return false;

    for (unsigned int i = 0; i < portNumber; i++) {
        newPorts[i] = edge->ports[i];
    }

    for (unsigned int i = portNumber + 1; i < edge->portsAmount; i++) {
        newPorts[i - 1] = edge->ports[i];
    }

    free(edge->ports);
    edge->ports = newPorts;
    edge->portsAmount--;
    return true;
}